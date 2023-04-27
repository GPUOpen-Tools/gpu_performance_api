//==============================================================================
// Copyright (c) 2018-2020 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief CL GPA Implementation
//==============================================================================

#include <assert.h>

#include <CL/cl.h>

#include <ADLUtil.h>
#include <DeviceInfoUtils.h>

#include "cl_rt_module_loader.h"

#include "cl_gpa_implementor.h"
#include "cl_gpa_context.h"
#include "cl_perf_counter_amd_extension.h"

#include "gpa_counter_generator_cl.h"
#include "gpa_counter_scheduler_cl.h"

IGpaImplementor*             gpa_imp = ClGpaImplementor::Instance();
static GpaCounterGeneratorCl counter_generator_cl;  ///< static instance of CL generator
static GpaCounterSchedulerCl counter_scheduler_cl;  ///< static instance of CL scheduler

GpaApiType ClGpaImplementor::GetApiType() const
{
    return kGpaApiOpencl;
}

bool ClGpaImplementor::GetHwInfoFromApi(const GpaContextInfoPtr context_info, GpaHwInfo& hw_info) const
{
    bool is_success = true;

    OpenCLModule* ocl_module = ClRuntimeModuleLoader::Instance()->GetApiRuntimeModule();

    if (nullptr == ocl_module)
    {
        GPA_LOG_ERROR("OpenCL runtime module is NULL.");
        is_success = false;
    }
    else
    {
        cl_command_queue cmd_queue = static_cast<cl_command_queue>(context_info);

        cl_device_id device;

        // get device from the command queue
        if (CL_SUCCESS != ocl_module->GetCommandQueueInfo(cmd_queue, CL_QUEUE_DEVICE, sizeof(cl_device_id), &device, nullptr))
        {
            GPA_LOG_ERROR("Unable to get device from command queue.");
            is_success = false;
        }
        else
        {
            cl_device_type device_type;

            if (CL_SUCCESS != ocl_module->GetDeviceInfo(device, CL_DEVICE_TYPE, sizeof(cl_device_type), &device_type, nullptr) ||
                CL_DEVICE_TYPE_GPU != device_type)
            {
                GPA_LOG_ERROR("Unable to get device info or the device is not a GPU device.");
                is_success = false;
            }
            else
            {
                size_t      device_name_size = 0;
                std::string device_name_str;

                bool device_name_valid = CL_SUCCESS == ocl_module->GetDeviceInfo(device, CL_DEVICE_NAME, 0, nullptr, &device_name_size);

                if (!device_name_valid)
                {
                    GPA_LOG_ERROR("Unable to get device name.");
                    is_success = false;
                }
                else
                {
                    char* device_name = new char[device_name_size];

                    if (nullptr == device_name)
                    {
                        GPA_LOG_ERROR("Unable to allocate memory for the device name.");
                        return false;
                    }

                    device_name_valid = CL_SUCCESS == ocl_module->GetDeviceInfo(device, CL_DEVICE_NAME, device_name_size, device_name, &device_name_size);

                    if (!device_name_valid)
                    {
                        GPA_LOG_ERROR("Unable to get device name.");
                        is_success = false;
                    }
                    else
                    {
                        device_name_str.assign(device_name);
                    }

                    delete[] device_name;

                    if (device_name_valid)
                    {
                        std::stringstream message;
                        message << "Device name from Queue: " << device_name_str << ".";
                        GPA_LOG_DEBUG_MESSAGE(message.str().c_str());

                        bool        board_name_valid = CL_SUCCESS == ocl_module->GetDeviceInfo(device, CL_DEVICE_BOARD_NAME_AMD, 0, nullptr, &device_name_size);
                        std::string board_name_str;

                        if (board_name_valid)
                        {
                            char* board_name = new char[device_name_size];

                            if (nullptr == board_name)
                            {
                                GPA_LOG_ERROR("Unable to allocate memory for the board name.");
                                return false;
                            }

                            board_name_valid =
                                CL_SUCCESS == ocl_module->GetDeviceInfo(device, CL_DEVICE_BOARD_NAME_AMD, device_name_size, board_name, &device_name_size);

                            if (board_name_valid)
                            {
                                board_name_str.assign(board_name);
                            }

                            delete[] board_name;
                        }

                        std::vector<GDT_GfxCardInfo> card_list_from_name;
                        bool card_found_by_name = AMDTDeviceInfoUtils::Instance()->GetAllCardsWithName(device_name_str.c_str(), card_list_from_name);
                        bool card_found         = false;
                        bool precise_card_found = false;

                        cl_uint pcie_device_id   = 0;
                        bool    is_pcie_id_valid = false;

                        if (CL_SUCCESS == ocl_module->GetDeviceInfo(device, CL_DEVICE_PCIE_ID_AMD, sizeof(cl_uint), &pcie_device_id, nullptr) &&
                            0 != pcie_device_id)
                        {
                            // the CL_DEVICE_ID_AMD query can return a bogus device id in some drivers
                            std::vector<GDT_GfxCardInfo> card_list_device_id;
                            is_pcie_id_valid = AMDTDeviceInfoUtils::Instance()->GetAllCardsWithDeviceId(pcie_device_id, card_list_device_id);

                            if (is_pcie_id_valid)
                            {
                                hw_info.SetDeviceId(pcie_device_id);
                                hw_info.SetRevisionId(REVISION_ID_ANY);

                                for (auto card = card_list_device_id.begin(); card != card_list_device_id.end() && !precise_card_found; ++card)
                                {
                                    card_found = true;

                                    if (board_name_valid)
                                    {
                                        if ((0 == board_name_str.compare(card->m_szMarketingName)) && (0 == device_name_str.compare(card->m_szCALName)))
                                        {
                                            hw_info.SetRevisionId(static_cast<GpaUInt32>(card->m_revID));
                                            precise_card_found = true;
                                        }
                                    }
                                }
                            }

                            if (!precise_card_found && card_found_by_name)
                            {
                                for (auto card = card_list_from_name.begin(); card != card_list_from_name.end() && !precise_card_found; ++card)
                                {
                                    if (is_pcie_id_valid && card->m_deviceID != pcie_device_id)
                                    {
                                        // skip cards where the pcie device id is incorrect
                                        continue;
                                    }

                                    hw_info.SetDeviceId(static_cast<GpaUInt32>(card->m_deviceID));
                                    hw_info.SetRevisionId(static_cast<GpaUInt32>(card->m_revID));
                                    card_found = true;

                                    if (board_name_valid)
                                    {
                                        if (0 == board_name_str.compare(card->m_szMarketingName))
                                        {
                                            precise_card_found = true;
                                        }
                                    }
                                }
                            }

                            if (!card_found)
                            {
                                GPA_LOG_ERROR("Unable to determine device id.");
                                is_success = false;
                            }

                            if (!precise_card_found)
                            {
                                GPA_LOG_MESSAGE("Unable to determine precise device. Best guess device identified.");
                            }
                        }
                        else
                        {
                            // unable to get device id from OCL runtime -- just use  first item in cardListFromName
                            if (card_found_by_name)
                            {
                                GPA_LOG_MESSAGE("Unable to determine precise device. Best guess device identified.");
                                hw_info.SetDeviceId(static_cast<GpaUInt32>(card_list_from_name[0].m_deviceID));
                                hw_info.SetRevisionId(static_cast<GpaUInt32>(card_list_from_name[0].m_revID));
                            }
                            else
                            {
                                GPA_LOG_ERROR("Unable to determine device id.");
                                is_success = false;
                            }
                        }
                    }

                    if (is_success)
                    {
                        hw_info.SetDeviceName(device_name_str.c_str());

                        cl_uint vendor_id;

                        if (CL_SUCCESS != ocl_module->GetDeviceInfo(device, CL_DEVICE_VENDOR_ID, sizeof(cl_uint), &vendor_id, nullptr))
                        {
                            GPA_LOG_ERROR("Unable to get Vendor ID.");
                            is_success = false;
                        }

                        hw_info.SetVendorId(vendor_id);

#ifdef WIN32

                        if (kNvidiaVendorId == vendor_id)
                        {
                            hw_info.SetHwGeneration(GDT_HW_GENERATION_NVIDIA);
                        }
                        else if (kIntelVendorId == vendor_id)
                        {
                            hw_info.SetHwGeneration(GDT_HW_GENERATION_INTEL);
                        }
                        else

#endif
                        {
                            hw_info.UpdateDeviceInfoBasedOnDeviceId();
                        }

                        cl_uint num_compute_units = 0;

                        if (CL_SUCCESS != ocl_module->GetDeviceInfo(device, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(cl_uint), &num_compute_units, nullptr))
                        {
                            GPA_LOG_ERROR("Unable to get number of compute units.");
                            is_success = false;
                        }
                        else
                        {
                            GDT_HW_GENERATION generation;

                            if (hw_info.GetHwGeneration(generation) && GDT_HW_GENERATION_GFX10 <= generation)
                            {
                                // Starting on GFX10, the OCL runtime reports the number of WGPs rather than number of CUs for the CL_DEVICE_MAX_COMPUTE_UNITS query
                                num_compute_units *= 2;
                            }

                            hw_info.SetNumberCus(static_cast<size_t>(num_compute_units));

                            cl_uint num_simd_per_cu = 0;

                            if (CL_SUCCESS !=
                                ocl_module->GetDeviceInfo(device, CL_DEVICE_SIMD_PER_COMPUTE_UNIT_AMD, sizeof(cl_uint), &num_simd_per_cu, nullptr))
                            {
                                GPA_LOG_ERROR("Unable to get number of SIMDS per compute unit.");
                                is_success = false;
                            }
                            else
                            {
                                hw_info.SetNumberSimds(static_cast<size_t>(num_compute_units) * num_simd_per_cu);
                            }
                        }
                    }
                }
            }
        }
    }

    return is_success;
}

bool ClGpaImplementor::VerifyApiHwSupport(const GpaContextInfoPtr context_info, const GpaHwInfo& hw_info) const
{
    UNREFERENCED_PARAMETER(context_info);

    bool is_supported = false;

    GDT_HW_GENERATION generation = GDT_HW_GENERATION_NONE;

    if (hw_info.GetHwGeneration(generation) == false)
    {
        GPA_LOG_ERROR("Unable to get hardware generation.");
    }
    else
    {
        is_supported = true;
    }

    if (generation == GDT_HW_GENERATION_GFX11)
    {
        unsigned int   major_ver     = 0;
        unsigned int   minor_ver     = 0;
        unsigned int   sub_minor_ver = 0;
        ADLUtil_Result adl_result    = AMDTADLUtils::Instance()->GetDriverVersion(major_ver, minor_ver, sub_minor_ver);
        AMDTADLUtils::DeleteInstance();

        if ((ADL_SUCCESS == adl_result || ADL_WARNING == adl_result))
        {
            // 22.40.43 is the first driver that properly supports perf counters on GFX11.
            static const unsigned int kMinMajorVersionForGfx11Support = 22;
            static const unsigned int kMinMinorVersionForGfx11Support = 40;
            static const unsigned int kMinSubMinorVersionForGfx11Support = 43;

            if (major_ver < kMinMajorVersionForGfx11Support || (major_ver == kMinMajorVersionForGfx11Support && minor_ver < kMinMinorVersionForGfx11Support) ||
                (major_ver == kMinMajorVersionForGfx11Support && minor_ver == kMinMinorVersionForGfx11Support && sub_minor_ver < kMinSubMinorVersionForGfx11Support))
            {
                GPA_LOG_ERROR("Known Issue: This driver version does not properly support GPUPerfAPI on this hardware.");
                is_supported = false;
            }
        }
    }

    return is_supported;
}

IGpaContext* ClGpaImplementor::OpenApiContext(GpaContextInfoPtr context_info, GpaHwInfo& hw_info, GpaOpenContextFlags flags)
{
    ClGpaContext* ret_gpa_context = nullptr;

    cl_command_queue cl_cmd_queue = static_cast<cl_command_queue>(context_info);

    ClGpaContext* cl_gpa_context = new (std::nothrow) ClGpaContext(cl_cmd_queue, hw_info, flags);

    if (nullptr == cl_gpa_context)
    {
        GPA_LOG_ERROR("Unable to allocate memory for the context.");
    }
    else
    {
        OpenCLModule* ocl_module = ClRuntimeModuleLoader::Instance()->GetApiRuntimeModule();

        cl_int cl_status = CL_SUCCESS;

        if (nullptr == ocl_module)
        {
            GPA_LOG_ERROR("OpenCL runtime module is NULL.");
        }
        else
        {
            cl_device_id device_id;
            // get device from the command queue and store it
            cl_status = ocl_module->GetCommandQueueInfo(cl_cmd_queue, CL_QUEUE_DEVICE, sizeof(cl_device_id), &device_id, nullptr);

            if (CL_SUCCESS == cl_status)
            {
                // initialize AMD perf counter's extension
                if (!init_perf_counter_amd_extension_)
                {
                    cl_platform_id platform;

                    cl_status = ocl_module->GetDeviceInfo(device_id, CL_DEVICE_PLATFORM, sizeof(cl_platform_id), &platform, nullptr);

                    if (CL_SUCCESS != cl_status)
                    {
                        GPA_LOG_ERROR("Unable to get platform from device.");
                    }
                    else if (!InitPerfCounterAmdExtension(platform))
                    {
                        GPA_LOG_ERROR("Unable to initialize the PerfCounter AMD Extension.");
                    }
                    else
                    {
                        init_perf_counter_amd_extension_ = true;
                    }
                }

                if (init_perf_counter_amd_extension_)
                {
                    if (cl_gpa_context->Initialize(device_id))
                    {
                        ret_gpa_context = cl_gpa_context;
                    }
                    else
                    {
                        delete cl_gpa_context;
                        GPA_LOG_ERROR("Unable to open a context.");
                    }
                }
            }
            else
            {
                GPA_LOG_ERROR("Unable to query CL device from CL command queue.");
            }
        }
    }

    return ret_gpa_context;
}

bool ClGpaImplementor::CloseApiContext(GpaDeviceIdentifier device_identifier, IGpaContext* context)
{
    assert(nullptr != device_identifier);
    assert(nullptr != context);

    if (nullptr != context)
    {
        delete reinterpret_cast<ClGpaContext*>(context);
        context = nullptr;
    }

    return (nullptr == context) && (nullptr != device_identifier);
}

GpaDeviceIdentifier ClGpaImplementor::GetDeviceIdentifierFromContextInfo(GpaContextInfoPtr context_info) const
{
    return context_info;
}
