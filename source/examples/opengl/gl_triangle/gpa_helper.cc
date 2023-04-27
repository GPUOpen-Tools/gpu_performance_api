//==============================================================================
// Copyright (c) 2019-2022 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief GPA Helper class implementation.
//==============================================================================

#include "examples/opengl/gl_triangle/gpa_helper.h"

#include <chrono>
#include <thread>
#include <locale>

#ifdef _WIN32
#include <codecvt>
#endif

#include "examples/common/cmdline_parser.h"

GpaApiManager*    GpaApiManager::gpa_api_manager_ = nullptr;
GpaHelper*        GpaHelper::gpa_helper_          = nullptr;
GpaFuncTableInfo* gpa_function_table_info         = nullptr;

#ifdef _WIN32
/// @brief Converts string from wide to utf-8 encoding.
///
/// @return The converted utf-8 encoded string.
static std::string wide_to_utf8_converter(const std::wstring wide)
{
    int         num_bytes_needed = WideCharToMultiByte(CP_UTF8, 0, wide.data(), (int)wide.size(), nullptr, 0, nullptr, nullptr);
    std::string utf8;
    utf8.resize(num_bytes_needed);
    WideCharToMultiByte(CP_UTF8, 0, wide.data(), (int)wide.size(), utf8.data(), num_bytes_needed, nullptr, nullptr);
    return utf8;
}
#endif

GpaHelper* GpaHelper::Instance()
{
    if (nullptr == gpa_helper_)
    {
        gpa_helper_ = new (std::nothrow) GpaHelper();
    }

    return gpa_helper_;
}

void GpaHelper::DeleteInstance()
{
    if (nullptr != gpa_helper_)
    {
        delete gpa_helper_;
        gpa_helper_ = nullptr;
    }
}

void GpaLogger(GpaLoggingType log_type, const char* log_msg)
{
    std::string log_message;

    switch (log_type)
    {
    case kGpaLoggingError:
        log_message                                = "GPA ERROR: ";
        GpaHelper::Instance()->has_error_occurred_ = true;
        GpaHelper::Instance()->num_errors_occurred_ += 1;
        break;

    case kGpaLoggingTrace:
        log_message = "GPA TRACE: ";
        break;

    default:
        log_message = "GPA: ";
        break;
    }

    if (static_cast<unsigned int>(log_type) == static_cast<unsigned int>(kGlError))
    {
        log_message.clear();
        log_message                                = "GL ERROR: ";
        GpaHelper::Instance()->has_error_occurred_ = true;
        GpaHelper::Instance()->num_errors_occurred_ += 1;
    }

    if (static_cast<unsigned int>(log_type) == static_cast<unsigned int>(kWinError))
    {
        log_message.clear();
        log_message                                = "WINDOWS ERROR: ";
        GpaHelper::Instance()->has_error_occurred_ = true;
        GpaHelper::Instance()->num_errors_occurred_ += 1;
    }

    if (static_cast<unsigned int>(log_type) == static_cast<unsigned int>(kXServerError))
    {
        log_message.clear();
        log_message                                = "X SERVER ERROR: ";
        GpaHelper::Instance()->has_error_occurred_ = true;
        GpaHelper::Instance()->num_errors_occurred_ += 1;
    }

    log_message.append(log_msg);

    if (!GpaHelper::Instance()->gpa_log_file_stream_.is_open())
    {
        GpaHelper::Instance()->gpa_log_file_stream_.open(GpaHelper::Instance()->gpa_log_file_name_.c_str(), std::ios_base::out | std::ios_base::app);
    }

    GpaHelper::Instance()->gpa_log_file_stream_ << log_message << std::endl;
}

bool GpaHelper::ParseCommandLine(int argc, char* argv[])
{
    gpa_example::CmdlineParser cmdline_parser(argc, argv);
    app_ = new (std::nothrow) gpa_example::GpaSampleApp(AMDT_PROJECT_NAME, cmdline_parser);

    if (app_ == nullptr)
    {
        return false;
    }

    if (!app_->Initialize())
    {
        return false;
    }

    InitializeIO();

    return true;
}

bool GpaHelper::SetupGpa()
{
    bool success = kGpaStatusOk == GpaApiManager::Instance()->LoadApi(kGpaApiOpengl);

    if (success)
    {
        gpa_function_table_ = GpaApiManager::Instance()->GetFunctionTable(kGpaApiOpengl);

        if (nullptr != gpa_function_table_)
        {
            GpaLoggingType gpa_log_types = kGpaLoggingError;

            if (confirm_success_)
            {
                // Only log message types if confirm_success_ is enabled, because GPA will log a confirmation message
                // that the logging callback was registered, and we don't want to output a log if --verify was enabled
                // but not --confirmsuccess.
                gpa_log_types = kGpaLoggingErrorAndMessage;
            }

            gpa_function_table_->GpaRegisterLoggingCallback(gpa_log_types, GpaLogger);
            success = kGpaStatusOk == gpa_function_table_->GpaInitialize(kGpaInitializeDefaultBit);
        }
    }

    return success;
}

bool GpaHelper::OpenContext(GlContext gl_context, bool include_hw_counters)
{
    GpaOpenContextFlags open_context_flags = include_hw_counters ? kGpaOpenContextEnableHardwareCountersBit : kGpaOpenContextDefaultBit;
    bool                is_context_opened  = kGpaStatusOk == gpa_function_table_->GpaOpenContext(gl_context, open_context_flags, &gpa_context_id_);

    if (is_context_opened)
    {
        // Get the HW generation to aid in counter validation.
        gpa_function_table_->GpaGetDeviceGeneration(gpa_context_id_, &gpa_hw_generation_);
    }

    return is_context_opened;
}

bool GpaHelper::CloseContext()
{
    bool is_context_closed = true;
    if (gpa_context_id_ != nullptr)
    {
        is_context_closed = (kGpaStatusOk == gpa_function_table_->GpaCloseContext(gpa_context_id_));
        gpa_context_id_   = nullptr;
    }
    gpa_hw_generation_ = kGpaHwGenerationNone;
    return is_context_closed;
}

bool GpaHelper::CreateGpaSession()
{
    return kGpaStatusOk == gpa_function_table_->GpaCreateSession(gpa_context_id_, kGpaSessionSampleTypeDiscreteCounter, &gpa_session_id_);
}

bool GpaHelper::DestroyGpaSession()
{
    bool success = true;
    if (gpa_session_id_ != nullptr)
    {
        success         = (kGpaStatusOk == gpa_function_table_->GpaDeleteSession(gpa_session_id_));
        gpa_session_id_ = nullptr;
    }
    return success;
}

bool GpaHelper::EnableAllCounters()
{
    bool success = kGpaStatusOk == gpa_function_table_->GpaEnableAllCounters(gpa_session_id_);
    success      = success && kGpaStatusOk == gpa_function_table_->GpaGetPassCount(gpa_session_id_, &num_passes_required_);
    return success;
}

bool GpaHelper::EnableCounterByName(const char* name)
{
    bool success = kGpaStatusOk == gpa_function_table_->GpaEnableCounterByName(gpa_session_id_, name);
    success      = success && kGpaStatusOk == gpa_function_table_->GpaGetPassCount(gpa_session_id_, &num_passes_required_);
    return success;
}

bool GpaHelper::OnGpaSessionStart()
{
    current_pass_index_  = -1;
    gpa_command_list_id_ = nullptr;
    sample_list_.clear();
    return kGpaStatusOk == gpa_function_table_->GpaBeginSession(gpa_session_id_);
}

bool GpaHelper::OnGpaSessionEnd()
{
    return kGpaStatusOk == gpa_function_table_->GpaEndSession(gpa_session_id_);
}

bool GpaHelper::OnPassStart()
{
    current_pass_index_++;
    sample_counter_ = -1;
    sample_list_.clear();
    bool success = true;

    if (nullptr == gpa_command_list_id_)
    {
        success = kGpaStatusOk == gpa_function_table_->GpaBeginCommandList(
                                      gpa_session_id_, current_pass_index_, GPA_NULL_COMMAND_LIST, kGpaCommandListNone, &gpa_command_list_id_);
    }

    return success;
}

bool GpaHelper::OnPassEnd()
{
    bool success = true;

    if (nullptr != gpa_function_table_ && nullptr != gpa_session_id_)
    {
        success = kGpaStatusOk == gpa_function_table_->GpaEndCommandList(gpa_command_list_id_);
    }

    gpa_command_list_id_ = nullptr;
    return success;
}

void GpaHelper::CheckForPassResults()
{
    if (nullptr != gpa_function_table_ && nullptr != gpa_session_id_)
    {
        GpaStatus status = gpa_function_table_->GpaIsPassComplete(gpa_session_id_, current_pass_index_);
        UNREFERENCED_PARAMETER(status);
        //assert(status == kGpaStatusOk);
    }
}

void GpaHelper::BeginSample()
{
    sample_counter_++;

    if (kGpaStatusOk != gpa_function_table_->GpaBeginSample(sample_counter_, gpa_command_list_id_))
    {
        GpaLogger((GpaLoggingType)kGeneralError, "GpaBeginSample failed.");
    }

    sample_list_.push_back(sample_counter_);
}

void GpaHelper::EndSample()
{
    if (kGpaStatusOk != gpa_function_table_->GpaEndSample(gpa_command_list_id_))
    {
        GpaLogger((GpaLoggingType)kGeneralError, "GpaEndSample failed.");
    }
}

bool GpaHelper::CounterValueCompare(unsigned int profile_set,
                                    unsigned int sample_index,
                                    const char*  counter_name,
                                    GpaFloat64   counter_value,
                                    CompareType  compare_type,
                                    GpaFloat64   compare_value)
{
    bool              return_value = false;
    std::stringstream output_string;
    std::stringstream error_string;
    std::stringstream success_string;
    std::stringstream compare_string;

    output_string << "Profile " << profile_set << ", sample " << sample_index << ": ";

    error_string << "Incorrect value for counter " << counter_name << ". Value is " << counter_value << ". Expected counter to be ";
    success_string << "Counter " << counter_name << " is correct. Value " << counter_value << " is ";

    switch (compare_type)
    {
    case kCompareTypeEqual:
        return_value = counter_value == compare_value;
        compare_string << "equal to " << compare_value;
        break;

    case kCompareTypeGreaterThan:
        return_value = counter_value > compare_value;
        compare_string << "greater than " << compare_value;
        break;

    case kCompareTypeGreaterThanOrEqualTo:
        return_value = counter_value >= compare_value;
        compare_string << "greater than or equal to " << compare_value;
        break;

    case kCompareTypeLessThan:
        return_value = counter_value < compare_value;
        compare_string << "less than " << compare_value;
        break;

    case kCompareTypeLessThanOrEqualTo:
        return_value = counter_value <= compare_value;
        compare_string << "less than or equal to " << compare_value;
        break;
    }

    if (!return_value)
    {
        output_string << error_string.str() << compare_string.str();
        GpaLogger(kGpaLoggingError, output_string.str().c_str());
    }
    else if (confirm_success_)
    {
        output_string << success_string.str() << compare_string.str();
        GpaLogger(kGpaLoggingMessage, output_string.str().c_str());
    }

    return return_value;
}

bool GpaHelper::PrintGpaSampleResults(unsigned int profile_set, bool verify_counters)
{
    GpaUInt32 sample_count         = 0u;
    GpaStatus status               = gpa_function_table_->GpaGetSampleCount(gpa_session_id_, &sample_count);
    bool      success              = kGpaStatusOk == status;
    bool      verification_success = true;

    for (std::vector<unsigned int>::iterator sample_iter = sample_list_.begin(); success == true && sample_iter != sample_list_.end(); ++sample_iter)
    {
        if (success && sample_count == sample_list_.size())
        {
            size_t sample_data_size = 0u;
            success                 = kGpaStatusOk == gpa_function_table_->GpaGetSampleResultSize(gpa_session_id_, *sample_iter, &sample_data_size);

            void* sample_result = malloc(sample_data_size);

            if (nullptr == sample_result)
            {
                success = false;
            }
            else
            {
                GpaStatus sample_result_status = gpa_function_table_->GpaGetSampleResult(gpa_session_id_, *sample_iter, sample_data_size, sample_result);

                if (kGpaStatusErrorTimeout == sample_result_status)
                {
                    GpaLogger(kGpaLoggingError, "Received a timeout when attempting to get sample result.");
                    success = false;
                }
                else if (kGpaStatusOk != sample_result_status)
                {
                    success = false;
                }
                else
                {
                    GpaUInt32 num_enabled_counters = 0;

                    if (kGpaStatusOk != gpa_function_table_->GpaGetNumEnabledCounters(gpa_session_id_, &num_enabled_counters))
                    {
                        success = false;
                    }
                    else
                    {
                        for (GpaUInt32 i = 0; i < num_enabled_counters; i++)
                        {
                            GpaUInt32 enabled_index = 0;
                            success                 = success && kGpaStatusOk == gpa_function_table_->GpaGetEnabledIndex(gpa_session_id_, i, &enabled_index);

                            const char* counter_name = nullptr;
                            success = success && kGpaStatusOk == gpa_function_table_->GpaGetCounterName(gpa_context_id_, enabled_index, &counter_name);

                            if (!is_header_written_)
                            {
                                header_ << counter_name << ",";
                            }

                            GpaUsageType usage_type = kGpaUsageTypeLast;
                            success = success && kGpaStatusOk == gpa_function_table_->GpaGetCounterUsageType(gpa_context_id_, enabled_index, &usage_type);

                            GpaDataType data_type = kGpaDataTypeFloat64;
                            success = success && kGpaStatusOk == gpa_function_table_->GpaGetCounterDataType(gpa_context_id_, enabled_index, &data_type);

                            GpaFloat64 float_result = 0.0f;

                            if (data_type == kGpaDataTypeUint64)
                            {
                                GpaUInt64 result = reinterpret_cast<GpaUInt64*>(sample_result)[i];
                                float_result     = static_cast<GpaFloat64>(result);
                                content_ << result << ",";
                            }
                            else if (data_type == kGpaDataTypeFloat64)
                            {
                                float_result = reinterpret_cast<GpaFloat64*>(sample_result)[i];
                                content_ << float_result << ",";
                            }

                            if (verify_counters)
                            {
                                verification_success = true;
                                std::stringstream error_string;
                                error_string << "Incorrect value for counter ";

                                std::string local_counter_name = "";
                                if (nullptr != counter_name)
                                {
                                    local_counter_name = counter_name;
                                }

                                if (kGpaUsageTypePercentage == usage_type)
                                {
                                    verification_success &=
                                        (CounterValueCompare(profile_set, *sample_iter, counter_name, float_result, kCompareTypeGreaterThanOrEqualTo, 0.0f) &&
                                         CounterValueCompare(profile_set, *sample_iter, counter_name, float_result, kCompareTypeLessThanOrEqualTo, 100.0f));
                                }

                                if (0 == local_counter_name.compare("GPUTime"))
                                {
                                    verification_success &=
                                        CounterValueCompare(profile_set, *sample_iter, counter_name, float_result, kCompareTypeGreaterThan, 0.0f);
                                }
                                else if (0 == local_counter_name.compare("GPUBusy"))
                                {
                                    verification_success &=
                                        (CounterValueCompare(profile_set, *sample_iter, counter_name, float_result, kCompareTypeGreaterThan, 0.0f) &&
                                         CounterValueCompare(profile_set, *sample_iter, counter_name, float_result, kCompareTypeLessThanOrEqualTo, 100.0f));
                                }
                                else if (0 == local_counter_name.compare("VSBusy"))
                                {
                                    verification_success &=
                                        CounterValueCompare(profile_set, *sample_iter, counter_name, float_result, kCompareTypeGreaterThan, 0.0f);
                                }
                                else if (0 == local_counter_name.compare("VSTime"))
                                {
                                    verification_success &=
                                        CounterValueCompare(profile_set, *sample_iter, counter_name, float_result, kCompareTypeGreaterThan, 0.0f);
                                }
                                else if (0 == local_counter_name.compare("PSBusy"))
                                {
                                    verification_success &=
                                        CounterValueCompare(profile_set, *sample_iter, counter_name, float_result, kCompareTypeGreaterThan, 0.0f);
                                }
                                else if (0 == local_counter_name.compare("PSTime"))
                                {
                                    verification_success &=
                                        CounterValueCompare(profile_set, *sample_iter, counter_name, float_result, kCompareTypeGreaterThan, 0.0f);
                                }
                                else if (0 == local_counter_name.compare("VSVerticesIn"))
                                {
                                    verification_success &= CounterValueCompare(profile_set, *sample_iter, counter_name, float_result, kCompareTypeEqual, 3);
                                }
                                else if (app_->IncludeKnownIssues() && 0 == local_counter_name.compare("PSPixelsOut"))
                                {
                                    verification_success &=
                                        CounterValueCompare(profile_set, *sample_iter, counter_name, float_result, kCompareTypeEqual, 180000);
                                }
                                else if (app_->IncludeKnownIssues() && 0 == local_counter_name.compare("PreZSamplesPassing"))
                                {
                                    verification_success &=
                                        CounterValueCompare(profile_set, *sample_iter, counter_name, float_result, kCompareTypeEqual, 180000);
                                }
                                else if (0 == local_counter_name.compare("PrimitivesIn"))
                                {
                                    verification_success &= CounterValueCompare(profile_set, *sample_iter, counter_name, float_result, kCompareTypeEqual, 1);
                                }
                            }
                        }

                        if (counter_data_file_stream_.is_open())
                        {
                            if (!is_header_written_)
                            {
                                counter_data_file_stream_ << "Frame"
                                                          << "," << header_.str() << std::endl;
                                is_header_written_ = true;
                            }

                            counter_data_file_stream_ << frame_counter_ << "," << content_.str() << std::endl;
                            content_.str(std::string());
                            header_.str(std::string());
                        }
                    }
                }

                free(sample_result);
            }
        }
    }

    return success && verification_success;
}

unsigned int GpaHelper::GetPassRequired() const
{
    return num_passes_required_;
}

void GpaHelper::IncrementFrameCounter()
{
    ++frame_counter_;
}

unsigned GpaHelper::GetCurrentFrameCount() const
{
    return frame_counter_;
}

GpaHelper::~GpaHelper()
{
    gpa_log_file_stream_.close();
    counter_data_file_stream_.close();
    if (gpa_function_table_ != nullptr)
    {
        gpa_function_table_->GpaDestroy();
    }

    if (app_ != nullptr)
    {
        delete app_;
        app_ = nullptr;
    }
}

GpaHelper::GpaHelper()
    : has_error_occurred_(false)
    , num_errors_occurred_(0)
    , app_(nullptr)
    , gpa_function_table_(nullptr)
    , gpa_hw_generation_(kGpaHwGenerationNone)
    , gpa_context_id_(nullptr)
    , gpa_session_id_(nullptr)
    , gpa_command_list_id_(nullptr)
    , num_passes_required_(0u)
    , current_pass_index_(0u)
    , confirm_success_(false)
{
}

void GpaHelper::InitializeIO()
{
#ifdef _WIN32
    wchar_t module_path[GPA_MAX_PATH];
    ::GetModuleFileNameW(NULL, module_path, _countof(module_path));

    std::wstring module_string(module_path);
    size_t       last_slash_position = module_string.find_last_of('\\');

    std::wstring executable_path = std::wstring(module_string.begin(), module_string.begin() + (last_slash_position + 1));

    std::string utf8_executable_path = wide_to_utf8_converter(executable_path);

#else
    int  len;
    char module_path[GPA_MAX_PATH];
    len = readlink("/proc/self/exe", module_path, GPA_MAX_PATH - 1);

    if (len != -1)
    {
        module_path[len] = '\0';
    }

    std::string module_string(module_path);
    size_t      last_slash_position = module_string.find_last_of('/');

    std::string executable_path(module_path);

    if (std::string::npos != last_slash_position)
    {
        executable_path = std::string(module_string.begin(), module_string.begin() + (last_slash_position + 1));
    }

    std::string utf8_executable_path;
    utf8_executable_path.append(executable_path.begin(), executable_path.end());
#endif

    gpa_counter_file_name_ = std::string(utf8_executable_path.begin(), utf8_executable_path.end()).append(app_->Datafile());
    gpa_log_file_name_ = std::string(utf8_executable_path.begin(), utf8_executable_path.end()).append(app_->Logfile());
    std::remove(gpa_counter_file_name_.c_str());
    std::remove(gpa_log_file_name_.c_str());
    counter_data_file_stream_.open(gpa_counter_file_name_.c_str(), std::ios_base::out | std::ios_base::app);
}
