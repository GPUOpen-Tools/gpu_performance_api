//==============================================================================
// Copyright (c) 2018-2023 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Vulkan Color Cube Sample.
//==============================================================================

#include "examples/vulkan/vk_color_cube/vk_color_cube.h"

#include <assert.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(VK_USE_PLATFORM_XCB_KHR) || defined(VK_USE_PLATFORM_XLIB_KHR)
#include <X11/Xutil.h>
#include <xcb/xcb.h>
#include <dlfcn.h>
#include <unistd.h>
#endif

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <thread>
#include <vector>

#include "gpu_performance_api/gpu_perf_api_vk.h"

#include "examples/vulkan/vk_color_cube/vk_util.h"

GpaApiManager*    GpaApiManager::gpa_api_manager_ = nullptr;
GpaFuncTableInfo* gpa_function_table_info         = nullptr;
std::string       GpaHelper::gpa_log_file_name    = AMDT_PROJECT_NAME "_gpa_log.txt";
std::string       GpaHelper::csv_file_name        = AMDT_PROJECT_NAME "_counter_data.csv";
std::fstream      GpaHelper::gpa_log_file_stream;
bool              GpaHelper::gpa_any_errors_logged = false;
int               GpaHelper::gpa_num_errors_logged = 0;
bool              GpaHelper::include_known_issues = false;

AMDVulkanDemo::AMDVulkanDemo(const std::string app_name, gpa_example::CmdlineParser& cmdline_parser)
    : gpa_example::GpaSampleApp(app_name, cmdline_parser)
    ,
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    hInstance_(nullptr)
    , hWindow_(nullptr)
    ,
#elif defined(VK_USE_PLATFORM_XCB_KHR)
    display_(nullptr)
    , xcb_conntection_(nullptr)
    , xcb_screen_(nullptr)
    , xcb_atom_delete_window_(nullptr)
    ,
#endif
    vk_instance_(VK_NULL_HANDLE)
    , default_physical_device_(VK_NULL_HANDLE)
    , vk_device_(VK_NULL_HANDLE)
    , vk_queue_(VK_NULL_HANDLE)
    , vk_surface_(VK_NULL_HANDLE)
    , queue_family_index_graphics_(0)
    , queue_family_index_present_(0)
    , vk_swap_chain_(VK_NULL_HANDLE)
    , vk_render_pass_initial_(VK_NULL_HANDLE)
    , vk_render_pass_mid_(VK_NULL_HANDLE)
    , vk_render_pass_final_(VK_NULL_HANDLE)
    , vk_pipeline_layout_(VK_NULL_HANDLE)
    , vk_pipeline_(VK_NULL_HANDLE)
    , vk_command_pool_(VK_NULL_HANDLE)
    , vertex_shader_module_(VK_NULL_HANDLE)
    , fragment_shader_module_(VK_NULL_HANDLE)
    , vk_semaphore_acquired_swapchain_image_(VK_NULL_HANDLE)
    , vk_sempahore_fineshed_rendering_(VK_NULL_HANDLE)
    , vk_debug_report_callback_(VK_NULL_HANDLE)
    , gpa_context_id_(nullptr)
    , gpa_session_id_(nullptr)
    , required_pass_count_(0)
    , num_frames_rendered_(0)
    , print_debug_output_(false)
    , print_gpa_counter_info_(false)
    , exit_after_profile_(false)
    , initialized_(false)
    , exit_(false)
    , nogpa_(false)
{
    cmdline_parser_.AddArg("--nogpa", &nogpa_, gpa_example::ArgType::kArgTypeBool, "Do not use GPUPerfAPI to collect performance counters");
    cmdline_parser_.AddArg("--exitafterprofile",
                           &exit_after_profile_,
                           gpa_example::ArgType::kArgTypeBool,
                           "Application will exit automatically after collecting performance counters");
    cmdline_parser_.AddArg("--verbose", &print_debug_output_, gpa_example::ArgType::kArgTypeBool, "Produce verbose output");
    cmdline_parser_.AddArg(
        "--printcounterinfo", &print_gpa_counter_info_, gpa_example::ArgType::kArgTypeBool, "Output information about available performance counters");

    physical_device_properties_        = {};
    physical_device_features_          = {};
    physical_device_memory_properties_ = {};
    vk_surface_format_                 = {};
    vk_present_mode_                   = VK_PRESENT_MODE_FIFO_KHR;
    vk_surface_capabilities_           = {};
    swap_chain_image_extent_           = {};

    // Specifically setting this to 0 because it will be used to query a queue,
    // and the first queue available (ie: at the 0th index) is the desired one.
    queue_index_ = 0;

    required_instance_extensions_ = {
        VK_KHR_SURFACE_EXTENSION_NAME,
#ifdef ANDROID
        VK_KHR_ANDROID_SURFACE_EXTENSION_NAME,
#endif
        VK_EXT_DEBUG_REPORT_EXTENSION_NAME,
        AMD_GPA_REQUIRED_INSTANCE_EXTENSION_NAME_LIST,
#if defined(VK_USE_PLATFORM_WIN32_KHR)
        VK_KHR_WIN32_SURFACE_EXTENSION_NAME
#elif defined(VK_USE_PLATFORM_XCB_KHR)
        VK_KHR_XCB_SURFACE_EXTENSION_NAME
#endif
    };

    required_device_extensions_ = {VK_KHR_SWAPCHAIN_EXTENSION_NAME, AMD_GPA_REQUIRED_DEVICE_EXTENSION_NAME_LIST};
    optional_device_extensions_ = {VK_KHR_SWAPCHAIN_EXTENSION_NAME, AMD_GPA_REQUIRED_DEVICE_EXTENSION_NAME_LIST, AMD_GPA_OPTIONAL_DEVICE_EXTENSION_NAME_LIST};
}

AMDVulkanDemo* AMDVulkanDemo::amd_vulkan_demo_ = nullptr;

AMDVulkanDemo::~AMDVulkanDemo()
{
    Destroy();
}

bool AMDVulkanDemo::Exit() const
{
    return exit_;
}

void AMDVulkanDemo::Exit(bool exit)
{
    exit_ = exit;
}

bool AMDVulkanDemo::Initialized() const
{
    return initialized_;
}

#ifdef VK_USE_PLATFORM_WIN32_KHR
void AMDVulkanDemo::CreateWindowWin32(WNDPROC demo_window_procedure)
{
    if (hWindow_ != nullptr)
    {
        AMDVulkanDemoVkUtils::Log("WARNING: calling CreateWindowWin32 more than once!");
    }

    WNDCLASSEXW window_class;
    memset(&window_class, 0, sizeof(WNDCLASSEXW));
    window_class.cbSize        = sizeof(WNDCLASSEXW);
    window_class.style         = CS_HREDRAW | CS_VREDRAW;
    window_class.hInstance     = hInstance_;
    window_class.lpfnWndProc   = demo_window_procedure;
    window_class.lpszClassName = L"GPA Demo Window Class";
    window_class.hCursor       = LoadCursor(nullptr, IDC_ARROW);
    window_class.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);

    if (::RegisterClassExW(&window_class))
    {
        hWindow_ = ::CreateWindowExW(0,
                                     window_class.lpszClassName,
                                     kLongName.c_str(),
                                     WS_OVERLAPPED | WS_VISIBLE | WS_SYSMENU,
                                     CW_USEDEFAULT,
                                     CW_USEDEFAULT,
                                     static_cast<int>(kDefaultWindowWidth),
                                     static_cast<int>(kDefaultWindowHeight),
                                     nullptr,
                                     nullptr,
                                     hInstance_,
                                     nullptr);
    }
}

void AMDVulkanDemo::InitializeWindowWin32(HINSTANCE instance_handle, WNDPROC demo_window_message_procedure, int cmd_show)
{
    if (hInstance_ == nullptr)
    {
        hInstance_ = instance_handle;

        if (hWindow_ == nullptr)
        {
            CreateWindowWin32(demo_window_message_procedure);

            if (hWindow_ != nullptr)
            {
                SetWindowLongPtrW(hWindow_, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

                if (FALSE == ShowWindow(hWindow_, cmd_show))
                {
                    hWindow_ = nullptr;
                }
            }
        }
    }
}

HWND AMDVulkanDemo::GetWindowWin32() const
{
    return hWindow_;
}

#elif defined(VK_USE_PLATFORM_XCB_KHR)

xcb_connection_t* AMDVulkanDemo::InitializeWindowXcb()
{
    uint32_t window_flags;
    uint32_t window_list[32];

    const xcb_setup_t*    xcb_setup = nullptr;
    xcb_screen_iterator_t screen_iter;
    int                   screen_index = 0;

    xcb_conntection_ = xcb_connect(NULL, &screen_index);

    if (xcb_connection_has_error(xcb_conntection_) > 0)
    {
        AMDVulkanDemoVkUtils::Log("ERROR: Cannot find a compatible Vulkan installable client driver (ICD).");
        return nullptr;
    }

    xcb_setup   = xcb_get_setup(xcb_conntection_);
    screen_iter = xcb_setup_roots_iterator(xcb_setup);

    while (screen_index-- > 0)
    {
        xcb_screen_next(&screen_iter);
    }

    xcb_screen_ = screen_iter.data;

    xcb_window_ = xcb_generate_id(xcb_conntection_);

    window_flags   = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
    window_list[0] = xcb_screen_->black_pixel;
    window_list[1] = XCB_EVENT_MASK_KEY_RELEASE | XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_STRUCTURE_NOTIFY;

    xcb_create_window(xcb_conntection_,
                      XCB_COPY_FROM_PARENT,
                      xcb_window_,
                      xcb_screen_->root,
                      0,
                      0,
                      kDefaultWindowWidth,
                      kDefaultWindowHeight,
                      0,
                      XCB_WINDOW_CLASS_INPUT_OUTPUT,
                      xcb_screen_->root_visual,
                      window_flags,
                      window_list);

    // Connect Window Management events to replies that can be compared against.
    xcb_intern_atom_cookie_t protocol_cookie      = xcb_intern_atom(xcb_conntection_, 1, 12, "WM_PROTOCOLS");
    xcb_intern_atom_cookie_t delete_window_cookie = xcb_intern_atom(xcb_conntection_, 0, 16, "WM_DELETE_WINDOW");

    xcb_intern_atom_reply_t* protocols_reply = xcb_intern_atom_reply(xcb_conntection_, protocol_cookie, 0);

    xcb_atom_delete_window_ = xcb_intern_atom_reply(xcb_conntection_, delete_window_cookie, 0);

    xcb_change_property(xcb_conntection_, XCB_PROP_MODE_REPLACE, xcb_window_, protocols_reply->atom, 4, 32, 1, &xcb_atom_delete_window_->atom);
    free(protocols_reply);

    // Display the window
    xcb_map_window(xcb_conntection_, xcb_window_);

    // Force the x/y coordinates to 100,100 results are identical in consecutive runs
    const uint32_t coords[] = {100, 100};
    xcb_configure_window(xcb_conntection_, xcb_window_, XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_Y, coords);

    return xcb_conntection_;
}
#endif  // VK_USE_PLATFORM_XCB_KHR

VkShaderModule AMDVulkanDemo::LoadShader(const char* file_name)
{
    std::vector<char> shader_bytes;
#ifdef ANDROID
    std::string shader_path = file_name;
    if (nullptr != native_activity_)
    {
        AAsset* shader_file = AAssetManager_open(native_activity_->assetManager, shader_path.c_str(), AASSET_MODE_BUFFER);

        if (nullptr != shader_file)
        {
            size_t shader_byte_code_len = AAsset_getLength(shader_file);
            shader_bytes.resize(shader_byte_code_len);

            if (shader_byte_code_len == AAsset_read(shader_file, shader_bytes.data(), shader_byte_code_len))
            {
                AMDVulkanDemoVkUtils::Log("Shader successfully loaded.");
            }

            AAsset_close(shader_file);
        }
    }
    else
    {
        AMDVulkanDemoVkUtils::Log("No native activity.");
    }

#else

    std::string shader_path = gpu_perf_api_helper_.GetExecutablePath();
    shader_path.append(file_name);
    std::ifstream shader_file(shader_path, std::ios::binary | std::ios::in);

    if (!shader_file.is_open())
    {
        AMDVulkanDemoVkUtils::Log("ERROR: Failed to read shader file: '%s'.", shader_path.c_str());
        return VK_NULL_HANDLE;
    }

    shader_file.seekg(0, shader_file.end);
    size_t length = static_cast<size_t>(shader_file.tellg());
    shader_file.seekg(0);
    shader_bytes.resize(length);
    shader_file.read(shader_bytes.data(), length);
    shader_file.close();

#endif

    VkShaderModuleCreateInfo shader_module_create_info = {};
    shader_module_create_info.sType                    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    shader_module_create_info.pNext                    = nullptr;
    shader_module_create_info.codeSize                 = shader_bytes.size();
    shader_module_create_info.pCode                    = reinterpret_cast<const uint32_t*>(shader_bytes.data());

    VkShaderModule shader_module;
    VkResult       create_shader_module_result = _vkCreateShaderModule(vk_device_, &shader_module_create_info, nullptr, &shader_module);

    if (create_shader_module_result != VK_SUCCESS)
    {
        AMDVulkanDemoVkUtils::Log("ERROR: Failed to create shader module for '%s'.", shader_path.c_str());
        return VK_NULL_HANDLE;
    }

    return shader_module;
}

bool AMDVulkanDemo::InitializeGpa()
{
#ifndef ANDROID
    if (!gpu_perf_api_helper_.Load())
    {
        AMDVulkanDemoVkUtils::Log("ERROR: Failed to Load GPA library.");
        return false;
    }

    if (gpu_perf_api_helper_.IsLoaded())
    {
        GpaLoggingType gpa_log_types = kGpaLoggingError;

        if (ConfirmSuccess())
        {
            // Only log message types if confirm_success_ is enabled, because GPA will log a confirmation message
            // that the logging callback was registered, and we don't want to output a log if --verify was enabled
            // but not --confirmsuccess.
            gpa_log_types = kGpaLoggingErrorAndMessage;
        }

        GpaStatus status_register_callback =
            gpu_perf_api_helper_.gpa_function_table_->GpaRegisterLoggingCallback(gpa_log_types, gpu_perf_api_helper_.gpaLoggingCallback);
        if (status_register_callback != kGpaStatusOk)
        {
            gpu_perf_api_helper_.LogStatus(status_register_callback, "ERROR: Failed to register GPA logging callback.");
            return false;
        }

        GpaStatus status_gpa_initialize = gpu_perf_api_helper_.gpa_function_table_->GpaInitialize(kGpaInitializeDefaultBit);

        if (status_gpa_initialize != kGpaStatusOk)
        {
            gpu_perf_api_helper_.LogStatus(status_gpa_initialize, "ERROR: Failed to initialize GPA.");
            return false;
        }

        std::remove(gpu_perf_api_helper_.GetCSVFileName().c_str());
        return true;
    }

#else
#ifdef _DEBUG
    void* gpa_lib = dlopen("libGPUPerfAPIVK-d.so", RTLD_NOW);
#else
    void* gpa_lib = dlopen("libGPUPerfAPIVK.so", RTLD_NOW);
#endif
    if (nullptr == gpa_lib)
    {
        AMDVulkanDemoVkUtils::Log("ERROR: Failed to dlopen the GPA vulkan library.");
        return false;
    }

    GpaGetFuncTablePtrType get_function_table_type = (GpaGetFuncTablePtrType)(dlsym(gpa_lib, "GpaGetFuncTable"));
    if (nullptr == get_function_table_type)
    {
        AMDVulkanDemoVkUtils::Log("ERROR: Unable to get GpaGetFuncTable pointer from GPA vulkan library.");
        return false;
    }

    GpaFunctionTable* gpa_function_table = new (std::nothrow) GpaFunctionTable();
    if (nullptr == gpa_function_table)
    {
        AMDVulkanDemoVkUtils::Log("ERROR: Out of memory.");
        return false;
    }

    gpa_function_table->major_version = GPA_FUNCTION_TABLE_MAJOR_VERSION_NUMBER;
    gpa_function_table->minor_version = GPA_FUNCTION_TABLE_MINOR_VERSION_NUMBER;

    GpaStatus status = get_function_table_type((void*)(gpa_function_table));
    if (kGpaStatusOk != status)
    {
        AMDVulkanDemoVkUtils::Log("ERROR: GpaGetFuncTable failed with status %d.", status);
        delete gpa_function_table;
        return false;
    }

    gpu_perf_api_helper_.gpa_function_table_ = gpa_function_table;

    // Register our logging callback function
    GpaLoggingType gpa_log_types = kGpaLoggingError;
    if (ConfirmSuccess())
    {
        // Only log message types if confirm_success_ is enabled, because GPA will log a confirmation message
        // that the logging callback was registered, and we don't want to output a log if --verify was enabled
        // but not --confirmsuccess.
        gpa_log_types = kGpaLoggingErrorAndMessage;
    }

    status = gpu_perf_api_helper_.gpa_function_table_->GpaRegisterLoggingCallback(gpa_log_types, gpu_perf_api_helper_.gpaLoggingCallback);
    if (status != kGpaStatusOk)
    {
        gpu_perf_api_helper_.LogStatus(status, "ERROR: Failed to register GPA logging callback.");
        return false;
    }

    return true;
#endif

    return false;
}

bool AMDVulkanDemo::InitializeVulkan()
{
    // At a high level, there is the concept of a Vulkan Instance (VkInstance) which is essentially
    // an instance of the Vulkan API. The instance can expose extensions and layers that are generic to
    // any Vulkan implementation (driver/hardware), such as validation layers / object trackers / CPU
    // profilers / debug reporting / etc; and also extensions and layers that are platform-specific
    // such as WIN32 Surfaces, XLIB Surfaces, etc.
    //
    // In order to render to a window on each platform, the corresponding instance extensions must be available.
    // The specific device also needs to support the swapchain extension.

#ifdef ANDROID
    InitializeGpa();
#endif

    if (!AMDVulkanDemoVkUtils::InitVulkanModule())
    {
        return false;
    }

    uint32_t instance_layer_count             = 0;
    VkResult instance_layer_properties_result = _vkEnumerateInstanceLayerProperties(&instance_layer_count, NULL);

    if (instance_layer_properties_result == VK_SUCCESS && instance_layer_count > 0)
    {
        std::vector<VkLayerProperties> instanceLayerProperties;
        instanceLayerProperties.resize(instance_layer_count);
        instance_layer_properties_result = _vkEnumerateInstanceLayerProperties(&instance_layer_count, instanceLayerProperties.data());

        if (instance_layer_properties_result == VK_SUCCESS && print_debug_output_)
        {
            for (uint32_t i = 0; i < instance_layer_count; ++i)
            {
                AMDVulkanDemoVkUtils::Log("Instance Layer %d: '%s'.", i, instanceLayerProperties[i].layerName);
            }
        }
    }

    uint32_t    instance_extension_count             = 0;
    const char* layer_name                           = NULL;
    VkResult    instance_extension_properties_result = _vkEnumerateInstanceExtensionProperties(layer_name, &instance_extension_count, NULL);

    if (instance_extension_properties_result != VK_SUCCESS || instance_extension_count == 0)
    {
        AMDVulkanDemoVkUtils::Log("WARNING: No instance extension properties are available.");
    }
    else
    {
        std::vector<VkExtensionProperties> instance_extension_properties;
        instance_extension_properties.resize(instance_extension_count);
        instance_extension_properties_result =
            _vkEnumerateInstanceExtensionProperties(layer_name, &instance_extension_count, instance_extension_properties.data());

        if (instance_extension_properties_result != VK_SUCCESS)
        {
            AMDVulkanDemoVkUtils::Log("ERROR: Failed to get instance extension properties.");
        }
        else
        {
            // Store and print extension names.
            for (uint32_t i = 0; i < instance_extension_count; ++i)
            {
                AddSupportedInstanceExtension(instance_extension_properties[i].extensionName);

                if (print_debug_output_)
                {
                    AMDVulkanDemoVkUtils::Log("Instance Extension %d: '%s'.", i, instance_extension_properties[i].extensionName);
                }
            }

            // Report error if required extension not available.
            bool missing_required_extensions = false;

            for (uint32_t r = 0; r < required_instance_extensions_.size(); ++r)
            {
                if (!IsInstanceExtensionSupported(required_instance_extensions_[r]))
                {
                    AMDVulkanDemoVkUtils::Log("ERROR: Required Instance extension '%s' is not available.", required_instance_extensions_[r]);
                    missing_required_extensions = true;
                }
            }

            if (missing_required_extensions)
            {
                return false;
            }
        }
    }

    std::vector<const char*> layers;

    bool enable_validation = false;

    if (enable_validation)
    {
        layers.push_back("VK_LAYER_KHRONOS_validation");
    };

    VkApplicationInfo app_info  = {};
    app_info.sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    app_info.pNext              = nullptr;
    app_info.pApplicationName   = kShortName.c_str();
    app_info.applicationVersion = 1;
    app_info.apiVersion         = VK_API_VERSION_1_0;

    VkInstanceCreateInfo instance_create_info    = {};
    instance_create_info.sType                   = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instance_create_info.pNext                   = nullptr;
    instance_create_info.pApplicationInfo        = &app_info;
    instance_create_info.enabledExtensionCount   = static_cast<uint32_t>(required_instance_extensions_.size());
    instance_create_info.ppEnabledExtensionNames = required_instance_extensions_.data();
    instance_create_info.enabledLayerCount       = static_cast<uint32_t>(layers.size());
    instance_create_info.ppEnabledLayerNames     = layers.data();

    // This demo doesn't do any special memory allocation handling,
    // so there's no need for AllocationCallbacks.
    VkAllocationCallbacks* callbacks = nullptr;

    VkResult create_instance_result = _vkCreateInstance(&instance_create_info, callbacks, &vk_instance_);

    if (VK_SUCCESS != create_instance_result)
    {
        AMDVulkanDemoVkUtils::Log("ERROR: Failed to create VkInstance (VkResult %d).", create_instance_result);
        return false;
    }

    if (!AMDVulkanDemoVkUtils::InitInstanceFunctions(vk_instance_))
    {
        return false;
    }

    // There is also a concept of Vulkan Physical Devices (VkPhysicalDevice) which correspond to
    // physical hardware in the system. Physical devices may support different image formats, limits,
    // properties, memory types, and queue types (graphics, compute, transfer, or a combination).
    //
    // On those physical devices, multiple logical devices (VkDevice) can be created which different
    // extensions or layers enabled, along with with specific features and queue types.
    uint32_t physical_device_count       = 0;
    VkResult get_physical_devices_result = _vkEnumeratePhysicalDevices(vk_instance_, &physical_device_count, nullptr);

    if (get_physical_devices_result != VK_SUCCESS || physical_device_count == 0)
    {
        AMDVulkanDemoVkUtils::Log("ERROR: Failed to enumerate physical devices, and had %d physical devices.", physical_device_count);
        return false;
    }
    else
    {
        std::vector<VkPhysicalDevice> physical_devices;
        physical_devices.resize(physical_device_count);
        get_physical_devices_result = _vkEnumeratePhysicalDevices(vk_instance_, &physical_device_count, physical_devices.data());

        if (get_physical_devices_result != VK_SUCCESS)
        {
            AMDVulkanDemoVkUtils::Log("ERROR: Failed to enumerate physical devices.");
            return false;
        }

        if (print_debug_output_)
        {
            // Print out physical device names.
            VkPhysicalDeviceProperties physical_device_properties = {};

            for (uint32_t i = 0; i < physical_device_count; ++i)
            {
                _vkGetPhysicalDeviceProperties(physical_devices[i], &physical_device_properties);
                AMDVulkanDemoVkUtils::Log("PhysicalDevice[%d]: %s", i, physical_device_properties.deviceName);
            }
        }

        // Select the default physical device and store related information.
        // Iterating through each of the retrieved physical devices and skipping over unsupported hardware when selecting device.
        bool found_supported_gpu = false;
        for (uint32_t i = 0; i < physical_device_count; i++)
        {
            default_physical_device_ = physical_devices.at(i);
            _vkGetPhysicalDeviceProperties(default_physical_device_, &physical_device_properties_);
            if (!(physical_device_properties_.deviceID == 0x1506 || physical_device_properties_.deviceID == 0x164e))
            {
                found_supported_gpu = true;
                _vkGetPhysicalDeviceFeatures(default_physical_device_, &physical_device_features_);
                _vkGetPhysicalDeviceMemoryProperties(default_physical_device_, &physical_device_memory_properties_);
                break;
            }
        }
        if (!found_supported_gpu)
        {
            std::cout << "ERROR: Failed to find a supported physical device." << std::endl;
            return false;
        }
    }

#if defined(VK_USE_PLATFORM_WIN32_KHR)
    // Create a VkSurface for the Win32 window so that the demo can present to the display.
    VkWin32SurfaceCreateInfoKHR surface_create_info = {};
    surface_create_info.sType                       = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    surface_create_info.pNext                       = nullptr;
    surface_create_info.hinstance                   = hInstance_;
    surface_create_info.hwnd                        = hWindow_;
    VkResult create_surface_result                  = _vkCreateWin32SurfaceKHR(vk_instance_, &surface_create_info, nullptr, &vk_surface_);

    if (create_surface_result != VK_SUCCESS || vk_surface_ == VK_NULL_HANDLE)
    {
        AMDVulkanDemoVkUtils::Log("ERROR: Failed to create Win32 surface.");
        return false;
    }

#elif defined(VK_USE_PLATFORM_XCB_KHR)
    // Create a VkSurface for the xcb window so that the demo can present to the display.
    VkXcbSurfaceCreateInfoKHR surface_create_info = {};
    surface_create_info.sType                     = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
    surface_create_info.pNext                     = nullptr;
    surface_create_info.flags                     = 0;
    surface_create_info.connection                = xcb_conntection_;
    surface_create_info.window                    = xcb_window_;
    VkResult create_surface_result                = _vkCreateXcbSurfaceKHR(vk_instance_, &surface_create_info, nullptr, &vk_surface_);

    if (create_surface_result != VK_SUCCESS || vk_surface_ == VK_NULL_HANDLE)
    {
        AMDVulkanDemoVkUtils::Log("ERROR: Failed to create XCB surface.");
        return false;
    }
#elif defined(VK_USE_PLATFORM_ANDROID_KHR)
    assert(native_window_ != nullptr);
    assert(vk_surface_ == VK_NULL_HANDLE);

    VkAndroidSurfaceCreateInfoKHR surface_create_info{};
    surface_create_info.sType = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR, surface_create_info.pNext = nullptr, surface_create_info.flags = 0,
    surface_create_info.window = native_window_;

    VkResult result = _vkCreateAndroidSurfaceKHR(vk_instance_, &surface_create_info, nullptr, &vk_surface_);
    if (result != VK_SUCCESS || vk_surface_ == VK_NULL_HANDLE)
    {
        AMDVulkanDemoVkUtils::Log("ERROR: Failed to create Android surface. _vkCreateAndroidSurfaceKHR() returned %d.", result);
        return false;
    }
    assert(vk_surface_ != VK_NULL_HANDLE);
#else
    AMDVulkanDemoVkUtils::Log("ERROR: The current platform is not supported - no VkSurface will be created!");
    assert(!"The current platform is not supported - no VkSurface will be created!");
    return false;
#endif

    // Each Physical Device can support a variety of Queues which support different types of processing
    // (ie: Graphics, computer, transfer, sparse binding, etc), but not all of them support presenting
    // to the recently created surface, so the different queues need to be queried to find one that supports
    // both graphics and presenting (Note: it is not guaranteed that one will exists that supports both,
    // but in the case of desktop systems it's likely that one will be there). It is quite possible for
    // a GPU to used in a headless system (server) which would not be able to present to any surfaces, but
    // could still run either graphics or compute (or both). There could also be two different queues
    // such that one supports graphics, and the other supports present, and in that case the application
    // would need to transfer the generated image from the graphics queue to the present queue to display it.
    // NOTE: This code does not support the situation of using different queues for graphics and present.
    uint32_t queue_family_count = 0;
    _vkGetPhysicalDeviceQueueFamilyProperties(default_physical_device_, &queue_family_count, nullptr);

    if (queue_family_count == 0)
    {
        AMDVulkanDemoVkUtils::Log("ERROR: Selected physical device does not support any queue families.");
        return false;
    }

    std::vector<VkQueueFamilyProperties> queue_family_properties;
    queue_family_properties.resize(queue_family_count);
    _vkGetPhysicalDeviceQueueFamilyProperties(default_physical_device_, &queue_family_count, queue_family_properties.data());

    // Select first queue family that supports both graphics and present for the surface created above.
    bool found_supporting_queue = false;

    for (uint32_t queue_family_index = 0; queue_family_index < queue_family_count; ++queue_family_index)
    {
        // Check if supports graphics.
        bool supports_graphics = false;

        if ((queue_family_properties[queue_family_index].queueFlags & VK_QUEUE_GRAPHICS_BIT) == VK_QUEUE_GRAPHICS_BIT)
        {
            if (print_debug_output_)
            {
                AMDVulkanDemoVkUtils::Log("DEBUG: QueueFamilyIndex %d supports Graphics.", queue_family_index);
            }

            supports_graphics = true;
        }

        // Check if the device supports presenting to this surface.
        VkBool32 supports_present       = VK_FALSE;
        VkResult surface_support_result = _vkGetPhysicalDeviceSurfaceSupportKHR(default_physical_device_, queue_family_index, vk_surface_, &supports_present);

        if (surface_support_result == VK_SUCCESS && supports_present == VK_TRUE && print_debug_output_)
        {
            AMDVulkanDemoVkUtils::Log("DEBUG: QueueFamilyIndex %d supports present.", queue_family_index);
        }

        if (supports_graphics && supports_present)
        {
            // Both graphics and present is supported, so store this queue_family_index.
            if (print_debug_output_)
            {
                AMDVulkanDemoVkUtils::Log("DEBUG: Selecting QueueFamilyIndex %d.", queue_family_index);
            }

            found_supporting_queue       = true;
            queue_family_index_graphics_ = queue_family_index;
            queue_family_index_present_  = queue_family_index;
        }
    }

    if (!found_supporting_queue)
    {
        AMDVulkanDemoVkUtils::Log("ERROR: Unable to find a queue family that supports graphics and present.");
        return false;
    }

    // Query available device extensions.
    uint32_t available_device_extension_count = 0;
    VkResult get_device_extension_result = _vkEnumerateDeviceExtensionProperties(default_physical_device_, nullptr, &available_device_extension_count, nullptr);

    if (get_device_extension_result != VK_SUCCESS)
    {
        AMDVulkanDemoVkUtils::Log("ERROR: Unable to get number of device extensions.");
        return false;
    }

    // Make sure required device extensions are available.
    std::vector<VkExtensionProperties> available_device_extensions;
    available_device_extensions.resize(available_device_extension_count);
    get_device_extension_result =
        _vkEnumerateDeviceExtensionProperties(default_physical_device_, nullptr, &available_device_extension_count, available_device_extensions.data());

    if (get_device_extension_result != VK_SUCCESS)
    {
        AMDVulkanDemoVkUtils::Log("ERROR: Unable to get device extensions.");
        return false;
    }
    else
    {
        // Store and print extension names.
        for (uint32_t i = 0; i < available_device_extension_count; ++i)
        {
            AddSupportedDeviceExtension(available_device_extensions[i].extensionName);

            if (print_debug_output_)
            {
                AMDVulkanDemoVkUtils::Log("Device Extension %d: %s", i, available_device_extensions[i].extensionName);
            }
        }

        // Report error if required extension not available.
        bool missing_required_extensions = false;

        for (uint32_t r = 0; r < required_device_extensions_.size(); ++r)
        {
            if (!IsDeviceExtensionSupported(required_device_extensions_[r]))
            {
                AMDVulkanDemoVkUtils::Log("ERROR: Required Device extension '%s' is not available.", required_device_extensions_[r]);
                missing_required_extensions = true;
            }
        }

        if (missing_required_extensions)
        {
            return false;
        }
    }

    // CREATE A DEVICE.
    VkDeviceQueueCreateInfo device_queue_create_info = {};
    device_queue_create_info.sType                   = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    device_queue_create_info.pNext                   = nullptr;
    device_queue_create_info.flags                   = 0;
    device_queue_create_info.queueFamilyIndex        = queue_family_index_graphics_;
    device_queue_create_info.queueCount              = 1;
    float queuePriority                              = 1.0f;
    device_queue_create_info.pQueuePriorities        = &queuePriority;

    VkDeviceCreateInfo device_create_info      = {};
    device_create_info.sType                   = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    device_create_info.pNext                   = nullptr;
    device_create_info.flags                   = 0;
    device_create_info.queueCreateInfoCount    = 1;
    device_create_info.pQueueCreateInfos       = &device_queue_create_info;
    device_create_info.enabledLayerCount       = 0;
    device_create_info.ppEnabledLayerNames     = nullptr;
    device_create_info.enabledExtensionCount   = static_cast<uint32_t>(optional_device_extensions_.size());
    device_create_info.ppEnabledExtensionNames = optional_device_extensions_.data();
    device_create_info.pEnabledFeatures        = &physical_device_features_;

    VkResult create_device_result = _vkCreateDevice(default_physical_device_, &device_create_info, nullptr, &vk_device_);

    if (create_device_result == VK_ERROR_EXTENSION_NOT_PRESENT)
    {
        // Try again with only required extensions.
        device_create_info.enabledExtensionCount   = static_cast<uint32_t>(required_device_extensions_.size());
        device_create_info.ppEnabledExtensionNames = required_device_extensions_.data();

        create_device_result = _vkCreateDevice(default_physical_device_, &device_create_info, nullptr, &vk_device_);
    }

    if (create_device_result != VK_SUCCESS)
    {
        AMDVulkanDemoVkUtils::Log("ERROR: Failed to create device.");
        return false;
    }

    if (!AMDVulkanDemoVkUtils::InitDeviceFunctions(vk_device_))
    {
        return false;
    }

    // Now that a VkInstance, VkPhysicalDevice, and VkDevice have been selected, a GPUPerfAPI Context can be opened on the specified device
    // so that the available counters can be queried.
    if (gpu_perf_api_helper_.IsLoaded())
    {
        GpaVkContextOpenInfo gpa_context_open_info = {};
        gpa_context_open_info.instance             = vk_instance_;
        gpa_context_open_info.physical_device      = default_physical_device_;
        gpa_context_open_info.device               = vk_device_;

        GpaOpenContextFlags open_flags    = IncludeHwCounters() ? kGpaOpenContextEnableHardwareCountersBit : kGpaOpenContextDefaultBit;
        GpaStatus gpa_open_context_status = gpu_perf_api_helper_.gpa_function_table_->GpaOpenContext(&gpa_context_open_info, open_flags, &gpa_context_id_);
        GpaUInt32 device_id, revision_id;
        gpu_perf_api_helper_.gpa_function_table_->GpaGetDeviceAndRevisionId(gpa_context_id_, &device_id, &revision_id);
        char        device_name[80] = {};
        const char* device          = device_name;
        gpu_perf_api_helper_.gpa_function_table_->GpaGetDeviceName(gpa_context_id_, &device);

        if (gpa_open_context_status != kGpaStatusOk)
        {
            gpu_perf_api_helper_.LogStatus(gpa_open_context_status, "ERROR: Failed to open GPA context.");
            return false;
        }

        if (print_gpa_counter_info_)
        {
            gpu_perf_api_helper_.PrintGPACounterInfo(gpa_context_id_);
        }

        // Make sure discrete counters are supported.
        GpaContextSampleTypeFlags sample_types = 0;
        GpaStatus get_sample_types_status      = gpu_perf_api_helper_.gpa_function_table_->GpaGetSupportedSampleTypes(gpa_context_id_, &sample_types);
        if (get_sample_types_status != kGpaStatusOk)
        {
            gpu_perf_api_helper_.LogStatus(get_sample_types_status, "ERROR: Failed to get supported GPA sample types.");
            return false;
        }

        GpaStatus gpa_create_session_status =
            gpu_perf_api_helper_.gpa_function_table_->GpaCreateSession(gpa_context_id_, kGpaSessionSampleTypeDiscreteCounter, &gpa_session_id_);

        if (gpa_create_session_status != kGpaStatusOk)
        {
            gpu_perf_api_helper_.LogStatus(gpa_create_session_status, "ERROR: Failed to create GPA session.");
            return false;
        }

        GpaStatus gpa_enable_all_counters_status = kGpaStatusOk;
        if (!Counterfile().empty())
        {
            std::fstream counter_file_stream;
            counter_file_stream.open(Counterfile().c_str(), std::ios_base::in);
            std::vector<std::string> counter_list;
            char                     temp_counter[256];
            if (counter_file_stream.is_open())
            {
                while (counter_file_stream.getline(temp_counter, 256))
                {
                    counter_list.push_back(std::string(temp_counter));
                }

                counter_file_stream.close();

                bool success_enable_counter = true;
                for (std::vector<std::string>::const_iterator it = counter_list.cbegin(); it != counter_list.cend(); ++it)
                {
                    GpaStatus gpa_status = gpu_perf_api_helper_.gpa_function_table_->GpaEnableCounterByName(gpa_session_id_, it->c_str());
                    if (gpa_status != kGpaStatusOk)
                    {
                        AMDVulkanDemoVkUtils::Log("Failed to enable counter: '%s'.", it->c_str());
                        gpu_perf_api_helper_.LogStatus(gpa_status);
                    }
                    success_enable_counter &= gpa_status == kGpaStatusOk;
                }

                if (!success_enable_counter)
                {
                    gpa_enable_all_counters_status = kGpaStatusErrorCounterNotFound;
                }
            }
            else
            {
                AMDVulkanDemoVkUtils::Log("ERROR: Unable to open counter file '%s'. Not enabling any counters.", Counterfile().c_str());
            }
        }
        else
        {
            // Enable all the counters.
            gpa_enable_all_counters_status = gpu_perf_api_helper_.gpa_function_table_->GpaEnableAllCounters(gpa_session_id_);
        }

        if (gpa_enable_all_counters_status != kGpaStatusOk)
        {
            gpu_perf_api_helper_.LogStatus(gpa_enable_all_counters_status, "ERROR: Failed to enable all GPA counters.");
            return false;
        }

        // Get the number of required passes based on the counters that were enabled above. Store it as a member
        // because it will be needed to control which CommandBuffers get GPA calls included.
        GpaStatus gpa_get_pass_count_status = gpu_perf_api_helper_.gpa_function_table_->GpaGetPassCount(gpa_session_id_, &required_pass_count_);
        if (gpa_get_pass_count_status != kGpaStatusOk)
        {
            gpu_perf_api_helper_.LogStatus(gpa_get_pass_count_status, "ERROR: Failed to get the number of required GPA passes.");
            return false;
        }

        if (print_debug_output_)
        {
            AMDVulkanDemoVkUtils::Log("GPA requires %d pass(es).", required_pass_count_);
        }

        // Begin the GPA session to lock in the set of selected counters and allow command buffers to start
        // being built with GPA commands included.
        GpaStatus gpa_begin_session_status = gpu_perf_api_helper_.gpa_function_table_->GpaBeginSession(gpa_session_id_);

        if (gpa_begin_session_status != kGpaStatusOk)
        {
            gpu_perf_api_helper_.LogStatus(gpa_begin_session_status, "ERROR: Failed to begin GPA session.");
            return false;
        }
    }

    // Get a queue from the graphics queue family.
    _vkGetDeviceQueue(vk_device_, queue_family_index_graphics_, queue_index_, &vk_queue_);

    // Now the surface format needs to be selected from those available. The preference is for
    // B8G8R8A8_UNORM, but a different format will be okay.
    uint32_t format_count               = 0;
    VkResult get_surface_formats_result = _vkGetPhysicalDeviceSurfaceFormatsKHR(default_physical_device_, vk_surface_, &format_count, nullptr);

    if (get_surface_formats_result != VK_SUCCESS || format_count == 0)
    {
        AMDVulkanDemoVkUtils::Log("ERROR: The selected physical device does not support any surface formats.");
        return false;
    }

    std::vector<VkSurfaceFormatKHR> surface_formats;
    surface_formats.resize(format_count);
    get_surface_formats_result = _vkGetPhysicalDeviceSurfaceFormatsKHR(default_physical_device_, vk_surface_, &format_count, surface_formats.data());

    if (get_surface_formats_result != VK_SUCCESS)
    {
        AMDVulkanDemoVkUtils::Log("ERROR: Failed to get surface formats.");
        return false;
    }

    bool found_desired_format = false;

    for (uint32_t i = 0; i < format_count; ++i)
    {
        if (surface_formats[i].format == VK_FORMAT_B8G8R8A8_UNORM)
        {
            vk_surface_format_   = surface_formats[i];
            found_desired_format = true;
            break;
        }
    }

    if (!found_desired_format)
    {
        // Didn't find the desired format, but still be able to select it, or maybe have to fallback to whatever is available.
        if (surface_formats[0].format == VK_FORMAT_UNDEFINED)
        {
            // Get to select the format!
            vk_surface_format_.format     = VK_FORMAT_B8G8R8A8_UNORM;
            vk_surface_format_.colorSpace = surface_formats[0].colorSpace;
        }
        else
        {
            // Fallback to whatever is available.
            vk_surface_format_ = surface_formats[0];
        }
    }

    // Get presentation modes.
    uint32_t present_mode_count       = 0;
    VkResult get_present_modes_result = _vkGetPhysicalDeviceSurfacePresentModesKHR(default_physical_device_, vk_surface_, &present_mode_count, nullptr);

    if (get_present_modes_result != VK_SUCCESS)
    {
        AMDVulkanDemoVkUtils::Log("ERROR: Failed to get number of supported present modes.");
        return false;
    }

    std::vector<VkPresentModeKHR> present_modes;
    present_modes.resize(present_mode_count);
    get_present_modes_result = _vkGetPhysicalDeviceSurfacePresentModesKHR(default_physical_device_, vk_surface_, &present_mode_count, present_modes.data());

    if (get_present_modes_result != VK_SUCCESS)
    {
        AMDVulkanDemoVkUtils::Log("ERROR: Failed to get supported present modes.");
        return false;
    }

    // Presentation modes:
    // "VK_PRESENT_MODE_FIFO_KHR" is equivalent to traditional graphics 'v-sync' mode and it *should* be available on all drivers (but apparently
    // it is not always properly supported). However, that mode can cause the application to block if the CPU / GPU gets too many frames ahead of
    // the display. This is a great fall-back option if other smoother modes aren't available.
    // "VK_PRESENT_MODE_MAILBOX_KHR" will avoid the blocking scenario by always putting the most recently rendered image in-place of any others that
    // are pending in the display queue. This approach also avoids tearing artifacts.
    // "VK_PRESENT_MODE_IMMEDIATE_KHR" will also avoid the blocking scenarios, but tearing may occur as the image skips the present queue and gets
    // sent to the screen immediately, replacing whatever was in the display memory at that time. Thus part of the screen may have the previous image
    // and the other part of the screen would have the new image.
    // "VK_PRESENT_MODE_FIFO_RELAXED_KHR" is also available, but is best used for applications that may occasionally render slower than the refresh
    // rate of the display. In this mode, if the present queue is empty (due to the application taking slightly too long to render), then the image
    // will get sent directly to the screen which may result in tearing.
    // There are two additional modes "VK_PRESENT_MODE_SHARED_DEMAND_REFRESH_KHR" and "VK_PRESENT_MODE_SHARED_CONTINUOUS_REFRESH_KHR" which allow the
    // application and the display queue to share access to a single image. Neither of these modes are beneficial for this demo.
    //
    // In order to avoid tearing artifacts and allow for the fastest possible rendering, mailbox mode will be preferred over FIFO.
    vk_present_mode_ = VK_PRESENT_MODE_FIFO_KHR;

    // Select mailbox mode if it is available.
    for (std::vector<VkPresentModeKHR>::const_iterator mode_iterator = present_modes.cbegin(); mode_iterator != present_modes.cend(); ++mode_iterator)
    {
        if (*mode_iterator == VK_PRESENT_MODE_MAILBOX_KHR)
        {
            vk_present_mode_ = *mode_iterator;
            break;
        }
    }

    // Get surface capabilities to determine the acceptable sizes of the swapchain images that will be presented to the surface.
    VkResult get_surface_capabilities_result = _vkGetPhysicalDeviceSurfaceCapabilitiesKHR(default_physical_device_, vk_surface_, &vk_surface_capabilities_);

    if (get_surface_capabilities_result != VK_SUCCESS)
    {
        AMDVulkanDemoVkUtils::Log("ERROR: Failed to get surface capabilities.");
        return false;
    }

    // The extents of the swapchain images should match the resolution of the window being drawn into.
    // It doesn't actually HAVE to match, but for the purposes of this demo they should.
    // make sure 'currentExtent' matches window and is within acceptable range.
    if (vk_surface_capabilities_.currentExtent.width == UINT32_MAX && vk_surface_capabilities_.currentExtent.height == UINT32_MAX)
    {
        // This means the display engine supports some flexibility in the size of the image surface compared
        // to the size of the window that is being presented to.
        swap_chain_image_extent_.width =
            std::max(vk_surface_capabilities_.minImageExtent.width, std::min(vk_surface_capabilities_.maxImageExtent.width, kDefaultWindowWidth));
        swap_chain_image_extent_.height =
            std::max(vk_surface_capabilities_.minImageExtent.height, std::min(vk_surface_capabilities_.maxImageExtent.height, kDefaultWindowHeight));
    }
    else
    {
        swap_chain_image_extent_ = vk_surface_capabilities_.currentExtent;
    }

    // If allowed, add one more swapchain image than the implementation needs to better avoid latency.
    // This will allow the application to always have one image to work one while others may be queued for display.
    uint32_t swap_chain_image_count = vk_surface_capabilities_.minImageCount + 1;

    if (vk_surface_capabilities_.minImageCount > 0 && swap_chain_image_count > vk_surface_capabilities_.maxImageCount)
    {
        swap_chain_image_count = vk_surface_capabilities_.maxImageCount;
    }

    // Finally have all the information necessary to create a swapchain!
    VkSwapchainCreateInfoKHR swap_chain_create_info = {};
    swap_chain_create_info.sType                    = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    swap_chain_create_info.pNext                    = nullptr;
    swap_chain_create_info.flags                    = 0;
    swap_chain_create_info.surface                  = vk_surface_;
    swap_chain_create_info.minImageCount            = swap_chain_image_count;
    swap_chain_create_info.imageFormat              = vk_surface_format_.format;
    swap_chain_create_info.imageColorSpace          = vk_surface_format_.colorSpace;
    swap_chain_create_info.imageExtent              = swap_chain_image_extent_;
    swap_chain_create_info.imageArrayLayers         = 1;
    swap_chain_create_info.imageUsage               = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    // This demo currently only supports a single queue family that supports both graphics & present,
    // so EXCLUSIVE mode can be used here.
    swap_chain_create_info.imageSharingMode      = VK_SHARING_MODE_EXCLUSIVE;
    swap_chain_create_info.queueFamilyIndexCount = 1;
    swap_chain_create_info.pQueueFamilyIndices   = &queue_family_index_graphics_;

    // Can be used to rotate an image.
    swap_chain_create_info.preTransform = vk_surface_capabilities_.currentTransform;

    // Can be used to blend the window into other surfaces.
    swap_chain_create_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;

    swap_chain_create_info.presentMode  = vk_present_mode_;
    swap_chain_create_info.clipped      = VK_TRUE;
    swap_chain_create_info.oldSwapchain = VK_NULL_HANDLE;

    VkResult create_swap_chain_result = _vkCreateSwapchainKHR(vk_device_, &swap_chain_create_info, nullptr, &vk_swap_chain_);

    if (create_swap_chain_result != VK_SUCCESS)
    {
        AMDVulkanDemoVkUtils::Log("ERROR: Failed to create swapchain.");
        return false;
    }

    // The Vulkan implementation may have created more more swapchain images, so query the number again, and actually get handles
    // to those image objects.
    VkResult get_swap_chain_images_result = _vkGetSwapchainImagesKHR(vk_device_, vk_swap_chain_, &swap_chain_image_count, nullptr);

    if (get_swap_chain_images_result != VK_SUCCESS)
    {
        AMDVulkanDemoVkUtils::Log("ERROR: Failed to get final swapchain image count.");
        return false;
    }

    per_swap_chain_image_resources_.swap_chain_images.resize(swap_chain_image_count);
    get_swap_chain_images_result =
        _vkGetSwapchainImagesKHR(vk_device_, vk_swap_chain_, &swap_chain_image_count, per_swap_chain_image_resources_.swap_chain_images.data());

    if (get_swap_chain_images_result != VK_SUCCESS)
    {
        AMDVulkanDemoVkUtils::Log("ERROR: Failed to get swapchain images.");
        return false;
    }

    per_swap_chain_image_resources_.swap_chain_image_views.resize(swap_chain_image_count);
    per_swap_chain_image_resources_.vk_frame_buffers.resize(swap_chain_image_count);
    prebuilt_frame_resources_.resize(swap_chain_image_count);

    if (gpu_perf_api_helper_.IsLoaded())
    {
        // If using GPUPerfAPI and pre-creating command buffers, extra command buffers will need to be created in order to
        // support the additional passes needed by GPA. This is because the commands related to profiling are embedded in the
        // Vulkan command buffer.
        prebuilt_per_frame_resources_with_gpa_.resize(required_pass_count_);
    }

    // Create an ImageView for each swapchain image so that they can be bound as render targets.
    for (uint32_t i = 0; i < per_swap_chain_image_resources_.swap_chain_images.size(); ++i)
    {
        VkImageViewCreateInfo image_view_create_info           = {};
        image_view_create_info.sType                           = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        image_view_create_info.pNext                           = nullptr;
        image_view_create_info.flags                           = 0;
        image_view_create_info.image                           = per_swap_chain_image_resources_.swap_chain_images[i];
        image_view_create_info.viewType                        = VK_IMAGE_VIEW_TYPE_2D;
        image_view_create_info.format                          = vk_surface_format_.format;
        image_view_create_info.components.r                    = VK_COMPONENT_SWIZZLE_IDENTITY;
        image_view_create_info.components.g                    = VK_COMPONENT_SWIZZLE_IDENTITY;
        image_view_create_info.components.b                    = VK_COMPONENT_SWIZZLE_IDENTITY;
        image_view_create_info.components.a                    = VK_COMPONENT_SWIZZLE_IDENTITY;
        image_view_create_info.subresourceRange.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT;
        image_view_create_info.subresourceRange.baseMipLevel   = 0;
        image_view_create_info.subresourceRange.levelCount     = 1;
        image_view_create_info.subresourceRange.baseArrayLayer = 0;
        image_view_create_info.subresourceRange.layerCount     = 1;

        VkResult create_image_view_result =
            _vkCreateImageView(vk_device_, &image_view_create_info, nullptr, &per_swap_chain_image_resources_.swap_chain_image_views[i]);

        if (create_image_view_result != VK_SUCCESS)
        {
            AMDVulkanDemoVkUtils::Log("ERROR: Failed to create a swapchain image view.");
            return false;
        }
    }

    // This is the start of object creation that is more specific to this demo.

    // This demo will only render into a single color attachment, and the memory can be cleared
    // when the attachment is loaded because the frame will render into the entire image and
    // there is no blending / frame blur taking place.
    // The attachment has no stencil information, so DONT_CARE about those settings.
    VkAttachmentDescription initial_color_attachment_description = {};
    initial_color_attachment_description.flags                   = 0;
    initial_color_attachment_description.format                  = vk_surface_format_.format;
    initial_color_attachment_description.samples                 = VK_SAMPLE_COUNT_1_BIT;
    initial_color_attachment_description.loadOp                  = VK_ATTACHMENT_LOAD_OP_CLEAR;
    initial_color_attachment_description.storeOp                 = VK_ATTACHMENT_STORE_OP_STORE;
    initial_color_attachment_description.stencilLoadOp           = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    initial_color_attachment_description.stencilStoreOp          = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    initial_color_attachment_description.initialLayout           = VK_IMAGE_LAYOUT_UNDEFINED;
    initial_color_attachment_description.finalLayout             = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    // Each render pass is made of 1 or more sub-passes that can have different attachments.
    // The AttachmentReference simply indicates which attachment index it is located at
    // and what layout the attachment is in. In this case, it is a color attachment.
    VkAttachmentReference color_attachment_reference = {};
    color_attachment_reference.attachment            = 0;
    color_attachment_reference.layout                = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    // The description of this sub-pass is that it will:
    // execute a graphics pipeline,
    // has no input attachments (vertices are specified in VS rather than with IB/VB),
    // only has 1 color attachment,
    // no multi-sample attachments that would need to be resolved,
    // no depth stencil attachment,
    // no attachments that need to be passed-through to another sub-pass.
    VkSubpassDescription subpass_description    = {};
    subpass_description.flags                   = 0;
    subpass_description.pipelineBindPoint       = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass_description.inputAttachmentCount    = 0;
    subpass_description.pInputAttachments       = nullptr;
    subpass_description.colorAttachmentCount    = 1;
    subpass_description.pColorAttachments       = &color_attachment_reference;
    subpass_description.pResolveAttachments     = nullptr;
    subpass_description.pDepthStencilAttachment = nullptr;
    subpass_description.preserveAttachmentCount = 0;
    subpass_description.pPreserveAttachments    = nullptr;

    // Define the array of attachments that are used by the render pass.
    // As described above, it only has a color attachment.
    std::vector<VkAttachmentDescription> attachments = {initial_color_attachment_description};

    // Create the render pass.
    // It uses the set of attachments above, and the single sub-pass.
    VkRenderPassCreateInfo initial_render_pass_create_info = {};
    initial_render_pass_create_info.sType                  = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    initial_render_pass_create_info.pNext                  = nullptr;
    initial_render_pass_create_info.flags                  = 0;
    initial_render_pass_create_info.attachmentCount        = static_cast<uint32_t>(attachments.size());
    initial_render_pass_create_info.pAttachments           = attachments.data();
    initial_render_pass_create_info.subpassCount           = 1;
    initial_render_pass_create_info.pSubpasses             = &subpass_description;
    initial_render_pass_create_info.dependencyCount        = 0;
    initial_render_pass_create_info.pDependencies          = nullptr;

    VkResult create_render_pass_result = _vkCreateRenderPass(vk_device_, &initial_render_pass_create_info, nullptr, &vk_render_pass_initial_);

    if (create_render_pass_result != VK_SUCCESS)
    {
        AMDVulkanDemoVkUtils::Log("ERROR: Failed to create render pass.");
        return false;
    }

    // For mid-frame draws, use the same settings as above, except:
    // 1) Don't clear the RT on loading.
    // 2) The layout will start and end as a COLOR_ATTACHMENT_OPTIMAL.
    VkAttachmentDescription color_attachment_description_mid = initial_color_attachment_description;
    color_attachment_description_mid.loadOp                  = VK_ATTACHMENT_LOAD_OP_LOAD;
    color_attachment_description_mid.initialLayout           = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    color_attachment_description_mid.finalLayout             = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    // Define the array of attachments that are used by the render pass.
    // As described above, it only has a color attachment.
    std::vector<VkAttachmentDescription> attachmentsMid = {color_attachment_description_mid};

    // Create the render pass for the middle draw calls which leave the render target as a color attachment.
    VkRenderPassCreateInfo render_pass_create_info_mid = {};
    render_pass_create_info_mid.sType                  = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    render_pass_create_info_mid.pNext                  = nullptr;
    render_pass_create_info_mid.flags                  = 0;
    render_pass_create_info_mid.attachmentCount        = static_cast<uint32_t>(attachmentsMid.size());
    render_pass_create_info_mid.pAttachments           = attachmentsMid.data();
    render_pass_create_info_mid.subpassCount           = 1;
    render_pass_create_info_mid.pSubpasses             = &subpass_description;
    render_pass_create_info_mid.dependencyCount        = 0;
    render_pass_create_info_mid.pDependencies          = nullptr;

    VkResult result_create_render_pass_mid = _vkCreateRenderPass(vk_device_, &render_pass_create_info_mid, nullptr, &vk_render_pass_mid_);

    if (result_create_render_pass_mid != VK_SUCCESS)
    {
        AMDVulkanDemoVkUtils::Log("ERROR: Failed to create render pass mid.");
        return false;
    }

    // Now create a render pass for the final draw which will put the render target into a presentable layout.
    // It is the same as above, except:
    // 1) The final layout is PRESENT_SRC.
    VkAttachmentDescription color_attachment_description_final = color_attachment_description_mid;
    color_attachment_description_final.finalLayout             = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

    // Define the array of attachments that are used by the render pass.
    // As described above, it only has a color attachment.
    std::vector<VkAttachmentDescription> attachments_final = {color_attachment_description_final};

    // Create the render pass for drawing in wireframe.
    VkRenderPassCreateInfo render_pass_create_info_final = render_pass_create_info_mid;
    render_pass_create_info_final.sType                  = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    render_pass_create_info_final.pNext                  = nullptr;
    render_pass_create_info_final.flags                  = 0;
    render_pass_create_info_final.attachmentCount        = static_cast<uint32_t>(attachments_final.size());
    render_pass_create_info_final.pAttachments           = attachments_final.data();
    render_pass_create_info_final.subpassCount           = 1;
    render_pass_create_info_final.pSubpasses             = &subpass_description;
    render_pass_create_info_final.dependencyCount        = 0;
    render_pass_create_info_final.pDependencies          = nullptr;

    VkResult create_render_pass_final_result = _vkCreateRenderPass(vk_device_, &render_pass_create_info_final, nullptr, &vk_render_pass_final_);

    if (create_render_pass_final_result != VK_SUCCESS)
    {
        AMDVulkanDemoVkUtils::Log("ERROR: Failed to create render pass final.");
        return false;
    }

    // Create each of the frame buffers (one for each swapchain image).
    for (uint32_t i = 0; i < per_swap_chain_image_resources_.swap_chain_image_views.size(); i++)
    {
        VkFramebufferCreateInfo frame_buffer_create_info = {};
        frame_buffer_create_info.sType                   = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        frame_buffer_create_info.pNext                   = nullptr;
        frame_buffer_create_info.flags                   = 0;
        frame_buffer_create_info.renderPass =
            vk_render_pass_final_;  //< It doesn't matter too much which render pass is used here, because they are all "compatible" (see spec).
        frame_buffer_create_info.attachmentCount = 1;
        frame_buffer_create_info.pAttachments    = &per_swap_chain_image_resources_.swap_chain_image_views[i];
        frame_buffer_create_info.width           = swap_chain_image_extent_.width;
        frame_buffer_create_info.height          = swap_chain_image_extent_.height;
        frame_buffer_create_info.layers          = 1;

        VkResult create_frame_buffer_result =
            _vkCreateFramebuffer(vk_device_, &frame_buffer_create_info, nullptr, &per_swap_chain_image_resources_.vk_frame_buffers[i]);

        if (create_frame_buffer_result != VK_SUCCESS)
        {
            AMDVulkanDemoVkUtils::Log("ERROR: Failed to create frame_buffer.");
            return false;
        }
    }

    // Create Graphics Pipeline.
    VkPipelineLayoutCreateInfo pipeline_layout_create_info = {};
    pipeline_layout_create_info.sType                      = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipeline_layout_create_info.pNext                      = nullptr;
    pipeline_layout_create_info.flags                      = 0;
    pipeline_layout_create_info.setLayoutCount             = 0;
    pipeline_layout_create_info.pSetLayouts                = nullptr;
    pipeline_layout_create_info.pushConstantRangeCount     = 0;
    pipeline_layout_create_info.pPushConstantRanges        = nullptr;

    VkResult create_pipeline_layout_result = _vkCreatePipelineLayout(vk_device_, &pipeline_layout_create_info, nullptr, &vk_pipeline_layout_);

    if (create_pipeline_layout_result != VK_SUCCESS)
    {
        AMDVulkanDemoVkUtils::Log("ERROR: Failed to create pipeline layout.");
        return false;
    }

    std::string vertex_shader_file = "vk_color_cube_shader.vert.spv";
    vertex_shader_module_          = LoadShader(vertex_shader_file.c_str());

    std::string fragment_shader_file = "vk_color_cube_shader.frag.spv";
    fragment_shader_module_          = LoadShader(fragment_shader_file.c_str());

    std::string wire_frame_shader      = "vk_color_cube_wireframe_shader.frag.spv";
    fragment_shader_wire_frame_module_ = LoadShader(wire_frame_shader.c_str());

    if (VK_NULL_HANDLE == vertex_shader_module_ || VK_NULL_HANDLE == fragment_shader_module_ || VK_NULL_HANDLE == fragment_shader_wire_frame_module_)
    {
        return false;
    }

    VkPipelineShaderStageCreateInfo vertex_shader_state_create_info = {};
    vertex_shader_state_create_info.sType                           = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    vertex_shader_state_create_info.pNext                           = nullptr;
    vertex_shader_state_create_info.flags                           = 0;
    vertex_shader_state_create_info.stage                           = VK_SHADER_STAGE_VERTEX_BIT;
    vertex_shader_state_create_info.module                          = vertex_shader_module_;
    vertex_shader_state_create_info.pName                           = "main";
    vertex_shader_state_create_info.pSpecializationInfo             = nullptr;

    VkPipelineShaderStageCreateInfo fragment_shader_state_create_info = {};
    fragment_shader_state_create_info.sType                           = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    fragment_shader_state_create_info.pNext                           = nullptr;
    fragment_shader_state_create_info.flags                           = 0;
    fragment_shader_state_create_info.stage                           = VK_SHADER_STAGE_FRAGMENT_BIT;
    fragment_shader_state_create_info.module                          = fragment_shader_module_;
    fragment_shader_state_create_info.pName                           = "main";
    fragment_shader_state_create_info.pSpecializationInfo             = nullptr;

    VkPipelineShaderStageCreateInfo pipeline_shader_stages[] = {vertex_shader_state_create_info, fragment_shader_state_create_info};

    VkPipelineVertexInputStateCreateInfo pipeline_vertex_input_state_create_info = {};
    pipeline_vertex_input_state_create_info.sType                                = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    pipeline_vertex_input_state_create_info.pNext                                = nullptr;
    pipeline_vertex_input_state_create_info.flags                                = 0;
    pipeline_vertex_input_state_create_info.vertexAttributeDescriptionCount      = 0;
    pipeline_vertex_input_state_create_info.pVertexBindingDescriptions           = nullptr;
    pipeline_vertex_input_state_create_info.vertexAttributeDescriptionCount      = 0;
    pipeline_vertex_input_state_create_info.pVertexAttributeDescriptions         = nullptr;

    VkPipelineInputAssemblyStateCreateInfo pipeline_input_assembly_state_info = {};
    pipeline_input_assembly_state_info.sType                                  = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    pipeline_input_assembly_state_info.pNext                                  = nullptr;
    pipeline_input_assembly_state_info.flags                                  = 0;
    pipeline_input_assembly_state_info.topology                               = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    pipeline_input_assembly_state_info.primitiveRestartEnable                 = VK_FALSE;

    // scratch that, lets just make the viewports dynamic (Doh! Seems like there is a bug in the validation layers)
    // Create three viewports to divide the window into thirds.
    VkViewport viewports[3];

    for (uint32_t i = 0; i < 3; ++i)
    {
        viewports[i].x        = static_cast<float>(i * swap_chain_image_extent_.width / 3);
        viewports[i].y        = 0.0f;
        viewports[i].width    = static_cast<float>(swap_chain_image_extent_.width / 3);
        viewports[i].height   = static_cast<float>(swap_chain_image_extent_.height);
        viewports[i].minDepth = 0.0f;
        viewports[i].maxDepth = 1.0f;
    }

    std::vector<VkDynamicState> dynamic_states = {VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR};

    VkPipelineDynamicStateCreateInfo dynamic_state_creat_info = {};
    dynamic_state_creat_info.sType                            = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    dynamic_state_creat_info.pNext                            = nullptr;
    dynamic_state_creat_info.flags                            = 0;
    dynamic_state_creat_info.dynamicStateCount                = static_cast<uint32_t>(dynamic_states.size());
    dynamic_state_creat_info.pDynamicStates                   = dynamic_states.data();

    VkRect2D scissor_rect = {};
    scissor_rect.offset   = VkOffset2D({0, 0});
    scissor_rect.extent   = swap_chain_image_extent_;

    // Set a default viewport here, but since the viewport and scissor are set as dynamic states,
    // they can (and will be) modified within the command buffer.
    VkPipelineViewportStateCreateInfo viewport_state_create_info = {};
    viewport_state_create_info.sType                             = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewport_state_create_info.pNext                             = nullptr;
    viewport_state_create_info.flags                             = 0;
    viewport_state_create_info.viewportCount                     = 1;
    viewport_state_create_info.pViewports                        = &viewports[0];
    viewport_state_create_info.scissorCount                      = 1;
    viewport_state_create_info.pScissors                         = &scissor_rect;

    VkPipelineRasterizationStateCreateInfo rasterization_state_create_info = {};
    rasterization_state_create_info.sType                                  = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterization_state_create_info.pNext                                  = nullptr;
    rasterization_state_create_info.flags                                  = 0;
    rasterization_state_create_info.depthClampEnable                       = VK_FALSE;
    rasterization_state_create_info.rasterizerDiscardEnable                = VK_FALSE;
    rasterization_state_create_info.polygonMode                            = VK_POLYGON_MODE_FILL;
    rasterization_state_create_info.cullMode                               = VK_CULL_MODE_BACK_BIT;
    rasterization_state_create_info.frontFace                              = VK_FRONT_FACE_CLOCKWISE;
    rasterization_state_create_info.depthBiasEnable                        = VK_FALSE;
    rasterization_state_create_info.depthBiasConstantFactor                = 0;
    rasterization_state_create_info.depthBiasClamp                         = 0;
    rasterization_state_create_info.depthBiasSlopeFactor                   = 0;
    rasterization_state_create_info.lineWidth                              = 1;

    VkPipelineMultisampleStateCreateInfo pipeline_multi_sample_state_create_info = {};
    pipeline_multi_sample_state_create_info.sType                                = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    pipeline_multi_sample_state_create_info.sampleShadingEnable                  = VK_FALSE;
    pipeline_multi_sample_state_create_info.rasterizationSamples                 = VK_SAMPLE_COUNT_1_BIT;
    pipeline_multi_sample_state_create_info.minSampleShading                     = 1.0f;
    pipeline_multi_sample_state_create_info.pSampleMask                          = nullptr;
    pipeline_multi_sample_state_create_info.alphaToCoverageEnable                = VK_FALSE;
    pipeline_multi_sample_state_create_info.alphaToOneEnable                     = VK_FALSE;

    VkPipelineColorBlendAttachmentState pipeline_color_blend_attachment_state = {};
    pipeline_color_blend_attachment_state.colorWriteMask =
        VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    pipeline_color_blend_attachment_state.blendEnable         = VK_FALSE;
    pipeline_color_blend_attachment_state.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
    pipeline_color_blend_attachment_state.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
    pipeline_color_blend_attachment_state.colorBlendOp        = VK_BLEND_OP_ADD;
    pipeline_color_blend_attachment_state.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
    pipeline_color_blend_attachment_state.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
    pipeline_color_blend_attachment_state.alphaBlendOp        = VK_BLEND_OP_ADD;

    VkPipelineColorBlendStateCreateInfo pipeline_color_blend_state_create_info = {};
    pipeline_color_blend_state_create_info.sType                               = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    pipeline_color_blend_state_create_info.logicOpEnable                       = VK_FALSE;
    pipeline_color_blend_state_create_info.logicOp                             = VK_LOGIC_OP_COPY;
    pipeline_color_blend_state_create_info.attachmentCount                     = 1;
    pipeline_color_blend_state_create_info.pAttachments                        = &pipeline_color_blend_attachment_state;
    pipeline_color_blend_state_create_info.blendConstants[0]                   = 0.0f;
    pipeline_color_blend_state_create_info.blendConstants[1]                   = 0.0f;
    pipeline_color_blend_state_create_info.blendConstants[2]                   = 0.0f;
    pipeline_color_blend_state_create_info.blendConstants[3]                   = 0.0f;

    VkPipelineTessellationStateCreateInfo ts = {};
    ts.sType                                 = VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO;

    VkPipelineDepthStencilStateCreateInfo ds = {};
    ds.sType                                 = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;

    VkGraphicsPipelineCreateInfo graphics_pipeline_create_info = {};
    graphics_pipeline_create_info.sType                        = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    graphics_pipeline_create_info.flags                        = 0;
    graphics_pipeline_create_info.stageCount                   = 2;
    graphics_pipeline_create_info.pStages                      = pipeline_shader_stages;
    graphics_pipeline_create_info.pVertexInputState            = &pipeline_vertex_input_state_create_info;
    graphics_pipeline_create_info.pInputAssemblyState          = &pipeline_input_assembly_state_info;
    graphics_pipeline_create_info.pTessellationState           = &ts;
    graphics_pipeline_create_info.pViewportState               = &viewport_state_create_info;
    graphics_pipeline_create_info.pRasterizationState          = &rasterization_state_create_info;
    graphics_pipeline_create_info.pMultisampleState            = &pipeline_multi_sample_state_create_info;
    graphics_pipeline_create_info.pDepthStencilState           = &ds;
    graphics_pipeline_create_info.pColorBlendState             = &pipeline_color_blend_state_create_info;
    graphics_pipeline_create_info.pDynamicState                = &dynamic_state_creat_info;
    graphics_pipeline_create_info.layout                       = vk_pipeline_layout_;
    graphics_pipeline_create_info.renderPass                   = vk_render_pass_initial_;
    graphics_pipeline_create_info.subpass                      = 0;
    graphics_pipeline_create_info.basePipelineHandle           = VK_NULL_HANDLE;
    graphics_pipeline_create_info.basePipelineIndex            = -1;

    VkResult create_graphics_pipelines_result =
        _vkCreateGraphicsPipelines(vk_device_, VK_NULL_HANDLE, 1, &graphics_pipeline_create_info, nullptr, &vk_pipeline_);

    if (create_graphics_pipelines_result != VK_SUCCESS)
    {
        AMDVulkanDemoVkUtils::Log("ERROR: Failed to create graphics pipelines.");
        return false;
    }

    // Modify existing state objects as needed to configure a GraphicsPipeline that will draw a wireframe around the cube
    fragment_shader_state_create_info.module = fragment_shader_wire_frame_module_;

    VkPipelineShaderStageCreateInfo pipeline_shader_stages_wire_frame[] = {vertex_shader_state_create_info, fragment_shader_state_create_info};

    // Modify the existing rasterization state to draw lines and to disable culling.
    // Make sure lineWidth is set to 1. In order to draw wider lines, the "wideLines"
    // feature would need to be supported and enabled on the device.
    rasterization_state_create_info.polygonMode = VK_POLYGON_MODE_LINE;
    rasterization_state_create_info.cullMode    = VK_CULL_MODE_NONE;
    rasterization_state_create_info.lineWidth   = 1;

    VkGraphicsPipelineCreateInfo graphics_pipeline_create_info_wire_frame = graphics_pipeline_create_info;
    graphics_pipeline_create_info_wire_frame.stageCount                   = 2;
    graphics_pipeline_create_info_wire_frame.pStages                      = pipeline_shader_stages_wire_frame;
    graphics_pipeline_create_info_wire_frame.pRasterizationState          = &rasterization_state_create_info;
    graphics_pipeline_create_info_wire_frame.pColorBlendState             = &pipeline_color_blend_state_create_info;

    VkResult create_graphics_pipeline_wire_frame_result =
        _vkCreateGraphicsPipelines(vk_device_, VK_NULL_HANDLE, 1, &graphics_pipeline_create_info_wire_frame, nullptr, &vk_pipeline_wire_frame_);

    if (create_graphics_pipeline_wire_frame_result != VK_SUCCESS)
    {
        AMDVulkanDemoVkUtils::Log("ERROR: Failed to create wireframe graphics pipelines.");
        return false;
    }

    // Every Vulkan app will need at least one CommandPool in order to allocate CommandBuffers.
    // If an application is using multiple threads to distribute CommandBuffer building, then
    // one CommandPool should be created for each thread. And if the application is doing
    // both graphics and compute work, then it will need to create two different CommandPools,
    // one for each queue_family_index.
    // To get even more efficient an application may want to create one CommandPool for each
    // swapchainImage (because that will limit the number of frames that can be processed or
    // queued) for each thread. This would allow for any thread to process its portion of any
    // upcoming frame based on when that frame's resources become available. There are certain
    // situations when this would become more useful, such as when CommandBuffers are being reset
    // and rebuilt each frame.
    // In this demo, there is only one thread doing graphics work and the CommandBuffers can all
    // be built ahead of time, so only one CommandPool is needed.
    VkCommandPoolCreateInfo command_pool_create_info = {};
    command_pool_create_info.sType                   = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    command_pool_create_info.pNext                   = nullptr;
    command_pool_create_info.flags                   = 0;
    command_pool_create_info.queueFamilyIndex        = queue_family_index_graphics_;

    VkResult create_command_pool_result = _vkCreateCommandPool(vk_device_, &command_pool_create_info, nullptr, &vk_command_pool_);

    if (create_command_pool_result != VK_SUCCESS)
    {
        AMDVulkanDemoVkUtils::Log("ERROR: Failed to create command pool.");
        return false;
    }

    // Create semaphores that are necessary to synchronize rendering and presenting.
    VkSemaphoreCreateInfo semaphore_create_info = {};
    semaphore_create_info.sType                 = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    semaphore_create_info.pNext                 = nullptr;
    semaphore_create_info.flags                 = 0;

    VkResult create_semaphore_result = _vkCreateSemaphore(vk_device_, &semaphore_create_info, nullptr, &vk_semaphore_acquired_swapchain_image_);

    if (create_semaphore_result != VK_SUCCESS)
    {
        AMDVulkanDemoVkUtils::Log("ERROR: Failed to create semaphore to acquire swapchain images.");
        return false;
    }

    create_semaphore_result = _vkCreateSemaphore(vk_device_, &semaphore_create_info, nullptr, &vk_sempahore_fineshed_rendering_);

    if (create_semaphore_result != VK_SUCCESS)
    {
        AMDVulkanDemoVkUtils::Log("ERROR: Failed to create semaphore to control rendering.");
        return false;
    }

    // Build Command Buffers!
    // These are for normal execution and will NOT have GPA enabled.
    // There is a 1-1 relationship between the number of prebuiltPerFrameResources
    // and the number of frame buffers, so the same index can be used for both.
    for (size_t i = 0; i < prebuilt_frame_resources_.size(); i++)
    {
        bool      enable_gpa     = false;
        GpaUInt32 gpa_pass_index = 0;

        PreBuildCommandBuffers(&prebuilt_frame_resources_[i], per_swap_chain_image_resources_.vk_frame_buffers[i], enable_gpa, gpa_pass_index);
    }

    if (gpu_perf_api_helper_.IsLoaded())
    {
        // Build additional command buffers to support GPA profiling.
        // There will be one of these for each of the passes that GPA needs to perform,
        // so the frame buffers will need to be cycled among them.
        for (size_t i = 0; i < prebuilt_per_frame_resources_with_gpa_.size(); i++)
        {
            uint32_t  swap_chain_index = i % swap_chain_image_count;
            bool      enable_gpa       = true;
            GpaUInt32 gpa_pass_index   = static_cast<GpaUInt32>(i);

            PreBuildCommandBuffers(
                &prebuilt_per_frame_resources_with_gpa_[i], per_swap_chain_image_resources_.vk_frame_buffers[swap_chain_index], enable_gpa, gpa_pass_index);
        }

        // All command buffers have been built; ending the session will confirm this.
        GpaStatus gpa_end_session_status = gpu_perf_api_helper_.gpa_function_table_->GpaEndSession(gpa_session_id_);

        if (gpa_end_session_status != kGpaStatusOk)
        {
            gpu_perf_api_helper_.LogStatus(gpa_end_session_status, "ERROR: Failed to end GPA session.");
        }
    }

    // Set the app as being successfully intialized.
    initialized_ = true;
    AMDVulkanDemoVkUtils::Log("Vulkan initialization successful.");

    return true;
}

/// Draws the scene in a method that can be called on any platform.
void AMDVulkanDemo::DrawScene()
{
    if (!initialized_)
        return;

    // Get the index of an image in the swapchain that is available to be rendered into.
    // The previously discussed presentation modes may affect the order that the swapchain images become available
    // for rendering, so it is necessary to ask which image the presentation engine wants to use next.
    // This call may stall until an image is available, so it may be advantageous to do other necessary processing prior
    // to this call to take advantage of the asynchronous nature of the CPU, GPU, and presentation engines. For example,
    // render-to-texture operations could be submitted before this call, and other CPU-side operations could be done,
    // Then this call is executed to obtain an image index and do the final render and presentation.
    uint32_t swap_chain_image_index   = 0;
    VkResult aquire_next_image_result = _vkAcquireNextImageKHR(
        vk_device_, vk_swap_chain_, std::numeric_limits<uint64_t>::max(), vk_semaphore_acquired_swapchain_image_, VK_NULL_HANDLE, &swap_chain_image_index);

    if (aquire_next_image_result != VK_SUCCESS)
    {
        AMDVulkanDemoVkUtils::Log("ERROR: Failed to acquire next image.");
    }

    std::vector<VkCommandBuffer> command_buffers_to_submit;

    // Since GPA needs multiple passes, the command buffers also need to be cycled through similar to the swapchain image index.
    if (gpu_perf_api_helper_.IsLoaded() && num_frames_rendered_ < required_pass_count_)
    {
        // GPA is actively profiling, so make sure to use the resources with GPA Perf Counters enabled, and
        // use the frameCount to determine which set of resources (ie: which GPA pass) to submit. Each pass has
        // been specifically built to correspond to an existing swapchain image. That is to say, that there is
        // an assumption that the call to vkAcquireNextImageKHR() above will return the images in a cyclic manner.
        // This assumption may not hold true if a different PRESENT_MODE is used by the application.
        command_buffers_to_submit.push_back(prebuilt_per_frame_resources_with_gpa_[num_frames_rendered_].cube_.command_buffer);
        command_buffers_to_submit.push_back(prebuilt_per_frame_resources_with_gpa_[num_frames_rendered_].wire_frame_.command_buffer);
        command_buffers_to_submit.push_back(prebuilt_per_frame_resources_with_gpa_[num_frames_rendered_].cube_and_wire_frame_.command_buffer_cube);
        command_buffers_to_submit.push_back(prebuilt_per_frame_resources_with_gpa_[num_frames_rendered_].cube_and_wire_frame_.command_buffer_wire_frame);
    }
    else
    {
        // GPA is not profiling, so use the command buffers that do not have any counters enabled, and
        // use the swapchain index to select which resources to submit so that it draws to the correct swapchain image.
        command_buffers_to_submit.push_back(prebuilt_frame_resources_[swap_chain_image_index].cube_.command_buffer);
        command_buffers_to_submit.push_back(prebuilt_frame_resources_[swap_chain_image_index].wire_frame_.command_buffer);
        command_buffers_to_submit.push_back(prebuilt_frame_resources_[swap_chain_image_index].cube_and_wire_frame_.command_buffer_cube);
        command_buffers_to_submit.push_back(prebuilt_frame_resources_[swap_chain_image_index].cube_and_wire_frame_.command_buffer_wire_frame);
    }

    // Setup the submit.
    // With a wait_dest_stage_mask of TOP_OF_PIPE, the submit will wait at the very beginning for the wait_semaphores
    // (AcquiredSwapchainImage) to get signaled, thus indicating that a new swapchain image is available to be
    // rendered into. This synchronizes the processing of the current frame until an earlier frame has completed
    // and a new swapchain image is available. Earlier, the numbers of requested swapchain images was +1 from the
    // minimum, so theoretically this synchronization shouldn't cause any significant delays.
    //
    // If the demo had a lot more vertex processing to do, it might be advantageous to set the wait_dest_stage_mask to
    // COLOR_ATTACHMENT_OUTPUT so that vertex processing could happen even while earlier frames are still being
    // rendered or presented. That approach would have required that the RenderPass sub-pass was setup with a
    // dependency that would transition the color attachment from the external sub-pass (being presented) to
    // allowing read / write access from the "current" sub-pass.
    //
    // The submit info also specifies which command buffers to execute, and which semaphores to signal when those
    // command buffers have completed. This needs to be setup (or at least modified) each frame to update which
    // swap_chain_image_index was acquired for rendering. It may not always be round-robin or deterministic depending
    // on the selected present mode and other workloads on the system.
    VkPipelineStageFlags wait_dest_stage_mask = {VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT};
    VkSemaphore          wait_semaphores[]    = {vk_semaphore_acquired_swapchain_image_};
    VkSemaphore          signal_semaphores[]  = {vk_sempahore_fineshed_rendering_};
    VkSubmitInfo         submit_info          = {};
    submit_info.sType                         = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submit_info.pNext                         = nullptr;
    submit_info.waitSemaphoreCount            = 1;
    submit_info.pWaitSemaphores               = wait_semaphores;
    submit_info.pWaitDstStageMask             = &wait_dest_stage_mask;
    submit_info.commandBufferCount            = static_cast<uint32_t>(command_buffers_to_submit.size());
    submit_info.pCommandBuffers               = command_buffers_to_submit.data();
    submit_info.signalSemaphoreCount          = 1;
    submit_info.pSignalSemaphores             = signal_semaphores;

    VkResult queue_submit_result = _vkQueueSubmit(vk_queue_, 1, &submit_info, VK_NULL_HANDLE);

    if (queue_submit_result != VK_SUCCESS)
    {
        AMDVulkanDemoVkUtils::Log("ERROR: Failed to submit to queue.");
    }

    // Now present the rendered image to the screen!
    // The present info specifies that presentation shouldn't happen until the signal_semaphores have been signaled
    // (ie: the submitted workload has finished rendering).
    // It also specifies which swapchain to present to, and specifically the index of the swapchain image to use.
    VkPresentInfoKHR present_info   = {};
    present_info.sType              = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    present_info.pNext              = nullptr;
    present_info.waitSemaphoreCount = 1;
    present_info.pWaitSemaphores    = signal_semaphores;
    present_info.swapchainCount     = 1;
    present_info.pSwapchains        = &vk_swap_chain_;
    present_info.pImageIndices      = &swap_chain_image_index;
    present_info.pResults           = nullptr;

    VkResult result_present = _vkQueuePresentKHR(vk_queue_, &present_info);

    if (result_present != VK_SUCCESS)
    {
        AMDVulkanDemoVkUtils::Log("ERROR: Failed to present queue.");
    }

    if (gpu_perf_api_helper_.IsLoaded() && num_frames_rendered_ == required_pass_count_)
    {
        bool           is_ready   = false;
        const uint32_t time_out   = 10000;  // ms
        auto           start_time = std::chrono::high_resolution_clock::now();

        do
        {
            is_ready = kGpaStatusOk == gpu_perf_api_helper_.gpa_function_table_->GpaIsSessionComplete(gpa_session_id_);

            if (!is_ready)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(0));

                auto                                      endTime     = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::milli> elapsedTime = endTime - start_time;

                if (elapsedTime.count() > time_out)
                {
                    break;
                }
            }
        } while (!is_ready);

        if (is_ready)
        {
            GpaUInt32 sample_count = 0;
            gpu_perf_api_helper_.gpa_function_table_->GpaGetSampleCount(gpa_session_id_, &sample_count);

            if (print_debug_output_)
            {
                AMDVulkanDemoVkUtils::Log("There were %d GPA samples recorded.", sample_count);
            }

            // Open the CSV file so that counter results also get output there.
            if (!gpu_perf_api_helper_.OpenCSVFile())
            {
                AMDVulkanDemoVkUtils::Log("ERROR: Unable to open CSV file to output profile results.");
            }

            // This example only renders one set of profiles (aka, only the number of passes needed to generate one set of results).
            unsigned int profile_set = 0;

            gpu_perf_api_helper_.PrintGpaSampleResults(gpa_context_id_, gpa_session_id_, profile_set, AMDVulkanDemo::kGpaSampleIdCube,             print_debug_output_, Verify(), ConfirmSuccess());
            gpu_perf_api_helper_.PrintGpaSampleResults(gpa_context_id_, gpa_session_id_, profile_set, AMDVulkanDemo::kGpaSampleIdWireframe,        print_debug_output_, Verify(), ConfirmSuccess());
            gpu_perf_api_helper_.PrintGpaSampleResults(gpa_context_id_, gpa_session_id_, profile_set, AMDVulkanDemo::kGpaSampleIdCubeAndWireframe, print_debug_output_, Verify(), ConfirmSuccess());

            // Close the CSV file so that it actually gets saved out.
            gpu_perf_api_helper_.CloseCSVFile();

            // Since the goal is to demonstrate GPUPerfAPI, the demo can optionally be exited now that the profile is complete.
            if (exit_after_profile_)
            {
                exit_ = true;
            }
        }
    }

    ++num_frames_rendered_;
}

void AMDVulkanDemo::Destroy()
{
    if (gpu_perf_api_helper_.IsLoaded())
    {
        if (gpa_session_id_ != nullptr)
        {
            GpaStatus gpa_delete_session_status = gpu_perf_api_helper_.gpa_function_table_->GpaDeleteSession(gpa_session_id_);

            if (gpa_delete_session_status != kGpaStatusOk)
            {
                gpu_perf_api_helper_.LogStatus(gpa_delete_session_status, "ERROR: Failed to delete GPA session.");
            }
        }

        if (gpa_context_id_ != nullptr)
        {
            GpaStatus gpa_close_context_status = gpu_perf_api_helper_.gpa_function_table_->GpaCloseContext(gpa_context_id_);

            if (gpa_close_context_status != kGpaStatusOk)
            {
                gpu_perf_api_helper_.LogStatus(gpa_close_context_status, "ERROR: Failed to close GPA Context.");
            }
        }
    }

    if (VK_NULL_HANDLE != vk_device_)
    {
        VkResult device_wait_idle_result = _vkDeviceWaitIdle(vk_device_);

        if (device_wait_idle_result != VK_SUCCESS)
        {
            AMDVulkanDemoVkUtils::Log("ERROR: Failed to wait for the device to idle.");
        }

        if (VK_NULL_HANDLE != vk_semaphore_acquired_swapchain_image_)
        {
            _vkDestroySemaphore(vk_device_, vk_semaphore_acquired_swapchain_image_, nullptr);
            vk_semaphore_acquired_swapchain_image_ = VK_NULL_HANDLE;
        }

        if (VK_NULL_HANDLE != vk_sempahore_fineshed_rendering_)
        {
            _vkDestroySemaphore(vk_device_, vk_sempahore_fineshed_rendering_, nullptr);
            vk_sempahore_fineshed_rendering_ = VK_NULL_HANDLE;
        }

        if (VK_NULL_HANDLE != vk_command_pool_)
        {
            _vkDestroyCommandPool(vk_device_, vk_command_pool_, nullptr);
            vk_command_pool_ = VK_NULL_HANDLE;
        }

        if (VK_NULL_HANDLE != vk_pipeline_layout_)
        {
            _vkDestroyPipelineLayout(vk_device_, vk_pipeline_layout_, nullptr);
            vk_pipeline_layout_ = VK_NULL_HANDLE;
        }

        if (VK_NULL_HANDLE != vertex_shader_module_)
        {
            _vkDestroyShaderModule(vk_device_, vertex_shader_module_, nullptr);
            vertex_shader_module_ = VK_NULL_HANDLE;
        }

        if (VK_NULL_HANDLE != fragment_shader_module_)
        {
            _vkDestroyShaderModule(vk_device_, fragment_shader_module_, nullptr);
            fragment_shader_module_ = VK_NULL_HANDLE;
        }

        if (VK_NULL_HANDLE != vk_pipeline_)
        {
            _vkDestroyPipeline(vk_device_, vk_pipeline_, nullptr);
            vk_pipeline_ = VK_NULL_HANDLE;
        }

        if (VK_NULL_HANDLE != fragment_shader_wire_frame_module_)
        {
            _vkDestroyShaderModule(vk_device_, fragment_shader_wire_frame_module_, nullptr);
            fragment_shader_wire_frame_module_ = VK_NULL_HANDLE;
        }

        if (VK_NULL_HANDLE != vk_pipeline_wire_frame_)
        {
            _vkDestroyPipeline(vk_device_, vk_pipeline_wire_frame_, nullptr);
            vk_pipeline_ = VK_NULL_HANDLE;
        }

        if (VK_NULL_HANDLE != vk_render_pass_initial_)
        {
            _vkDestroyRenderPass(vk_device_, vk_render_pass_initial_, nullptr);
            vk_render_pass_initial_ = VK_NULL_HANDLE;
        }

        if (VK_NULL_HANDLE != vk_render_pass_mid_)
        {
            _vkDestroyRenderPass(vk_device_, vk_render_pass_mid_, nullptr);
            vk_render_pass_mid_ = VK_NULL_HANDLE;
        }

        if (VK_NULL_HANDLE != vk_render_pass_final_)
        {
            _vkDestroyRenderPass(vk_device_, vk_render_pass_final_, nullptr);
            vk_render_pass_final_ = VK_NULL_HANDLE;
        }

        for (uint32_t i = 0; i < per_swap_chain_image_resources_.vk_frame_buffers.size(); ++i)
        {
            _vkDestroyFramebuffer(vk_device_, per_swap_chain_image_resources_.vk_frame_buffers[i], nullptr);
        }

        per_swap_chain_image_resources_.vk_frame_buffers.clear();

        for (uint32_t i = 0; i < per_swap_chain_image_resources_.swap_chain_image_views.size(); ++i)
        {
            VkImageView& view = per_swap_chain_image_resources_.swap_chain_image_views[i];

            if (VK_NULL_HANDLE != view)
            {
                _vkDestroyImageView(vk_device_, view, nullptr);
            }
        }

        per_swap_chain_image_resources_.swap_chain_image_views.clear();

        if (VK_NULL_HANDLE != vk_swap_chain_)
        {
            _vkDestroySwapchainKHR(vk_device_, vk_swap_chain_, nullptr);
            vk_swap_chain_ = VK_NULL_HANDLE;
        }

        _vkDestroyDevice(vk_device_, nullptr);
        vk_device_ = VK_NULL_HANDLE;
    }

    if (VK_NULL_HANDLE != vk_instance_)
    {
        if (VK_NULL_HANDLE != vk_surface_)
        {
            _vkDestroySurfaceKHR(vk_instance_, vk_surface_, nullptr);
            vk_surface_ = VK_NULL_HANDLE;
        }

        if (VK_NULL_HANDLE != vk_debug_report_callback_)
        {
            _vkDestroyDebugReportCallbackEXT(vk_instance_, vk_debug_report_callback_, nullptr);
            vk_debug_report_callback_ = VK_NULL_HANDLE;
        }

        _vkDestroyInstance(vk_instance_, NULL);
        vk_instance_ = VK_NULL_HANDLE;
    }

    if (gpu_perf_api_helper_.IsLoaded())
    {
        gpu_perf_api_helper_.gpa_function_table_->GpaDestroy();
        gpu_perf_api_helper_.Unload();
    }

#if defined(VK_USE_PLATFORM_XCB_KHR)

    if (nullptr != xcb_conntection_)
    {
        xcb_destroy_window(xcb_conntection_, xcb_window_);
        xcb_disconnect(xcb_conntection_);
        xcb_conntection_ = nullptr;
    }

    if (nullptr != xcb_atom_delete_window_)
    {
        free(xcb_atom_delete_window_);
        xcb_atom_delete_window_ = nullptr;
    }

#endif
}

bool AMDVulkanDemo::NoGpa()
{
    return nogpa_;
}

void AMDVulkanDemo::AddSupportedInstanceExtension(const char* extension_name)
{
    supported_instance_extensions_.insert(std::pair<const std::string, bool>(std::string(extension_name), true));
}

bool AMDVulkanDemo::IsInstanceExtensionSupported(const char* extension_name)
{
    return supported_instance_extensions_.end() != supported_instance_extensions_.find(std::string(extension_name));
}

void AMDVulkanDemo::AddSupportedDeviceExtension(const char* extension_name)
{
    supported_device_extensions_.insert(std::pair<const std::string, bool>(std::string(extension_name), true));
}

bool AMDVulkanDemo::IsDeviceExtensionSupported(const char* extension_name)
{
    return supported_device_extensions_.end() != supported_device_extensions_.find(std::string(extension_name));
}

void AMDVulkanDemo::PreBuildCommandBuffers(PrebuiltPerFrameResources* prebuilt_resources, VkFramebuffer frame_buffer, bool enable_gpa, uint32_t gpa_pass_index)
{
    // Setup some standard structs that can be used for all sets of CommandBuffers since they all come from the same pool.

    // Information about allocating command buffers.
    VkCommandBufferAllocateInfo command_buffer_alloc_info = {};
    command_buffer_alloc_info.sType                       = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    command_buffer_alloc_info.pNext                       = nullptr;
    command_buffer_alloc_info.commandPool                 = vk_command_pool_;
    command_buffer_alloc_info.level                       = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    command_buffer_alloc_info.commandBufferCount          = 1;

    // Information about beginning a command buffer.
    VkCommandBufferBeginInfo command_buffer_begin_info = {};
    command_buffer_begin_info.pNext                    = nullptr;
    command_buffer_begin_info.sType                    = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    command_buffer_begin_info.flags                    = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
    command_buffer_begin_info.pInheritanceInfo         = nullptr;

    // Create three viewports and scissors to divide the window into thirds.
    float      third_width_float = static_cast<float>(swap_chain_image_extent_.width / 3);
    uint32_t   third_width_uint  = swap_chain_image_extent_.width / 3;
    VkViewport viewports[3];
    VkRect2D   scissor_rects[3];

    for (uint32_t i = 0; i < 3; ++i)
    {
        viewports[i].x        = static_cast<float>(i * third_width_uint);
        viewports[i].y        = 0.0f;
        viewports[i].width    = third_width_float;
        viewports[i].height   = static_cast<float>(swap_chain_image_extent_.height);
        viewports[i].minDepth = 0.0f;
        viewports[i].maxDepth = 1.0f;

        scissor_rects[i].offset        = VkOffset2D({static_cast<int32_t>(i * third_width_uint), 0});
        scissor_rects[i].extent.width  = third_width_uint;
        scissor_rects[i].extent.height = swap_chain_image_extent_.height;
    }

    // Generate calls to draw the cube.
    {
        // Allocate a command buffer for the cube.
        VkResult allocate_command_buffers_result =
            _vkAllocateCommandBuffers(vk_device_, &command_buffer_alloc_info, &(prebuilt_resources->cube_.command_buffer));

        if (allocate_command_buffers_result != VK_SUCCESS)
        {
            AMDVulkanDemoVkUtils::Log("ERROR: Failed to allocate command buffers.");
            return;
        }

        _vkBeginCommandBuffer(prebuilt_resources->cube_.command_buffer, &command_buffer_begin_info);

        if (enable_gpa)
        {
            gpu_perf_api_helper_.gpa_function_table_->GpaBeginCommandList(gpa_session_id_,
                                                                          gpa_pass_index,
                                                                          prebuilt_resources->cube_.command_buffer,
                                                                          kGpaCommandListPrimary,
                                                                          &prebuilt_resources->cube_.gpa_command_list_id);
        }

        VkClearValue clear_color = {0.0f, 0.0f, 0.0f, 1.0f};

        VkRenderPassBeginInfo render_pass_begin_info = {};
        render_pass_begin_info.sType                 = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        render_pass_begin_info.pNext                 = nullptr;
        render_pass_begin_info.renderPass            = vk_render_pass_initial_;
        render_pass_begin_info.framebuffer           = frame_buffer;
        render_pass_begin_info.renderArea.offset     = {0, 0};
        render_pass_begin_info.renderArea.extent     = swap_chain_image_extent_;
        render_pass_begin_info.clearValueCount       = 1;
        render_pass_begin_info.pClearValues          = &clear_color;

        _vkCmdBeginRenderPass(prebuilt_resources->cube_.command_buffer, &render_pass_begin_info, VK_SUBPASS_CONTENTS_INLINE);

        _vkCmdSetViewport(prebuilt_resources->cube_.command_buffer, 0, 1, &viewports[0]);
        _vkCmdSetScissor(prebuilt_resources->cube_.command_buffer, 0, 1, &scissor_rects[0]);

        _vkCmdBindPipeline(prebuilt_resources->cube_.command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, vk_pipeline_);

        if (enable_gpa)
        {
            gpu_perf_api_helper_.gpa_function_table_->GpaBeginSample(prebuilt_resources->cube_.gpa_sample_id, prebuilt_resources->cube_.gpa_command_list_id);
        }

        _vkCmdDraw(prebuilt_resources->cube_.command_buffer, 36, 1, 0, 0);

        if (enable_gpa)
        {
            gpu_perf_api_helper_.gpa_function_table_->GpaEndSample(prebuilt_resources->cube_.gpa_command_list_id);
        }

        _vkCmdEndRenderPass(prebuilt_resources->cube_.command_buffer);

        if (enable_gpa)
        {
            gpu_perf_api_helper_.gpa_function_table_->GpaEndCommandList(prebuilt_resources->cube_.gpa_command_list_id);
        }

        VkResult end_cmd_buffer_result = _vkEndCommandBuffer(prebuilt_resources->cube_.command_buffer);

        if (end_cmd_buffer_result != VK_SUCCESS)
        {
            AMDVulkanDemoVkUtils::Log("ERROR: Failed to end command buffer.");
        }
    }

    // Now generate calls to overlay the wireframe.
    {
        VkResult allocate_command_buffers_result =
            _vkAllocateCommandBuffers(vk_device_, &command_buffer_alloc_info, &(prebuilt_resources->wire_frame_.command_buffer));

        if (allocate_command_buffers_result != VK_SUCCESS)
        {
            AMDVulkanDemoVkUtils::Log("ERROR: Failed to allocate wireframe command buffers.");
            return;
        }

        _vkBeginCommandBuffer(prebuilt_resources->wire_frame_.command_buffer, &command_buffer_begin_info);

        if (enable_gpa)
        {
            gpu_perf_api_helper_.gpa_function_table_->GpaBeginCommandList(gpa_session_id_,
                                                                          gpa_pass_index,
                                                                          prebuilt_resources->wire_frame_.command_buffer,
                                                                          kGpaCommandListPrimary,
                                                                          &prebuilt_resources->wire_frame_.gpa_command_list_id);
        }

        VkRenderPassBeginInfo render_pass_begin_info_wire_frame = {};
        render_pass_begin_info_wire_frame.sType                 = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        render_pass_begin_info_wire_frame.pNext                 = nullptr;
        render_pass_begin_info_wire_frame.renderPass            = vk_render_pass_mid_;
        render_pass_begin_info_wire_frame.framebuffer           = frame_buffer;
        render_pass_begin_info_wire_frame.renderArea.offset     = {1 * static_cast<int32_t>(swap_chain_image_extent_.width) / 3, 0};
        render_pass_begin_info_wire_frame.renderArea.extent     = swap_chain_image_extent_;
        render_pass_begin_info_wire_frame.renderArea.extent.width /= 3u;
        render_pass_begin_info_wire_frame.clearValueCount = 0;
        render_pass_begin_info_wire_frame.pClearValues    = nullptr;

        _vkCmdBeginRenderPass(prebuilt_resources->wire_frame_.command_buffer, &render_pass_begin_info_wire_frame, VK_SUBPASS_CONTENTS_INLINE);

        _vkCmdSetViewport(prebuilt_resources->wire_frame_.command_buffer, 0, 1, &viewports[1]);
        _vkCmdSetScissor(prebuilt_resources->wire_frame_.command_buffer, 0, 1, &scissor_rects[1]);

        _vkCmdBindPipeline(prebuilt_resources->wire_frame_.command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, vk_pipeline_wire_frame_);

        if (enable_gpa)
        {
            gpu_perf_api_helper_.gpa_function_table_->GpaBeginSample(prebuilt_resources->wire_frame_.gpa_sample_id,
                                                                     prebuilt_resources->wire_frame_.gpa_command_list_id);
        }

        _vkCmdDraw(prebuilt_resources->wire_frame_.command_buffer, 36, 1, 0, 0);

        if (enable_gpa)
        {
            gpu_perf_api_helper_.gpa_function_table_->GpaEndSample(prebuilt_resources->wire_frame_.gpa_command_list_id);
        }

        _vkCmdEndRenderPass(prebuilt_resources->wire_frame_.command_buffer);

        if (enable_gpa)
        {
            gpu_perf_api_helper_.gpa_function_table_->GpaEndCommandList(prebuilt_resources->wire_frame_.gpa_command_list_id);
        }

        VkResult end_command_buffer_wire_frame_result = _vkEndCommandBuffer(prebuilt_resources->wire_frame_.command_buffer);

        if (end_command_buffer_wire_frame_result != VK_SUCCESS)
        {
            AMDVulkanDemoVkUtils::Log("ERROR: Failed to end wireframe command buffer.");
        }
    }

    // Generate calls to draw the cube in one command buffer, the wireframe in a second command buffer,
    // and have a GPA Sample continue between the two command buffers.
    {
        // Allocate a command buffer for the cube.
        VkResult allocate_command_buffers_result =
            _vkAllocateCommandBuffers(vk_device_, &command_buffer_alloc_info, &(prebuilt_resources->cube_and_wire_frame_.command_buffer_cube));

        if (allocate_command_buffers_result != VK_SUCCESS)
        {
            AMDVulkanDemoVkUtils::Log("ERROR: Failed to allocate command buffers.");
            return;
        }

        _vkBeginCommandBuffer(prebuilt_resources->cube_and_wire_frame_.command_buffer_cube, &command_buffer_begin_info);

        if (enable_gpa)
        {
            gpu_perf_api_helper_.gpa_function_table_->GpaBeginCommandList(gpa_session_id_,
                                                                          gpa_pass_index,
                                                                          prebuilt_resources->cube_and_wire_frame_.command_buffer_cube,
                                                                          kGpaCommandListPrimary,
                                                                          &prebuilt_resources->cube_and_wire_frame_.gpa_command_list_id_cube);
        }

        VkRenderPassBeginInfo render_pass_begin_info = {};
        render_pass_begin_info.sType                 = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        render_pass_begin_info.pNext                 = nullptr;
        render_pass_begin_info.renderPass            = vk_render_pass_mid_;
        render_pass_begin_info.framebuffer           = frame_buffer;
        render_pass_begin_info.renderArea.offset     = {2 * static_cast<int32_t>(swap_chain_image_extent_.width) / 3, 0};
        render_pass_begin_info.renderArea.extent     = swap_chain_image_extent_;
        render_pass_begin_info.renderArea.extent.width /= 3u;
        render_pass_begin_info.clearValueCount = 0;
        render_pass_begin_info.pClearValues    = nullptr;

        _vkCmdBeginRenderPass(prebuilt_resources->cube_and_wire_frame_.command_buffer_cube, &render_pass_begin_info, VK_SUBPASS_CONTENTS_INLINE);

        _vkCmdSetViewport(prebuilt_resources->cube_and_wire_frame_.command_buffer_cube, 0, 1, &viewports[2]);
        _vkCmdSetScissor(prebuilt_resources->cube_and_wire_frame_.command_buffer_cube, 0, 1, &scissor_rects[2]);

        _vkCmdBindPipeline(prebuilt_resources->cube_and_wire_frame_.command_buffer_cube, VK_PIPELINE_BIND_POINT_GRAPHICS, vk_pipeline_);

        if (enable_gpa)
        {
            gpu_perf_api_helper_.gpa_function_table_->GpaBeginSample(prebuilt_resources->cube_and_wire_frame_.gpa_sample_id,
                                                                     prebuilt_resources->cube_and_wire_frame_.gpa_command_list_id_cube);
        }

        _vkCmdDraw(prebuilt_resources->cube_and_wire_frame_.command_buffer_cube, 36, 1, 0, 0);

        // COMMENT FOR DEMONSTRATION PURPOSES:
        // Do not end the GPA Sample, because it will be continued on another command list.
        //if (enable_gpa)
        //{
        //    m_GpuPerfApiHelperHelper.gpa_function_table_->GpaEndSample(prebuilt_resources->cube_and_wire_frame_.gpa_command_list_id);
        //}

        _vkCmdEndRenderPass(prebuilt_resources->cube_and_wire_frame_.command_buffer_cube);

        if (enable_gpa)
        {
            gpu_perf_api_helper_.gpa_function_table_->GpaEndCommandList(prebuilt_resources->cube_and_wire_frame_.gpa_command_list_id_cube);
        }

        VkResult end_cmd_buffer_result = _vkEndCommandBuffer(prebuilt_resources->cube_and_wire_frame_.command_buffer_cube);

        if (end_cmd_buffer_result != VK_SUCCESS)
        {
            AMDVulkanDemoVkUtils::Log("ERROR: Failed to end command buffer.");
        }
    }

    // Now generate calls to overlay the wireframe
    {
        VkResult allocate_command_buffers_result =
            _vkAllocateCommandBuffers(vk_device_, &command_buffer_alloc_info, &(prebuilt_resources->cube_and_wire_frame_.command_buffer_wire_frame));

        if (allocate_command_buffers_result != VK_SUCCESS)
        {
            AMDVulkanDemoVkUtils::Log("ERROR: Failed to allocate wireframe command buffers.");
            return;
        }

        _vkBeginCommandBuffer(prebuilt_resources->cube_and_wire_frame_.command_buffer_wire_frame, &command_buffer_begin_info);

        if (enable_gpa)
        {
            gpu_perf_api_helper_.gpa_function_table_->GpaBeginCommandList(gpa_session_id_,
                                                                          gpa_pass_index,
                                                                          prebuilt_resources->cube_and_wire_frame_.command_buffer_wire_frame,
                                                                          kGpaCommandListPrimary,
                                                                          &prebuilt_resources->cube_and_wire_frame_.gpa_command_list_id_wire_frame);

            // COMMENT FOR DEMONSTRATION PURPOSES:
            // Tell GPA that a sample that has previously been started will be continued onto the GPACommandListId that was just begun.
            gpu_perf_api_helper_.gpa_function_table_->GpaContinueSampleOnCommandList(prebuilt_resources->cube_and_wire_frame_.gpa_sample_id,
                                                                                     prebuilt_resources->cube_and_wire_frame_.gpa_command_list_id_wire_frame);
        }

        VkRenderPassBeginInfo render_pass_begin_info_wire_frame = {};
        render_pass_begin_info_wire_frame.sType                 = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        render_pass_begin_info_wire_frame.pNext                 = nullptr;
        render_pass_begin_info_wire_frame.renderPass            = vk_render_pass_final_;
        render_pass_begin_info_wire_frame.framebuffer           = frame_buffer;
        render_pass_begin_info_wire_frame.renderArea.offset     = {2 * static_cast<int32_t>(swap_chain_image_extent_.width) / 3, 0};
        render_pass_begin_info_wire_frame.renderArea.extent     = swap_chain_image_extent_;
        render_pass_begin_info_wire_frame.renderArea.extent.width /= 3u;
        render_pass_begin_info_wire_frame.clearValueCount = 0;
        render_pass_begin_info_wire_frame.pClearValues    = nullptr;

        _vkCmdBeginRenderPass(
            prebuilt_resources->cube_and_wire_frame_.command_buffer_wire_frame, &render_pass_begin_info_wire_frame, VK_SUBPASS_CONTENTS_INLINE);

        _vkCmdSetViewport(prebuilt_resources->cube_and_wire_frame_.command_buffer_wire_frame, 0, 1, &viewports[2]);
        _vkCmdSetScissor(prebuilt_resources->cube_and_wire_frame_.command_buffer_wire_frame, 0, 1, &scissor_rects[2]);

        _vkCmdBindPipeline(prebuilt_resources->cube_and_wire_frame_.command_buffer_wire_frame, VK_PIPELINE_BIND_POINT_GRAPHICS, vk_pipeline_wire_frame_);

        // COMMENT FOR DEMONSTRATION PURPOSES:
        // Do not begin a GPA Sample here, because it is automatically continued by GPA_ContinueSampleOnCommandList() above.
        //if (enable_gpa)
        //{
        //    gpu_perf_api_helper_.gpa_function_table_->GpaBeginSample(prebuilt_resources->cube_and_wire_frame_.gpa_sample_id, prebuilt_resources->cube_and_wire_frame_.gpa_command_list_id_wire_frame);
        //}

        _vkCmdDraw(prebuilt_resources->cube_and_wire_frame_.command_buffer_wire_frame, 36, 1, 0, 0);

        if (enable_gpa)
        {
            gpu_perf_api_helper_.gpa_function_table_->GpaEndSample(prebuilt_resources->cube_and_wire_frame_.gpa_command_list_id_wire_frame);
        }

        _vkCmdEndRenderPass(prebuilt_resources->cube_and_wire_frame_.command_buffer_wire_frame);

        if (enable_gpa)
        {
            gpu_perf_api_helper_.gpa_function_table_->GpaEndCommandList(prebuilt_resources->cube_and_wire_frame_.gpa_command_list_id_wire_frame);
        }

        VkResult end_command_buffer_wire_frame_result = _vkEndCommandBuffer(prebuilt_resources->cube_and_wire_frame_.command_buffer_wire_frame);

        if (end_command_buffer_wire_frame_result != VK_SUCCESS)
        {
            AMDVulkanDemoVkUtils::Log("ERROR: Failed to end wireframe command buffer.");
        }
    }
}

#if defined(VK_USE_PLATFORM_WIN32_KHR)

/// Window message processing callback.
LRESULT CALLBACK demoWindowMessageProcessorWin32(HWND window_handle, UINT message, WPARAM w_param, LPARAM l_param)
{
    switch (message)
    {
    case WM_DESTROY:
    {
        PostQuitMessage(0);
        return 0;
    }

    case WM_PAINT:
    {
        AMDVulkanDemo& app = *(reinterpret_cast<AMDVulkanDemo*>(GetWindowLongPtrW(window_handle, GWLP_USERDATA)));

        // Only draw if the demo has been initialized successfully. This may not be the case
        // if there was an error during initialization which would display a message box and
        // cause the window to paint. If this happens, skip drawing and let the default windowing
        // behavior occur.
        if (app.Initialized())
        {
            app.DrawScene();
            return 0;
        }
    }

    default:
        return DefWindowProc(window_handle, message, w_param, l_param);
    }
}

/// Main entry point for Windows applications.
int WINAPI WinMain(_In_ HINSTANCE instance_handle, _In_opt_ HINSTANCE previous_instance, _In_ LPSTR cmd_line, _In_ int cmd_show)
{
    UNREFERENCED_PARAMETER(previous_instance);
    UNREFERENCED_PARAMETER(cmd_line);

    MSG message;
    memset(&message, 0, sizeof(MSG));

    gpa_example::CmdlineParser parser(__argc, __argv);

    AMDVulkanDemo app(AMDT_PROJECT_NAME, parser);

    if (!app.Initialize())
    {
        return -1;
    }

    // Setting log and data file names in GPAHelper based on command line input.
    GpaHelper::gpa_log_file_name = app.Logfile();
    GpaHelper::csv_file_name     = app.Datafile();

    // Include known issues in counter validation.
    GpaHelper::include_known_issues = app.IncludeKnownIssues();

    // First load GPUPerfAPI if needed.
    if (!app.NoGpa())
    {
        if (!app.InitializeGpa())
        {
            return -1;
        }
    }

    // Create a window for the demo to render into before initializing Vulkan since the window
    // surface is needed as part of the vulkan initialization.
    app.InitializeWindowWin32(instance_handle, demoWindowMessageProcessorWin32, cmd_show);

    if (app.GetWindowWin32() == nullptr)
    {
        return -1;
    }

    if (!app.InitializeVulkan())
    {
        return -1;
    }

    // Main message loop.
    while (!app.Exit())
    {
        PeekMessage(&message, NULL, 0, 0, PM_REMOVE);

        if (message.message == WM_QUIT)
        {
            app.Exit(true);
        }
        else
        {
            // Translate and dispatch to event queue.
            TranslateMessage(&message);
            DispatchMessage(&message);
        }

        RedrawWindow(app.GetWindowWin32(), NULL, NULL, RDW_INTERNALPAINT);
    }

    int return_value = static_cast<int>(message.wParam);

    if (0 == return_value)
    {
        return_value = GpaHelper::gpa_any_errors_logged ? GpaHelper::gpa_num_errors_logged : 0;
    }

    return return_value;
}

#elif defined(VK_USE_PLATFORM_XCB_KHR)

/// Window message processing callback.
void demoWindowMessageProcessorXcb(AMDVulkanDemo& app, xcb_generic_event_t* event)
{
    uint8_t event_code = event->response_type & ~0x80;

    switch (event_code)
    {
    case XCB_CLIENT_MESSAGE:
    {
        const xcb_client_message_event_t* client_message = (const xcb_client_message_event_t*)event;

        if (client_message->data.data32[0] == app.xcb_atom_delete_window_->atom)
        {
            app.Exit(true);
        }
    }

    case XCB_KEY_RELEASE:
    {
        const xcb_key_release_event_t* key_release = (const xcb_key_release_event_t*)event;

        //std::cout << "DEBUG: Key Release detail: '" << (uint32_t)key_release->detail << "'." << std::endl;

        if (key_release->detail == 0x9)  // Escape key.
        {
            app.Exit(true);
        }
    }
    }
}

int main(const int argc, const char* argv[])
{
    UNREFERENCED_PARAMETER(argc);
    UNREFERENCED_PARAMETER(argv);

    gpa_example::CmdlineParser parser(argc, const_cast<char**>(argv));

    AMDVulkanDemo app(AMDT_PROJECT_NAME, parser);

    // Setting log and data file names in GPAHelper based on command line input.
    GpaHelper::gpa_log_file_name = app.Logfile();
    GpaHelper::csv_file_name     = app.Datafile();

    if (!app.Initialize())
    {
        return -1;
    }

    // Setting log and data file names in GPAHelper based on command line input.
    GpaHelper::gpa_log_file_name = app.Logfile();
    GpaHelper::csv_file_name     = app.Datafile();

    // Include known issues in counter validation.
    GpaHelper::include_known_issues = app.IncludeKnownIssues();

    // First load GPUPerfAPI if needed.
    if (!app.NoGpa())
    {
        if (!app.InitializeGpa())
        {
            return -1;
        }
    }

    // Create a window for the demo to render into before initializing Vulkan since the window
    // surface is needed as part of the vulkan initialization.
    xcb_connection_t* connection = app.InitializeWindowXcb();

    if (connection == nullptr)
    {
        return -1;
    }

    if (!app.InitializeVulkan())
    {
        return -1;
    }

    xcb_flush(connection);
    xcb_generic_event_t* event;

    // Main message loop.
    while (!app.Exit())
    {
        event = xcb_poll_for_event(connection);

        while (event)
        {
            demoWindowMessageProcessorXcb(app, event);
            free(event);
            event = xcb_poll_for_event(connection);
        }

        // Only draw if the demo has been initialized successfully. This may not be the case
        // if there was an error during initialization which would display a message box and
        // cause the window to paint. If this happens, skip drawing and let the default windowing
        // behavior occur.
        if (app.Initialized())
        {
            app.DrawScene();
        }
    }

    return GpaHelper::gpa_any_errors_logged ? GpaHelper::gpa_num_errors_logged : 0;
}

#endif
