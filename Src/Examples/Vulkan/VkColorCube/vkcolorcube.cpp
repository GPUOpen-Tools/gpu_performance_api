//==============================================================================
// Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Vulkan Color Cube Sample
//==============================================================================

// platform-specific headers
#ifdef _WIN32
    // Tell the linker that this is a windowed app, not a console app;
    // defining this in code allows for flexibility with other operating systems.
    #pragma comment(linker, "/subsystem:windows")
    #define VK_USE_PLATFORM_WIN32_KHR
#endif  // _WIN32

#ifdef __linux__
    #define VK_USE_PLATFORM_XCB_KHR
#endif // __linux__

// Headers needed on all platforms
#include <algorithm>
#include <assert.h>
#include <chrono>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <thread>
#include <vector>
#include <vulkan/vulkan.h>
#include "GPAInterfaceLoader.h"
#include "GPUPerfAPI-VK.h"

#if defined(VK_USE_PLATFORM_XCB_KHR) || defined(VK_USE_PLATFORM_XLIB_KHR)
    #include <X11/Xutil.h>
    #include <xcb/xcb.h>
    #include <dlfcn.h>
    #include <unistd.h>
#endif

// Macro to simplify querying instance procedure addresses and reporting & returning errors.
#define VK_INSTANCE_GET_PROC_ADDR(result, instance, func)                           \
    result = (PFN_##func)vkGetInstanceProcAddr(instance, #func);                    \
    if (result == nullptr) {                                                        \
        std::cout << "ERROR: Failed getting entrypoint '" #func "'" << std::endl;   \
        return false;                                                               \
    }

// Macro to simplify querying instance procedure addresses and reporting errors.
#define VK_INSTANCE_GET_PROC_ADDR_VOID(result, instance, func)                      \
    result = (PFN_##func)vkGetInstanceProcAddr(instance, #func);                    \
    if (result == nullptr) {                                                        \
        std::cout << "ERROR: Failed getting entrypoint '" #func "'" << std::endl;   \
    }

/// Callback that will be registered with the VK_KHR_debug_report extension
/// so that the validation layers can report debugging messages.
static VKAPI_ATTR VkBool32 VKAPI_CALL debugReportCallback(
    VkDebugReportFlagsEXT flags,
    VkDebugReportObjectTypeEXT objType,
    uint64_t obj,
    size_t location,
    int32_t code,
    const char* layerPrefix,
    const char* msg,
    void* userData)
{
    UNREFERENCED_PARAMETER(flags);
    UNREFERENCED_PARAMETER(objType);
    UNREFERENCED_PARAMETER(obj);
    UNREFERENCED_PARAMETER(location);
    UNREFERENCED_PARAMETER(code);
    UNREFERENCED_PARAMETER(layerPrefix);
    UNREFERENCED_PARAMETER(userData);

    std::cout << "ERROR: validation layer: " << msg << std::endl;

    return VK_FALSE;
}

/// Callback function for any error messages that GPUPerfAPI produces.
/// \param type The type of logging message.
/// \param msg The message.
void gpaLoggingCallback(
    GPA_Logging_Type type,
    const char* msg)
{
    switch (type)
    {
        case GPA_LOGGING_ERROR:
            std::cout << "GPA ERROR: ";
            break;

        case GPA_LOGGING_TRACE:
            std::cout << "GPA TRACE: ";
            break;

        default:
            std::cout << "GPA: ";
            break;
    }

    std::cout << msg << std::endl;
}

GPAApiManager* GPAApiManager::m_pGpaApiManager = nullptr;
GPAFuncTableInfo* g_pFuncTableInfo = nullptr;

/// Class that demonstrates one approach to loading GPUPerfAPI and into an application.
/// It can query the addresses of all GPA entrypoints, and has utility functions to demonstrate
/// how to access information about the available counters, as well as how to query the profile
/// result for a given sample Id.
class GPUPerfAPI
{
public:

    /// Constructor
    GPUPerfAPI():
        m_pGpaFuncTable(nullptr),
        m_bHeaderWritten(false)
    {
    }

    /// Destructor
    ~GPUPerfAPI()
    {
        if (IsLoaded())
        {
            Unload();
        }
    }

    /// Indicates whether or not the GPA library is loaded.
    bool IsLoaded() const
    {
        return m_pGpaFuncTable != nullptr;
    }

    /// Loads the necessary GPUPerfAPI library.
    /// \return True if the library loaded successfully; false otherwise.
    bool Load()
    {
        bool success = GPA_STATUS_OK == GPAApiManager::Instance()->LoadApi(GPA_API_VULKAN);

        if (success)
        {
            m_pGpaFuncTable = GPAApiManager::Instance()->GetFunctionTable(GPA_API_VULKAN);
        }

        return success;
    }

    /// Unloads the GPUPerfAPI library.
    void Unload()
    {
        if (IsLoaded())
        {
            GPAApiManager::Instance()->UnloadApi(GPA_API_VULKAN);
        }

        m_pGpaFuncTable = nullptr;
    }

    /// Print the available counters from the specified context.
    /// \param contextId A valid GPA Context ID.
    void PrintGPACounterInfo(GPA_ContextId contextId) const
    {
        gpa_uint32 numCounters = 0;
        GPA_Status gpaStatus = m_pGpaFuncTable->GPA_GetNumCounters(contextId, &numCounters);

        if (GPA_STATUS_OK != gpaStatus)
        {
            std::cout << "ERROR: Failed to get the number of available counters." << std::endl;
            return;
        }

        for (gpa_uint32 counterIndex = 0; counterIndex < numCounters; counterIndex++)
        {
            const char* pName = NULL;
            GPA_Status nameStatus = m_pGpaFuncTable->GPA_GetCounterName(contextId, counterIndex, &pName);

            const char* pGroup = NULL;
            GPA_Status groupStatus = m_pGpaFuncTable->GPA_GetCounterGroup(contextId, counterIndex, &pGroup);

            const char* pDescription = NULL;
            GPA_Status descStatus = m_pGpaFuncTable->GPA_GetCounterDescription(contextId, counterIndex, &pDescription);

            if (GPA_STATUS_OK == nameStatus &&
                GPA_STATUS_OK == groupStatus &&
                GPA_STATUS_OK == descStatus)
            {
                std::cout << counterIndex << ": " << pName << " \"" << pGroup << "\" - " << pDescription << std::endl;
            }
            else
            {
                std::cout << "ERROR: Failed to get counter name, group, or description." << std::endl;
            }
        }
    }

    /// Opens the CSV file to output profile results.
    /// \return True if the csv file was successfully opened; false otherwise.
    bool OpenCSVFile()
    {
        m_csvFile.open(m_csvFileName.c_str(), std::ios_base::out | std::ios_base::app);

        return m_csvFile.is_open();
    }

    /// Closes the CSV File so that it gets saved to disk.
    void CloseCSVFile()
    {
        m_csvFile.close();
    }

    /// Print counter results from a specific sample.
    /// If the CSV file is open, then the results will be written the CSV file too.
    /// \param contextId A valid Context ID.
    /// \param sessionId A valid Session ID.
    /// \param sampleId A valid Sample ID.
    void PrintGPASampleResults(GPA_ContextId contextId, GPA_SessionId sessionId, gpa_uint32 sampleId)
    {
        std::cout << "--------------------------------------------------" << std::endl;
        std::cout << "Sample ID: " << sampleId << std::endl;

        size_t sampleResultSizeInBytes = 0;
        GPA_Status gpaStatus = m_pGpaFuncTable->GPA_GetSampleResultSize(sessionId, sampleId, &sampleResultSizeInBytes);

        if (GPA_STATUS_OK != gpaStatus)
        {
            std::cout << "ERROR: Failed to get GPA sample result size." << std::endl;
            return;
        }

        gpa_uint64* pResultsBuffer = (gpa_uint64*)malloc(sampleResultSizeInBytes);

        if (pResultsBuffer == nullptr)
        {
            std::cout << "ERROR: Failed to allocate memory for GPA results." << std::endl;
            return;
        }

        gpaStatus = m_pGpaFuncTable->GPA_GetSampleResult(sessionId, sampleId, sampleResultSizeInBytes, pResultsBuffer);

        if (GPA_STATUS_OK != gpaStatus)
        {
            std::cout << "ERROR: Failed to get GPA sample results." << std::endl;
        }
        else
        {
            gpa_uint32 enabledCount = 0;
            gpaStatus = m_pGpaFuncTable->GPA_GetNumEnabledCounters(sessionId, &enabledCount);

            if (GPA_STATUS_OK != gpaStatus)
            {
                std::cout << "ERROR: Failed to get the number of enabled counters from GPA." << std::endl;
            }
            else
            {
                std::stringstream csvHeader;
                std::stringstream csvContent;

                for (gpa_uint32 i = 0; i < enabledCount; i++)
                {
                    gpa_uint32 counterIndex = 0;
                    gpaStatus = m_pGpaFuncTable->GPA_GetEnabledIndex(sessionId, i, &counterIndex);

                    if (GPA_STATUS_OK != gpaStatus)
                    {
                        std::cout << "ERROR: Failed to get the exposed GPA counter id of the enabled counter at index " << counterIndex << "." << std::endl;
                    }
                    else
                    {
                        GPA_Data_Type counterType = GPA_DATA_TYPE_UINT64;
                        gpaStatus = m_pGpaFuncTable->GPA_GetCounterDataType(contextId, counterIndex, &counterType);
                        assert(GPA_STATUS_OK == gpaStatus);

                        const char* pCounterName = NULL;
                        gpaStatus = m_pGpaFuncTable->GPA_GetCounterName(contextId, counterIndex, &pCounterName);
                        assert(GPA_STATUS_OK == gpaStatus);

                        printf("Counter %u %s result: ", counterIndex, pCounterName);

                        if (m_csvFile.is_open() && !m_bHeaderWritten)
                        {
                            csvHeader << pCounterName << ",";
                        }

                        if (counterType == GPA_DATA_TYPE_UINT64)
                        {
                            printf("%llu\n", pResultsBuffer[i]);

                            if (m_csvFile.is_open())
                            {
                                csvContent << pResultsBuffer[i] << ",";
                            }
                        }
                        else if (counterType == GPA_DATA_TYPE_FLOAT64)
                        {
                            gpa_float64 fResult = ((gpa_float64*)pResultsBuffer)[i];
                            printf("%f\n", fResult);

                            if (m_csvFile.is_open())
                            {
                                csvContent << fResult << ",";
                            }
                        }
                        else
                        {
                            printf("unhandled type (%d).\n", counterType);

                            if (m_csvFile.is_open())
                            {
                                csvContent << "unhandled type,";
                            }
                        }
                    }
                }

                // Output the counter results to the csv file
                if (m_csvFile.is_open())
                {
                    if (!m_bHeaderWritten)
                    {
                        m_csvFile << csvHeader.str() << std::endl;
                        m_bHeaderWritten = true;
                    }

                    m_csvFile << csvContent.str() << std::endl;
                }
            }
        }

        free(pResultsBuffer);
    }

    GPAFunctionTable* m_pGpaFuncTable;

private:

    /// The file stream for writing the csv file.
    std::fstream m_csvFile;

    /// The name of the csv file that will be written.
    const std::string m_csvFileName = "counterData.csv";

    /// Flag to indicate if the header has been written in the csv file.
    bool m_bHeaderWritten;

} GPUPerfAPI;

/// \brief Stores all the data needed for this demo.
/// Assists with available and enabled extensions, but not much other functionality. The reason for this
/// is so that the majority of Vulkan-related functionality flows as a linear progression rather than being
/// split up into multiple smaller functions.
class AMDVulkanDemo
{
public:

    /// Constructor
    AMDVulkanDemo()
        :
#if defined(VK_USE_PLATFORM_WIN32_KHR)
        m_hInstance(nullptr),
        m_hWindow(nullptr),
#elif defined(VK_USE_PLATFORM_XCB_KHR)
        m_pDisplay(nullptr),
        m_pXcbConnection(nullptr),
        m_pXcbScreen(nullptr),
        m_xcbAtomWmDeleteWindow(nullptr),
#endif
        m_vkInstance(VK_NULL_HANDLE),
        m_vkPhysicalDevice(VK_NULL_HANDLE),
        m_vkDevice(VK_NULL_HANDLE),
        m_vkQueue(VK_NULL_HANDLE),
        m_vkSurface(VK_NULL_HANDLE),
        m_queueFamilyIndexGraphics(0),
        m_queueFamilyIndexPresent(0),
        m_vkSwapchain(VK_NULL_HANDLE),
        m_vkRenderPassInitial(VK_NULL_HANDLE),
        m_vkRenderPassMid(VK_NULL_HANDLE),
        m_vkRenderPassFinal(VK_NULL_HANDLE),
        m_vkPipelineLayout(VK_NULL_HANDLE),
        m_vkPipeline(VK_NULL_HANDLE),
        m_vkCommandPool(VK_NULL_HANDLE),
        m_vertexShaderModule(VK_NULL_HANDLE),
        m_fragmentShaderModule(VK_NULL_HANDLE),
        m_vkSemaphoreAcquiredSwapchainImage(VK_NULL_HANDLE),
        m_vkSemaphoreFinishedRendering(VK_NULL_HANDLE),
        m_vkDebugReportCallback(VK_NULL_HANDLE),
        m_GPAContextId(nullptr),
        m_GPASessionId(nullptr),
        m_requiredPassCount(0),
        m_frameCount(0),
        m_bPrintDebugOutput(false),
        m_bInitialized(false),
        m_bExit(false)
    {
        m_vkPhysicalDeviceProperties = {};
        m_vkPhysicalDeviceFeatures = {};
        m_vkPhysicalDeviceMemoryProperties = {};
        m_vkSurfaceFormat = {};
        m_vkPresentMode = VK_PRESENT_MODE_FIFO_KHR;
        m_vkSurfaceCapabilities = {};
        m_swapchainImageExtent = {};

        // Specifically setting this to 0 because it will be used to query a queue,
        // and the first queue available (ie: at the 0th index) is the desired one.
        m_queueIndex = 0;

        m_requiredInstanceExtensions =
        {
            VK_KHR_SURFACE_EXTENSION_NAME,
            VK_EXT_DEBUG_REPORT_EXTENSION_NAME,
            AMD_GPA_REQUIRED_INSTANCE_EXTENSION_NAME_LIST,
#if defined(VK_USE_PLATFORM_WIN32_KHR)
            VK_KHR_WIN32_SURFACE_EXTENSION_NAME
#elif defined(VK_USE_PLATFORM_XCB_KHR)
            VK_KHR_XCB_SURFACE_EXTENSION_NAME
#endif
        };

        m_requiredDeviceExtensions =
        {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME,
            AMD_GPA_REQUIRED_DEVICE_EXTENSION_NAME_LIST
        };
    }

    /// Destructor
    ~AMDVulkanDemo()
    {
        Destroy();
    }

    /// Indicates whether or not the app should exit.
    /// \return true if the app should exit; false otherwise;
    bool Exit()
    {
        return m_bExit;
    }

    /// Sets whether or not the demo should exit at the next appropriate opportunity.
    /// \param bExit True to indicate that the demo should exit at the next appropriate opportunity;
    ///              False will clear the exit flag, but this may not prevent the demo from exiting if the exit process has already started.
    void Exit(bool bExit)
    {
        m_bExit = bExit;
    }

    /// Sets whether or not to print GPA Counter names & description on GPA initialization.
    /// \param bPrint True to print counter info; false to prevent it from printing.
    void SetPrintGPACounterInfo(bool bPrint)
    {
        m_bPrintGPACounterInfo = bPrint;
    }

    /// Sets whether or not to print debug output.
    /// \param bPrint True to print debug output; false to prevent debug output from being printed.
    void SetPrintDebugOutput(bool bPrint)
    {
        m_bPrintDebugOutput = bPrint;
    }

    /// Indicates that the Demo has been fully initialized.
    /// \return True if initialization has completed; false otherwise.
    bool Initialized()
    {
        return m_bInitialized;
    }

#ifdef VK_USE_PLATFORM_WIN32_KHR
    /// Registers a new window class and creates a window from that class.
    /// \param demoWindowProcessor Callback function to process windowing messages.
    /// \return Handle to the created window, or nullptr on error;
    HWND CreateWindowWin32(WNDPROC demoWindowProcessor)
    {
        HWND hWindow = nullptr;
        WNDCLASS windowClass;
        memset(&windowClass, 0, sizeof(WNDCLASS));
        windowClass.style = CS_HREDRAW | CS_VREDRAW;
        windowClass.hInstance = m_hInstance;
        windowClass.lpfnWndProc = demoWindowProcessor;
        windowClass.lpszClassName = "GPA Demo Window Class";
        windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
        windowClass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);

        if (RegisterClassA(&windowClass))
        {
            hWindow = CreateWindowEx(
                          0,
                          windowClass.lpszClassName,
                          m_cLongName.c_str(),
                          WS_OVERLAPPED | WS_VISIBLE | WS_SYSMENU,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          static_cast<int>(m_cDefaultWindowWidth),
                          static_cast<int>(m_cDefaultWindowHeight),
                          nullptr,
                          nullptr,
                          m_hInstance,
                          nullptr
                      );
        }

        return hWindow;
    }

    /// Initialize a window on Win32 platformas.
    /// \param hInstance The application instance handle.
    /// \param windowMessageProcessor The function that will process window messages.
    /// \param nCmdShow Indicates how the window will be shown.
    /// \return A Handle to the created window, or nullptr if the instance was already set or the window was already created, or there was an error creating the window.
    HWND InitializeWindowWin32(HINSTANCE hInstance, WNDPROC windowMessageProcessor, int nCmdShow)
    {
        HWND hWindow = nullptr;

        if (m_hInstance == nullptr)
        {
            m_hInstance = hInstance;

            if (m_hWindow == nullptr)
            {
                m_hWindow = CreateWindowWin32(windowMessageProcessor);

                if (m_hWindow != nullptr)
                {
                    if (FALSE == ShowWindow(m_hWindow, nCmdShow))
                    {
                        m_hWindow = nullptr;
                    }
                    else
                    {
                        hWindow = m_hWindow;
                    }
                }
            }
        }

        return hWindow;
    }

#elif defined(VK_USE_PLATFORM_XCB_KHR)

    /// Registers a new window class and creates a window from that class.
    /// \return Handle to the created window, or nullptr on error;
    xcb_connection_t* InitializeWindowXCB()
    {
        uint32_t windowFlags;
        uint32_t windowList[32];

        const xcb_setup_t* pXcbSetup = nullptr;
        xcb_screen_iterator_t screenIter;
        int screenIndex = 0;

        m_pXcbConnection = xcb_connect(NULL, &screenIndex);

        if (xcb_connection_has_error(m_pXcbConnection) > 0)
        {
            std::cout << "ERROR: Cannot find a compatible Vulkan installable client driver (ICD)." << std::endl;
            return nullptr;
        }

        pXcbSetup = xcb_get_setup(m_pXcbConnection);
        screenIter = xcb_setup_roots_iterator(pXcbSetup);

        while (screenIndex-- > 0)
        {
            xcb_screen_next(&screenIter);
        }

        m_pXcbScreen = screenIter.data;

        m_xcbWindow = xcb_generate_id(m_pXcbConnection);

        windowFlags = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
        windowList[0] = m_pXcbScreen->black_pixel;
        windowList[1] = XCB_EVENT_MASK_KEY_RELEASE |
                        XCB_EVENT_MASK_EXPOSURE |
                        XCB_EVENT_MASK_STRUCTURE_NOTIFY;

        xcb_create_window(m_pXcbConnection, XCB_COPY_FROM_PARENT,
                          m_xcbWindow,
                          m_pXcbScreen->root,
                          0, 0, m_cDefaultWindowWidth, m_cDefaultWindowHeight,
                          0, XCB_WINDOW_CLASS_INPUT_OUTPUT,
                          m_pXcbScreen->root_visual,
                          windowFlags, windowList);

        // Connect Window Management events to replies that can be compared against.
        xcb_intern_atom_cookie_t wmProtocolsCookie = xcb_intern_atom(m_pXcbConnection, 1, 12, "WM_PROTOCOLS");
        xcb_intern_atom_cookie_t wmDeleteWindowCookie = xcb_intern_atom(m_pXcbConnection, 0, 16, "WM_DELETE_WINDOW");

        xcb_intern_atom_reply_t* pProtocolsReply = xcb_intern_atom_reply(m_pXcbConnection, wmProtocolsCookie, 0);

        m_xcbAtomWmDeleteWindow = xcb_intern_atom_reply(m_pXcbConnection, wmDeleteWindowCookie, 0);

        xcb_change_property(m_pXcbConnection, XCB_PROP_MODE_REPLACE, m_xcbWindow,
                            pProtocolsReply->atom, 4, 32, 1,
                            &m_xcbAtomWmDeleteWindow->atom);
        free(pProtocolsReply);

        // Display the window
        xcb_map_window(m_pXcbConnection, m_xcbWindow);

        // Force the x/y coordinates to 100,100 results are identical in consecutive runs
        const uint32_t coords[] = {100, 100};
        xcb_configure_window(m_pXcbConnection, m_xcbWindow,
                             XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_Y, coords);

        return m_pXcbConnection;
    }
#endif // VK_USE_PLATFORM_XCB_KHR

    /// Loads a shader from the specified filename anre creates a vkShaderModule for it.
    /// \param filename The relative or absolute path to a filename of the SPIR-V shader to load.
    /// \return A valid VkShaderModule if the shader could be loaded, or VK_NULL_HANDLE on error.
    VkShaderModule LoadShader(const char* filename)
    {
        std::ifstream shaderFile(filename, std::ios::binary | std::ios::in);

        if (!shaderFile.is_open())
        {
            std::cout << "ERROR: Failed to read shader file: '" << filename << "'" << std::endl;
            return VK_NULL_HANDLE;
        }

        shaderFile.seekg(0, shaderFile.end);
        size_t length = static_cast<size_t>(shaderFile.tellg());
        shaderFile.seekg(0);

        std::vector<char> shaderBytes(length);

        shaderFile.read(shaderBytes.data(), length);
        shaderFile.close();

        VkShaderModuleCreateInfo shaderModuleCreateInfo = {};
        shaderModuleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        shaderModuleCreateInfo.pNext = nullptr;
        shaderModuleCreateInfo.codeSize = shaderBytes.size();
        shaderModuleCreateInfo.pCode = reinterpret_cast<const uint32_t*>(shaderBytes.data());

        VkShaderModule shaderModule;
        VkResult resultCreateShaderModule = vkCreateShaderModule(m_vkDevice, &shaderModuleCreateInfo, nullptr, &shaderModule);

        if (resultCreateShaderModule != VK_SUCCESS)
        {
            std::cout << "ERROR: Failed to create shader module for '" << filename << "'." << std::endl;
            return VK_NULL_HANDLE;
        }

        return shaderModule;
    }

    /// Load & Initialize GPUPerfAPI
    /// \return True if GPUPerfAPI could be loaded and initialized; false on error.
    bool InitializeGPA()
    {
        if (!GPUPerfAPI.Load())
        {
            std::cout << "ERROR: Failed to Load GPA library." << std::endl;
            return false;
        }

        if (GPUPerfAPI.IsLoaded())
        {
            GPA_Status statusRegisterCallback = GPUPerfAPI.m_pGpaFuncTable->GPA_RegisterLoggingCallback(GPA_LOGGING_ERROR_AND_MESSAGE, gpaLoggingCallback);

            if (statusRegisterCallback != GPA_STATUS_OK)
            {
                std::cout << "ERROR: Failed to register GPA logging callback." << std::endl;
                return false;
            }

            GPA_Status statusGPAInitialize = GPUPerfAPI.m_pGpaFuncTable->GPA_Initialize(GPA_INITIALIZE_DEFAULT_BIT);

            if (statusGPAInitialize != GPA_STATUS_OK)
            {
                std::cout << "ERROR: Failed to initialize GPA." << std::endl;
                return false;
            }

            return true;
        }

        return false;
    }


    /// General initialization that just about every Vulkan application would need to do.
    /// \return false if an error occurs, otherwise true.
    bool InitializeVulkan()
    {
        // At a high level, there is the concept of a Vulkan Instance (VkInstance) which is essentially
        // an instance of the Vulkan API. The instance can expose extensions and layers that are generic to
        // any Vulkan implementation (driver/hardware), such as validation layers / object trackers / CPU
        // profilers / debug reporting / etc; and also extensions and layers that are platform-specific
        // such as WIN32 Surfaces, XLIB Surfaces, etc.
        //
        // In order to render to a window on each platform, the corresponding instance extensions must be available.
        // The specific device also needs to support the swapchain extension.

        uint32_t instanceLayerCount = 0;
        VkResult resultInstanceLayerProperties = vkEnumerateInstanceLayerProperties(&instanceLayerCount, NULL);

        if (resultInstanceLayerProperties == VK_SUCCESS &&
            instanceLayerCount > 0)
        {
            std::vector<VkLayerProperties> instanceLayerProperties;
            instanceLayerProperties.resize(instanceLayerCount);
            resultInstanceLayerProperties = vkEnumerateInstanceLayerProperties(&instanceLayerCount, instanceLayerProperties.data());

            if (resultInstanceLayerProperties == VK_SUCCESS &&
                m_bPrintDebugOutput)
            {
                for (uint32_t i = 0; i < instanceLayerCount; ++i)
                {
                    std::cout << "Instance Layer " << i << ": " << instanceLayerProperties[i].layerName << std::endl;
                }
            }
        }

        uint32_t instanceExtensionCount = 0;
        const char* pLayerName = NULL;
        VkResult resultInstanceExtensionProperties = vkEnumerateInstanceExtensionProperties(pLayerName, &instanceExtensionCount, NULL);

        if (resultInstanceExtensionProperties != VK_SUCCESS ||
            instanceExtensionCount == 0)
        {
            std::cout << "WARNING: No instance extension properties are available." << std::endl;
        }
        else
        {
            std::vector<VkExtensionProperties> instanceExtensionProperties;
            instanceExtensionProperties.resize(instanceExtensionCount);
            resultInstanceExtensionProperties = vkEnumerateInstanceExtensionProperties(pLayerName, &instanceExtensionCount, instanceExtensionProperties.data());

            if (resultInstanceExtensionProperties != VK_SUCCESS)
            {
                std::cout << "ERROR: Failed to get instance extension properties." << std::endl;
            }
            else
            {
                // store and print extension names
                for (uint32_t i = 0; i < instanceExtensionCount; ++i)
                {
                    AddSupportedInstanceExtension(instanceExtensionProperties[i].extensionName);

                    if (m_bPrintDebugOutput)
                    {
                        std::cout << "Instance Extension " << i << ": " << instanceExtensionProperties[i].extensionName << std::endl;
                    }
                }

                // Report error if required extension not available
                bool bMissingRequiredExtensions = false;

                for (uint32_t r = 0; r < m_requiredInstanceExtensions.size(); ++r)
                {
                    if (!IsInstanceExtensionSupported(m_requiredInstanceExtensions[r]))
                    {
                        std::cout << "ERROR: Required Instance extension '" << m_requiredInstanceExtensions[r] << "' is not available." << std::endl;
                        bMissingRequiredExtensions = true;
                    }
                }

                if (bMissingRequiredExtensions)
                {
                    return false;
                }
            }
        }

        std::vector<const char*> layers;

        bool bEnableValidation = false;

        if (bEnableValidation)
        {
            layers.push_back("VK_LAYER_LUNARG_standard_validation");
        };

        VkApplicationInfo appInfo = {};

        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;

        appInfo.pNext = nullptr;

        appInfo.pApplicationName = m_cShortName.c_str();

        appInfo.applicationVersion = 1;

        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo instanceCreateInfo = {};

        instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;

        instanceCreateInfo.pNext = nullptr;

        instanceCreateInfo.pApplicationInfo = &appInfo;

        instanceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(m_requiredInstanceExtensions.size());

        instanceCreateInfo.ppEnabledExtensionNames = m_requiredInstanceExtensions.data();

        instanceCreateInfo.enabledLayerCount = static_cast<uint32_t>(layers.size());

        instanceCreateInfo.ppEnabledLayerNames = layers.data();

        // This demo doesn't do any special memory allocation handling,
        // so there's no need for AllocationCallbacks.
        VkAllocationCallbacks* pCallbacks = nullptr;

        VkResult createResult = vkCreateInstance(&instanceCreateInfo, pCallbacks, &m_vkInstance);

        if (VK_SUCCESS != createResult)
        {
            std::cout << "ERROR: Failed to create VkInstance (VkResult " << createResult << ")." << std::endl;
            return false;
        }

        // Register the debug report callback
        VkDebugReportCallbackCreateInfoEXT debugReportCallbackCreateInfo = {};
        debugReportCallbackCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
        debugReportCallbackCreateInfo.pNext = nullptr;
        debugReportCallbackCreateInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
        debugReportCallbackCreateInfo.pfnCallback = debugReportCallback;
        debugReportCallbackCreateInfo.pUserData = nullptr;

        PFN_vkCreateDebugReportCallbackEXT pvkCreateDebugReportCallback;
        VK_INSTANCE_GET_PROC_ADDR(pvkCreateDebugReportCallback, m_vkInstance, vkCreateDebugReportCallbackEXT);

        // There is also a concept of Vulkan Physical Devices (VkPhysicalDevice) which correspond to
        // physical hardware in the system. Physical devices may support different image formats, limits,
        // properties, memory types, and queue types (graphics, compute, transfer, or a combination).
        //
        // On those physical devices, multiple logical devices (VkDevice) can be created which different
        // extensions or layers enabled, along with with specific features and queue types.
        uint32_t physicalDeviceCount = 0;
        VkResult resultGetPhysDevices = vkEnumeratePhysicalDevices(m_vkInstance, &physicalDeviceCount, nullptr);

        if (resultGetPhysDevices != VK_SUCCESS ||
            physicalDeviceCount == 0)
        {
            std::cout << "ERROR: Failed to enumerate physical devices, and had " << physicalDeviceCount << " physical devices." << std::endl;
            return false;
        }
        else
        {
            std::vector<VkPhysicalDevice> physicalDevices;
            physicalDevices.resize(physicalDeviceCount);
            resultGetPhysDevices = vkEnumeratePhysicalDevices(m_vkInstance, &physicalDeviceCount, physicalDevices.data());

            if (resultGetPhysDevices != VK_SUCCESS)
            {
                std::cout << "ERROR: Failed to enumerate phyiscal devices." << std::endl;
                return false;
            }

            if (m_bPrintDebugOutput)
            {
                // Print out physical device names
                VkPhysicalDeviceProperties physicalDeviceProperties = {};

                for (uint32_t i = 0; i < physicalDeviceCount; ++i)
                {
                    vkGetPhysicalDeviceProperties(physicalDevices[i], &physicalDeviceProperties);
                    std::cout << "PhysicalDevice[" << i << "]: " << physicalDeviceProperties.deviceName << std::endl;
                }
            }

            // Select the default physical device and store related information.
            // Theoretically, an application might query this for each available physical device
            // and then use the information to select a physical device to use for rendering.
            m_vkPhysicalDevice = physicalDevices[m_cDefaultPhysicalDeviceIndex];
            vkGetPhysicalDeviceProperties(m_vkPhysicalDevice, &m_vkPhysicalDeviceProperties);
            vkGetPhysicalDeviceFeatures(m_vkPhysicalDevice, &m_vkPhysicalDeviceFeatures);
            vkGetPhysicalDeviceMemoryProperties(m_vkPhysicalDevice, &m_vkPhysicalDeviceMemoryProperties);
        }

#if defined(VK_USE_PLATFORM_WIN32_KHR)
        // Create a VkSurface for the Win32 window so that the demo can present to the display.
        VkWin32SurfaceCreateInfoKHR surfaceCreateInfo = {};
        surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
        surfaceCreateInfo.pNext = nullptr;
        surfaceCreateInfo.hinstance = m_hInstance;
        surfaceCreateInfo.hwnd = m_hWindow;
        VkResult resultCreateSurface = vkCreateWin32SurfaceKHR(m_vkInstance, &surfaceCreateInfo, nullptr, &m_vkSurface);

        if (resultCreateSurface != VK_SUCCESS ||
            m_vkSurface == VK_NULL_HANDLE)
        {
            std::cout << "ERROR: Failed to create Win32 surface." << std::endl;
            return false;
        }

#elif defined(VK_USE_PLATFORM_XCB_KHR)
        // Create a VkSurface for the xcb window so that the demo can present to the display.
        VkXcbSurfaceCreateInfoKHR surfaceCreateInfo = {};
        surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
        surfaceCreateInfo.pNext = nullptr;
        surfaceCreateInfo.flags = 0;
        surfaceCreateInfo.connection = m_pXcbConnection;
        surfaceCreateInfo.window = m_xcbWindow;
        VkResult resultCreateSurface = vkCreateXcbSurfaceKHR(m_vkInstance, &surfaceCreateInfo, nullptr, &m_vkSurface);

        if (resultCreateSurface != VK_SUCCESS ||
            m_vkSurface == VK_NULL_HANDLE)
        {
            std::cout << "ERROR: Failed to create XCB surface." << std::endl;
            return false;
        }

#else
        std::cout << "ERROR: The current platform is not supported - no VkSurface will be created!");
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
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(m_vkPhysicalDevice, &queueFamilyCount, nullptr);

        if (queueFamilyCount == 0)
        {
            std::cout << "ERROR: Selected physical device does not support any queue families." << std::endl;
            return false;
        }

        std::vector<VkQueueFamilyProperties> queueFamilyProperties;
        queueFamilyProperties.resize(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(m_vkPhysicalDevice, &queueFamilyCount, queueFamilyProperties.data());

        // Select first queue family that supports both graphics and present for the surface created above.
        bool bFoundSupportingQueue = false;

        for (uint32_t queueFamilyIndex = 0; queueFamilyIndex < queueFamilyCount; ++queueFamilyIndex)
        {
            // Check if supports graphics
            bool bSupportsGraphics = false;

            if ((queueFamilyProperties[queueFamilyIndex].queueFlags & VK_QUEUE_GRAPHICS_BIT) == VK_QUEUE_GRAPHICS_BIT)
            {
                if (m_bPrintDebugOutput)
                {
                    std::cout << "DEBUG: QueueFamilyIndex " << queueFamilyIndex << " supports Graphics." << std::endl;
                }

                bSupportsGraphics = true;
            }

            // Check if the device supports presenting to this surface
            VkBool32 bSupportsPresent = VK_FALSE;
            VkResult resultSurfaceSupport = vkGetPhysicalDeviceSurfaceSupportKHR(m_vkPhysicalDevice, queueFamilyIndex, m_vkSurface, &bSupportsPresent);

            if (resultSurfaceSupport == VK_SUCCESS &&
                bSupportsPresent == VK_TRUE &&
                m_bPrintDebugOutput)
            {
                std::cout << "DEBUG: QueueFamilyIndex " << queueFamilyIndex << " supports present." << std::endl;
            }

            if (bSupportsGraphics && bSupportsPresent)
            {
                // Both graphics and present is supported, so store this queueFamilyIndex;
                if (m_bPrintDebugOutput)
                {
                    std::cout << "DEBUG: Selecting QueueFamilyIndex " << queueFamilyIndex << "." << std::endl;
                }

                bFoundSupportingQueue = true;
                m_queueFamilyIndexGraphics = queueFamilyIndex;
                m_queueFamilyIndexPresent = queueFamilyIndex;
            }
        }

        if (!bFoundSupportingQueue)
        {
            std::cout << "ERROR: Unable to find a queue family that supports graphics and present." << std::endl;
            return false;
        }

        // Query available device extensions
        uint32_t availableDeviceExtensionCount = 0;
        VkResult resultGetDeviceExtensions = vkEnumerateDeviceExtensionProperties(m_vkPhysicalDevice, nullptr, &availableDeviceExtensionCount, nullptr);

        if (resultGetDeviceExtensions != VK_SUCCESS)
        {
            std::cout << "ERROR: Unable to get number of device extensions." << std::endl;
            return false;
        }

        // Make sure required device extensions are available.
        std::vector<VkExtensionProperties> availableDeviceExtensions;
        availableDeviceExtensions.resize(availableDeviceExtensionCount);
        resultGetDeviceExtensions = vkEnumerateDeviceExtensionProperties(m_vkPhysicalDevice, nullptr, &availableDeviceExtensionCount, availableDeviceExtensions.data());

        if (resultGetDeviceExtensions != VK_SUCCESS)
        {
            std::cout << "ERROR: Unable to get device extensions." << std::endl;
            return false;
        }
        else
        {
            // Store and print extension names
            for (uint32_t i = 0; i < availableDeviceExtensionCount; ++i)
            {
                AddSupportedDeviceExtension(availableDeviceExtensions[i].extensionName);

                if (m_bPrintDebugOutput)
                {
                    std::cout << "Device Extension " << i << ": " << availableDeviceExtensions[i].extensionName << "." << std::endl;
                }
            }

            // Report error if required extension not available
            bool bMissingRequiredExtensions = false;

            for (uint32_t r = 0; r < m_requiredDeviceExtensions.size(); ++r)
            {
                if (!IsDeviceExtensionSupported(m_requiredDeviceExtensions[r]))
                {
                    std::cout << "ERROR: Required Device extension '" << m_requiredDeviceExtensions[r] << "' is not available." << std::endl;
                    bMissingRequiredExtensions = true;
                }
            }

            if (bMissingRequiredExtensions)
            {
                return false;
            }
        }

        // CREATE A DEVICE
        VkDeviceQueueCreateInfo deviceQueueCreateInfo = {};
        deviceQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        deviceQueueCreateInfo.pNext = nullptr;
        deviceQueueCreateInfo.flags = 0;
        deviceQueueCreateInfo.queueFamilyIndex = m_queueFamilyIndexGraphics;
        deviceQueueCreateInfo.queueCount = 1;
        float queuePriority = 1.0f;
        deviceQueueCreateInfo.pQueuePriorities = &queuePriority;

        VkDeviceCreateInfo deviceCreateInfo = {};
        deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        deviceCreateInfo.pNext = nullptr;
        deviceCreateInfo.flags = 0;
        deviceCreateInfo.queueCreateInfoCount = 1;
        deviceCreateInfo.pQueueCreateInfos = &deviceQueueCreateInfo;
        deviceCreateInfo.enabledLayerCount = 0;
        deviceCreateInfo.ppEnabledLayerNames = nullptr;
        deviceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(m_requiredDeviceExtensions.size());
        deviceCreateInfo.ppEnabledExtensionNames = m_requiredDeviceExtensions.data();
        deviceCreateInfo.pEnabledFeatures = &m_vkPhysicalDeviceFeatures;

        VkResult resultCreateDevice = vkCreateDevice(m_vkPhysicalDevice, &deviceCreateInfo, nullptr, &m_vkDevice);

        if (resultCreateDevice != VK_SUCCESS)
        {
            std::cout << "ERROR: Failed to create device\n." << std::endl;
            return false;
        }

        // Now that a VkInstance, VkPhysicalDevice, and VkDevice have been selected, a GPUPerfAPI Context can be opened on the specified device
        // so that the available counters can be queried.
        if (GPUPerfAPI.IsLoaded())
        {
            GPA_vkContextOpenInfo gpaContextOpenInfo = {};
            gpaContextOpenInfo.instance = m_vkInstance;
            gpaContextOpenInfo.physicalDevice = m_vkPhysicalDevice;
            gpaContextOpenInfo.device = m_vkDevice;

            GPA_OpenContextFlags openFlags = GPA_OPENCONTEXT_DEFAULT_BIT;
            GPA_Status statusGPAOpenContext = GPUPerfAPI.m_pGpaFuncTable->GPA_OpenContext(&gpaContextOpenInfo, openFlags, &m_GPAContextId);

            if (statusGPAOpenContext != GPA_STATUS_OK)
            {
                std::cout << "ERROR: Failed to open GPA context." << std::endl;
                return false;
            }

            if (m_bPrintGPACounterInfo)
            {
                GPUPerfAPI.PrintGPACounterInfo(m_GPAContextId);
            }

            // Make sure discrete counters are supported
            GPA_ContextSampleTypeFlags sampleTypes = 0;
            GPA_Status statusGetSampleTypes = GPUPerfAPI.m_pGpaFuncTable->GPA_GetSupportedSampleTypes(m_GPAContextId, &sampleTypes);

            if (statusGetSampleTypes != GPA_STATUS_OK)
            {
                std::cout << "ERROR: Failed to get supported GPA sample types." << std::endl;
                return false;
            }

            GPA_Status statusGPACreateSession = GPUPerfAPI.m_pGpaFuncTable->GPA_CreateSession(m_GPAContextId, GPA_SESSION_SAMPLE_TYPE_DISCRETE_COUNTER, &m_GPASessionId);

            if (statusGPACreateSession != GPA_STATUS_OK)
            {
                std::cout << "ERROR: Failed to create GPA session." << std::endl;
                return false;
            }

            // Enable all the counters.
            GPA_Status statusGPAEnableAllCounters = GPUPerfAPI.m_pGpaFuncTable->GPA_EnableAllCounters(m_GPASessionId);

            if (statusGPAEnableAllCounters != GPA_STATUS_OK)
            {
                std::cout << "ERROR: Failed to enable all GPA counters." << std::endl;
                return false;
            }

            // Get the number of required passes based on the counters that were enabled above. Store it as a member
            // because it will be needed to control which CommandBuffers get GPA calls included.
            GPA_Status statusGPAGetPassCount = GPUPerfAPI.m_pGpaFuncTable->GPA_GetPassCount(m_GPASessionId, &m_requiredPassCount);

            if (statusGPAGetPassCount != GPA_STATUS_OK)
            {
                std::cout << "ERROR: Failed to get the number of required GPA passes." << std::endl;
                return false;
            }

            std::cout << "GPA requires " << m_requiredPassCount << " pass(es)." << std::endl;

            // Begin the GPA session to lock in the set of selected counters and allow command buffers to start
            // being built with GPA commands included.
            GPA_Status statusGPABeginSession = GPUPerfAPI.m_pGpaFuncTable->GPA_BeginSession(m_GPASessionId);

            if (statusGPABeginSession != GPA_STATUS_OK)
            {
                std::cout << "ERROR: Failed to begin GPA session." << std::endl;
                return false;
            }
        }

        // Get a queue from the graphics queue family
        vkGetDeviceQueue(m_vkDevice, m_queueFamilyIndexGraphics, m_queueIndex, &m_vkQueue);

        // Now the surface format needs to be selected from those available. The preference is for
        // B8G8R8A8_UNORM, but a different format will be okay.
        uint32_t formatCount = 0;
        VkResult resultGetSurfaceFormats = vkGetPhysicalDeviceSurfaceFormatsKHR(m_vkPhysicalDevice, m_vkSurface, &formatCount, nullptr);

        if (resultGetSurfaceFormats != VK_SUCCESS ||
            formatCount == 0)
        {
            std::cout << "ERROR: The selected physical device does not support any surface formats." << std::endl;
            return false;
        }

        std::vector<VkSurfaceFormatKHR> surfaceFormats;
        surfaceFormats.resize(formatCount);
        resultGetSurfaceFormats = vkGetPhysicalDeviceSurfaceFormatsKHR(m_vkPhysicalDevice, m_vkSurface, &formatCount, surfaceFormats.data());

        if (resultGetSurfaceFormats != VK_SUCCESS)
        {
            std::cout << "ERROR: Failed to get surface formats." << std::endl;
            return false;
        }

        bool bFoundDesiredFormat = false;

        for (uint32_t i = 0; i < formatCount; ++i)
        {
            if (surfaceFormats[i].format == VK_FORMAT_B8G8R8A8_UNORM)
            {
                m_vkSurfaceFormat = surfaceFormats[i];
                bFoundDesiredFormat = true;
                break;
            }
        }

        if (!bFoundDesiredFormat)
        {
            // Didn't find the desired format, but still be able to select it, or maybe have to fallback to whatever is available.
            if (surfaceFormats[0].format == VK_FORMAT_UNDEFINED)
            {
                // Get to select the format!
                m_vkSurfaceFormat.format = VK_FORMAT_B8G8R8A8_UNORM;
                m_vkSurfaceFormat.colorSpace = surfaceFormats[0].colorSpace;
            }
            else
            {
                // Fallback to whatever is available.
                m_vkSurfaceFormat = surfaceFormats[0];
            }
        }

        // Get presentation modes
        uint32_t presentModeCount = 0;
        VkResult resultGetPresentModes = vkGetPhysicalDeviceSurfacePresentModesKHR(m_vkPhysicalDevice, m_vkSurface, &presentModeCount, nullptr);

        if (resultGetPresentModes != VK_SUCCESS)
        {
            std::cout << "ERROR: Failed to get number of supported present modes." << std::endl;
            return false;
        }

        std::vector<VkPresentModeKHR> presentModes;
        presentModes.resize(presentModeCount);
        resultGetPresentModes = vkGetPhysicalDeviceSurfacePresentModesKHR(m_vkPhysicalDevice, m_vkSurface, &presentModeCount, presentModes.data());

        if (resultGetPresentModes != VK_SUCCESS)
        {
            std::cout << "ERROR: Failed to get supported present modes." << std::endl;
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
        // In order to avoid tearing artifacts and allow for the fastest possible rendering, mailbox mode will be prefered over FIFO.
        m_vkPresentMode = VK_PRESENT_MODE_FIFO_KHR;

        // Select mailbox mode if it is available
        for (std::vector<VkPresentModeKHR>::const_iterator modeIter = presentModes.cbegin(); modeIter != presentModes.cend(); ++modeIter)
        {
            if (*modeIter == VK_PRESENT_MODE_MAILBOX_KHR)
            {
                m_vkPresentMode = *modeIter;
                break;
            }
        }

        // Get surface capabilities to determine the acceptable sizes of the swpachain images that will be presented to the surface.
        VkResult resultSurfaceCapabilities = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(m_vkPhysicalDevice, m_vkSurface, &m_vkSurfaceCapabilities);

        if (resultSurfaceCapabilities != VK_SUCCESS)
        {
            std::cout << "ERROR: Failed to get surface capabilities." << std::endl;
            return false;
        }

        // The extents of the swapchain images should match the resolution of the window being drawn into.
        // It doesn't actually HAVE to match, but for the purposes of this demo they should.
        // make sure 'currentExtent' matches window and is within acceptable range.
        if (m_vkSurfaceCapabilities.currentExtent.width == UINT32_MAX &&
            m_vkSurfaceCapabilities.currentExtent.height == UINT32_MAX)
        {
            // This means the display engine supports some flexbility in the size of the image surface compared
            // to the size of the window that is being presented to.
            m_swapchainImageExtent.width = std::max(m_vkSurfaceCapabilities.minImageExtent.width, std::min(m_vkSurfaceCapabilities.maxImageExtent.width, m_cDefaultWindowWidth));
            m_swapchainImageExtent.height = std::max(m_vkSurfaceCapabilities.minImageExtent.height, std::min(m_vkSurfaceCapabilities.maxImageExtent.height, m_cDefaultWindowHeight));
        }
        else
        {
            m_swapchainImageExtent = m_vkSurfaceCapabilities.currentExtent;
        }

        // If allowed, add one more swapchain image than the implementation needs to better avoid latency.
        // This will allow the application to always have one image to work one while others may be queued for display.
        uint32_t swapchainImageCount = m_vkSurfaceCapabilities.minImageCount + 1;

        if (m_vkSurfaceCapabilities.minImageCount > 0 &&
            swapchainImageCount > m_vkSurfaceCapabilities.maxImageCount)
        {
            swapchainImageCount = m_vkSurfaceCapabilities.maxImageCount;
        }

        // Finally have all the information necessary to create a swapchain!
        VkSwapchainCreateInfoKHR swapchainCreateInfo = {};
        swapchainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        swapchainCreateInfo.pNext = nullptr;
        swapchainCreateInfo.flags = 0;
        swapchainCreateInfo.surface = m_vkSurface;
        swapchainCreateInfo.minImageCount = swapchainImageCount;
        swapchainCreateInfo.imageFormat = m_vkSurfaceFormat.format;
        swapchainCreateInfo.imageColorSpace = m_vkSurfaceFormat.colorSpace;
        swapchainCreateInfo.imageExtent = m_swapchainImageExtent;
        swapchainCreateInfo.imageArrayLayers = 1;
        swapchainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

        // This demo currently only supports a single queue family that supports both graphics & present,
        // so EXCLUSIVE mode can be used here.
        swapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        swapchainCreateInfo.queueFamilyIndexCount = 1;
        swapchainCreateInfo.pQueueFamilyIndices = &m_queueFamilyIndexGraphics;

        // Can be used to rotate an image
        swapchainCreateInfo.preTransform = m_vkSurfaceCapabilities.currentTransform;

        // Can be used to blend the window into other surfaces
        swapchainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;

        swapchainCreateInfo.presentMode = m_vkPresentMode;
        swapchainCreateInfo.clipped = VK_TRUE;
        swapchainCreateInfo.oldSwapchain = VK_NULL_HANDLE;

        VkResult resultCreateSwapchain = vkCreateSwapchainKHR(m_vkDevice, &swapchainCreateInfo, nullptr, &m_vkSwapchain);

        if (resultCreateSwapchain != VK_SUCCESS)
        {
            std::cout << "ERROR: Failed to create swapchain." << std::endl;
            return false;
        }

        // The Vulkan implementation may have created more more swapchain images, so query the number again, and actually get handles
        // to those image objects.
        VkResult resultGetSwapchainImages = vkGetSwapchainImagesKHR(m_vkDevice, m_vkSwapchain, &swapchainImageCount, nullptr);

        if (resultGetSwapchainImages != VK_SUCCESS)
        {
            std::cout << "ERROR: Failed to get final swapchain image count." << std::endl;
            return false;
        }

        m_perSwapchainImageResources.swapchainImages.resize(swapchainImageCount);
        resultGetSwapchainImages = vkGetSwapchainImagesKHR(m_vkDevice, m_vkSwapchain, &swapchainImageCount, m_perSwapchainImageResources.swapchainImages.data());

        if (resultGetSwapchainImages != VK_SUCCESS)
        {
            std::cout << "ERROR: Failed to get swapchain images." << std::endl;
            return false;
        }

        m_perSwapchainImageResources.swapchainImageViews.resize(swapchainImageCount);
        m_perSwapchainImageResources.vkFramebuffers.resize(swapchainImageCount);
        m_prebuiltPerFrameResources.resize(swapchainImageCount);

        if (GPUPerfAPI.IsLoaded())
        {
            // If using GPUPerfAPI and pre-creating command buffers, extra command buffers will need to be created in order to
            // support the additional passes needed by GPA. This is because the commands related to profiling are embedded in the
            // Vulkan command buffer.
            m_prebuiltPerFrameResourcesWithGPA.resize(m_requiredPassCount);
        }

        // Create an ImageView for each swapchain image so that they can be bound as rendertargets.
        for (uint32_t i = 0; i < m_perSwapchainImageResources.swapchainImages.size(); ++i)
        {
            VkImageViewCreateInfo imageViewCreateInfo = {};
            imageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
            imageViewCreateInfo.pNext = nullptr;
            imageViewCreateInfo.flags = 0;
            imageViewCreateInfo.image = m_perSwapchainImageResources.swapchainImages[i];
            imageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
            imageViewCreateInfo.format = m_vkSurfaceFormat.format;
            imageViewCreateInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
            imageViewCreateInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
            imageViewCreateInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
            imageViewCreateInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
            imageViewCreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            imageViewCreateInfo.subresourceRange.baseMipLevel = 0;
            imageViewCreateInfo.subresourceRange.levelCount = 1;
            imageViewCreateInfo.subresourceRange.baseArrayLayer = 0;
            imageViewCreateInfo.subresourceRange.layerCount = 1;

            VkResult resultCreateImageView = vkCreateImageView(m_vkDevice, &imageViewCreateInfo, nullptr, &m_perSwapchainImageResources.swapchainImageViews[i]);

            if (resultCreateImageView != VK_SUCCESS)
            {
                std::cout << "ERROR: Failed to create a swapchain image view." << std::endl;
                return false;
            }
        }

        // This is the start of object creation that is more specific to this demo.

        // This demo will only render into a single color attachment, and the memory can be cleared
        // when the attachment is loaded because the frame will render into the entire image and
        // there is no blending / frame blur taking place.
        // The attachment has no stencil information, so DONT_CARE about those settings.
        VkAttachmentDescription colorAttachmentDescriptionInitial = {};
        colorAttachmentDescriptionInitial.flags = 0;
        colorAttachmentDescriptionInitial.format = m_vkSurfaceFormat.format;
        colorAttachmentDescriptionInitial.samples = VK_SAMPLE_COUNT_1_BIT;
        colorAttachmentDescriptionInitial.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        colorAttachmentDescriptionInitial.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        colorAttachmentDescriptionInitial.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        colorAttachmentDescriptionInitial.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        colorAttachmentDescriptionInitial.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        colorAttachmentDescriptionInitial.finalLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

        // Each render pass is made of 1 or more subpasses that can have different attachments.
        // The AttachmentReference simply indicates which attachment index it is located at
        // and what layout the attachment is in. In this case, it is a color attachment.
        VkAttachmentReference colorAttachmentReference = {};
        colorAttachmentReference.attachment = 0;
        colorAttachmentReference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

        // The description of this subpass is that it will:
        // execute a graphics pipeline,
        // has no input attachments (vertices are specified in VS rather than with IB/VB),
        // only has 1 color attachment,
        // no multisample attachments that would need to be resolved,
        // no depth stencil attachment,
        // no attachments that need to be passed-through to another subpass.
        VkSubpassDescription subpassDescription = {};
        subpassDescription.flags = 0;
        subpassDescription.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
        subpassDescription.inputAttachmentCount = 0;
        subpassDescription.pInputAttachments = nullptr;
        subpassDescription.colorAttachmentCount = 1;
        subpassDescription.pColorAttachments = &colorAttachmentReference;
        subpassDescription.pResolveAttachments = nullptr;
        subpassDescription.pDepthStencilAttachment = nullptr;
        subpassDescription.preserveAttachmentCount = 0;
        subpassDescription.pPreserveAttachments = nullptr;

        // Define the array of attachments that are used by the render pass.
        // As described above, it only has a color attachment.
        std::vector<VkAttachmentDescription> attachments =
        {
            colorAttachmentDescriptionInitial
        };

        // Create the render pass.
        // It uses the set of attachments above, and the single subpass.
        VkRenderPassCreateInfo renderPassCreateInfoInitial = {};
        renderPassCreateInfoInitial.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
        renderPassCreateInfoInitial.pNext = nullptr;
        renderPassCreateInfoInitial.flags = 0;
        renderPassCreateInfoInitial.attachmentCount = static_cast<uint32_t>(attachments.size());
        renderPassCreateInfoInitial.pAttachments = attachments.data();
        renderPassCreateInfoInitial.subpassCount = 1;
        renderPassCreateInfoInitial.pSubpasses = &subpassDescription;
        renderPassCreateInfoInitial.dependencyCount = 0;
        renderPassCreateInfoInitial.pDependencies = nullptr;

        VkResult resultCreateRenderPass = vkCreateRenderPass(m_vkDevice, &renderPassCreateInfoInitial, nullptr, &m_vkRenderPassInitial);

        if (resultCreateRenderPass != VK_SUCCESS)
        {
            std::cout << "ERROR: Failed to create renderpass." << std::endl;
            return false;
        }

        // For mid-frame draws, use the same settings as above, except:
        // 1) Don't clear the RT on loading.
        // 2) The layout will start and end as a COLOR_ATTACHMENT_OPTIMAL.
        VkAttachmentDescription colorAttachmentDescriptionMid = colorAttachmentDescriptionInitial;
        colorAttachmentDescriptionMid.loadOp = VK_ATTACHMENT_LOAD_OP_LOAD;
        colorAttachmentDescriptionMid.initialLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
        colorAttachmentDescriptionMid.finalLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

        // Define the array of attachments that are used by the render pass.
        // As described above, it only has a color attachment.
        std::vector<VkAttachmentDescription> attachmentsMid =
        {
            colorAttachmentDescriptionMid
        };

        // Create the render pass for the middle draw calls which leave the rendertarget as a color attachment.
        VkRenderPassCreateInfo renderPassCreateInfoMid = {};
        renderPassCreateInfoMid.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
        renderPassCreateInfoMid.pNext = nullptr;
        renderPassCreateInfoMid.flags = 0;
        renderPassCreateInfoMid.attachmentCount = static_cast<uint32_t>(attachmentsMid.size());
        renderPassCreateInfoMid.pAttachments = attachmentsMid.data();
        renderPassCreateInfoMid.subpassCount = 1;
        renderPassCreateInfoMid.pSubpasses = &subpassDescription;
        renderPassCreateInfoMid.dependencyCount = 0;
        renderPassCreateInfoMid.pDependencies = nullptr;

        VkResult resultCreateRenderPassMid = vkCreateRenderPass(m_vkDevice, &renderPassCreateInfoMid, nullptr, &m_vkRenderPassMid);

        if (resultCreateRenderPassMid != VK_SUCCESS)
        {
            std::cout << "ERROR: Failed to create renderpass mid." << std::endl;
            return false;
        }

        // Now create a renderpass for the final draw which will put the rendertarget into a presentable layout.
        // It is the same as above, except:
        // 1) The final layout is PRESENT_SRC.
        VkAttachmentDescription colorAttachmentDescriptionFinal = colorAttachmentDescriptionMid;
        colorAttachmentDescriptionFinal.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

        // Define the array of attachments that are used by the render pass.
        // As described above, it only has a color attachment.
        std::vector<VkAttachmentDescription> attachmentsFinal =
        {
            colorAttachmentDescriptionFinal
        };

        // Create the render pass for drawing in wireframe
        VkRenderPassCreateInfo renderPassCreateInfoFinal = renderPassCreateInfoMid;
        renderPassCreateInfoFinal.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
        renderPassCreateInfoFinal.pNext = nullptr;
        renderPassCreateInfoFinal.flags = 0;
        renderPassCreateInfoFinal.attachmentCount = static_cast<uint32_t>(attachmentsFinal.size());
        renderPassCreateInfoFinal.pAttachments = attachmentsFinal.data();
        renderPassCreateInfoFinal.subpassCount = 1;
        renderPassCreateInfoFinal.pSubpasses = &subpassDescription;
        renderPassCreateInfoFinal.dependencyCount = 0;
        renderPassCreateInfoFinal.pDependencies = nullptr;

        VkResult resultCreateRenderPassFinal = vkCreateRenderPass(m_vkDevice, &renderPassCreateInfoFinal, nullptr, &m_vkRenderPassFinal);

        if (resultCreateRenderPassFinal != VK_SUCCESS)
        {
            std::cout << "ERROR: Failed to create renderpass final." << std::endl;
            return false;
        }

        // Create each of the framebuffers (one for each swapchain image).
        for (uint32_t i = 0; i < m_perSwapchainImageResources.swapchainImageViews.size(); i++)
        {
            VkFramebufferCreateInfo framebufferCreateInfo = {};
            framebufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
            framebufferCreateInfo.pNext = nullptr;
            framebufferCreateInfo.flags = 0;
            framebufferCreateInfo.renderPass = m_vkRenderPassFinal; //< It doesn't matter too much which renderpass is used here, because they are all "compatible" (see spec).
            framebufferCreateInfo.attachmentCount = 1;
            framebufferCreateInfo.pAttachments = &m_perSwapchainImageResources.swapchainImageViews[i];
            framebufferCreateInfo.width = m_swapchainImageExtent.width;
            framebufferCreateInfo.height = m_swapchainImageExtent.height;
            framebufferCreateInfo.layers = 1;

            VkResult resultCreateFramebuffer = vkCreateFramebuffer(m_vkDevice, &framebufferCreateInfo, nullptr, &m_perSwapchainImageResources.vkFramebuffers[i]);

            if (resultCreateFramebuffer != VK_SUCCESS)
            {
                std::cout << "ERROR: Failed to create framebuffer." << std::endl;
                return false;
            }
        }

        // Create Graphics Pipeline.
        VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo = {};
        pipelineLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutCreateInfo.pNext = nullptr;
        pipelineLayoutCreateInfo.flags = 0;
        pipelineLayoutCreateInfo.setLayoutCount = 0;
        pipelineLayoutCreateInfo.pSetLayouts = nullptr;
        pipelineLayoutCreateInfo.pushConstantRangeCount = 0;
        pipelineLayoutCreateInfo.pPushConstantRanges = nullptr;

        VkResult resultCreatePipelineLayout = vkCreatePipelineLayout(m_vkDevice, &pipelineLayoutCreateInfo, nullptr, &m_vkPipelineLayout);

        if (resultCreatePipelineLayout != VK_SUCCESS)
        {
            std::cout << "ERROR: Failed to create pipeline layout." << std::endl;
            return false;
        }

        char modulepath[4096];

#ifdef _WIN32
        GetModuleFileName(NULL, modulepath, sizeof(modulepath));
#else
        int len;
        len = readlink("/proc/self/exe", modulepath, 4096);
#endif

        std::string moduleString(modulepath);
        size_t lastSlashPosition = moduleString.find_last_of('\\');

        std::string m_executablePath = std::string(moduleString.begin(), moduleString.begin() + (lastSlashPosition + 1));
        std::string vertexShaderFile = m_executablePath;
        vertexShaderFile.append("vkcolorcubeshader.vert.spv");
        m_vertexShaderModule = LoadShader(vertexShaderFile.c_str());

        std::string fragmentShaderFile = m_executablePath;
        fragmentShaderFile.append("vkcolorcubeshader.frag.spv");
        m_fragmentShaderModule = LoadShader(fragmentShaderFile.c_str());

        std::string wireFrameShader = m_executablePath;
        wireFrameShader.append("vkcolorcubewireframeshader.frag.spv");
        m_fragmentShaderWireframeModule = LoadShader(wireFrameShader.c_str());

        if (m_vertexShaderModule == VK_NULL_HANDLE ||
            m_fragmentShaderModule == VK_NULL_HANDLE ||
            m_fragmentShaderWireframeModule == VK_NULL_HANDLE)
        {
            return false;
        }

        VkPipelineShaderStageCreateInfo vertexShaderStateCreateInfo = {};
        vertexShaderStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        vertexShaderStateCreateInfo.pNext = nullptr;
        vertexShaderStateCreateInfo.flags = 0;
        vertexShaderStateCreateInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
        vertexShaderStateCreateInfo.module = m_vertexShaderModule;
        vertexShaderStateCreateInfo.pName = "main";
        vertexShaderStateCreateInfo.pSpecializationInfo = nullptr;

        VkPipelineShaderStageCreateInfo fragmentShaderStateCreateInfo = {};
        fragmentShaderStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        fragmentShaderStateCreateInfo.pNext = nullptr;
        fragmentShaderStateCreateInfo.flags = 0;
        fragmentShaderStateCreateInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
        fragmentShaderStateCreateInfo.module = m_fragmentShaderModule;
        fragmentShaderStateCreateInfo.pName = "main";
        fragmentShaderStateCreateInfo.pSpecializationInfo = nullptr;

        VkPipelineShaderStageCreateInfo pipelineShaderStages[] =
        {
            vertexShaderStateCreateInfo,
            fragmentShaderStateCreateInfo
        };

        VkPipelineVertexInputStateCreateInfo pipelineVertexInputStateCreateInfo = {};
        pipelineVertexInputStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
        pipelineVertexInputStateCreateInfo.pNext = nullptr;
        pipelineVertexInputStateCreateInfo.flags = 0;
        pipelineVertexInputStateCreateInfo.vertexAttributeDescriptionCount = 0;
        pipelineVertexInputStateCreateInfo.pVertexBindingDescriptions = nullptr;
        pipelineVertexInputStateCreateInfo.vertexAttributeDescriptionCount = 0;
        pipelineVertexInputStateCreateInfo.pVertexAttributeDescriptions = nullptr;

        VkPipelineInputAssemblyStateCreateInfo pipelineInputAssemblyStateCreateInfo = {};
        pipelineInputAssemblyStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
        pipelineInputAssemblyStateCreateInfo.pNext = nullptr;
        pipelineInputAssemblyStateCreateInfo.flags = 0;
        pipelineInputAssemblyStateCreateInfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
        pipelineInputAssemblyStateCreateInfo.primitiveRestartEnable = VK_FALSE;

        // scratch that, lets just make the viewports dynamic (Doh! Seems like there is a bug in the validation layers)
        // Create three viewports to divide the window into thirds.
        VkViewport viewports[3];

        for (uint32_t i = 0; i < 3; ++i)
        {
            viewports[i].x = static_cast<float>(i * m_swapchainImageExtent.width / 3);
            viewports[i].y = 0.0f;
            viewports[i].width = static_cast<float>(m_swapchainImageExtent.width / 3);
            viewports[i].height = static_cast<float>(m_swapchainImageExtent.height);
            viewports[i].minDepth = 0.0f;
            viewports[i].maxDepth = 1.0f;
        }

        std::vector<VkDynamicState> dynamicStates = { VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR };

        VkPipelineDynamicStateCreateInfo dynamicStateCreateInfo = {};
        dynamicStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
        dynamicStateCreateInfo.pNext = nullptr;
        dynamicStateCreateInfo.flags = 0;
        dynamicStateCreateInfo.dynamicStateCount = static_cast<uint32_t>(dynamicStates.size());
        dynamicStateCreateInfo.pDynamicStates = dynamicStates.data();

        VkRect2D scissorRect = {};
        scissorRect.offset = VkOffset2D({ 0, 0 });
        scissorRect.extent = m_swapchainImageExtent;

        // Set a default viewport here, but since the viewport and scissor are set as dynamic states,
        // they can (and will be) modified within the command buffer.
        VkPipelineViewportStateCreateInfo viewportStateCreateInfo = {};
        viewportStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        viewportStateCreateInfo.pNext = nullptr;
        viewportStateCreateInfo.flags = 0;
        viewportStateCreateInfo.viewportCount = 1;
        viewportStateCreateInfo.pViewports = &viewports[0];
        viewportStateCreateInfo.scissorCount = 1;
        viewportStateCreateInfo.pScissors = &scissorRect;

        VkPipelineRasterizationStateCreateInfo rasterizationStateCreateInfo = {};
        rasterizationStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
        rasterizationStateCreateInfo.pNext = nullptr;
        rasterizationStateCreateInfo.flags = 0;
        rasterizationStateCreateInfo.depthClampEnable = VK_FALSE;
        rasterizationStateCreateInfo.rasterizerDiscardEnable = VK_FALSE;
        rasterizationStateCreateInfo.polygonMode = VK_POLYGON_MODE_FILL;
        rasterizationStateCreateInfo.cullMode = VK_CULL_MODE_BACK_BIT;
        rasterizationStateCreateInfo.frontFace = VK_FRONT_FACE_CLOCKWISE;
        rasterizationStateCreateInfo.depthBiasEnable = VK_FALSE;
        rasterizationStateCreateInfo.depthBiasConstantFactor = 0;
        rasterizationStateCreateInfo.depthBiasClamp = 0;
        rasterizationStateCreateInfo.depthBiasSlopeFactor = 0;
        rasterizationStateCreateInfo.lineWidth = 1;

        VkPipelineMultisampleStateCreateInfo pipelineMultisampleStateCreateInfo = {};
        pipelineMultisampleStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
        pipelineMultisampleStateCreateInfo.sampleShadingEnable = VK_FALSE;
        pipelineMultisampleStateCreateInfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
        pipelineMultisampleStateCreateInfo.minSampleShading = 1.0f;
        pipelineMultisampleStateCreateInfo.pSampleMask = nullptr;
        pipelineMultisampleStateCreateInfo.alphaToCoverageEnable = VK_FALSE;
        pipelineMultisampleStateCreateInfo.alphaToOneEnable = VK_FALSE;

        VkPipelineColorBlendAttachmentState pipelineColorBlendAttachmentState = {};
        pipelineColorBlendAttachmentState.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
        pipelineColorBlendAttachmentState.blendEnable = VK_FALSE;
        pipelineColorBlendAttachmentState.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
        pipelineColorBlendAttachmentState.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
        pipelineColorBlendAttachmentState.colorBlendOp = VK_BLEND_OP_ADD;
        pipelineColorBlendAttachmentState.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
        pipelineColorBlendAttachmentState.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
        pipelineColorBlendAttachmentState.alphaBlendOp = VK_BLEND_OP_ADD;

        VkPipelineColorBlendStateCreateInfo pipelineColorBlendStateCreateInfo = {};
        pipelineColorBlendStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
        pipelineColorBlendStateCreateInfo.logicOpEnable = VK_FALSE;
        pipelineColorBlendStateCreateInfo.logicOp = VK_LOGIC_OP_COPY;
        pipelineColorBlendStateCreateInfo.attachmentCount = 1;
        pipelineColorBlendStateCreateInfo.pAttachments = &pipelineColorBlendAttachmentState;
        pipelineColorBlendStateCreateInfo.blendConstants[0] = 0.0f;
        pipelineColorBlendStateCreateInfo.blendConstants[1] = 0.0f;
        pipelineColorBlendStateCreateInfo.blendConstants[2] = 0.0f;
        pipelineColorBlendStateCreateInfo.blendConstants[3] = 0.0f;

        VkPipelineTessellationStateCreateInfo ts = {};
        ts.sType = VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO;

        VkPipelineDepthStencilStateCreateInfo ds = {};
        ds.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;

        VkGraphicsPipelineCreateInfo graphicsPipelineCreateInfo = {};
        graphicsPipelineCreateInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        graphicsPipelineCreateInfo.flags = 0;
        graphicsPipelineCreateInfo.stageCount = 2;
        graphicsPipelineCreateInfo.pStages = pipelineShaderStages;
        graphicsPipelineCreateInfo.pVertexInputState = &pipelineVertexInputStateCreateInfo;
        graphicsPipelineCreateInfo.pInputAssemblyState = &pipelineInputAssemblyStateCreateInfo;
        graphicsPipelineCreateInfo.pTessellationState = &ts;
        graphicsPipelineCreateInfo.pViewportState = &viewportStateCreateInfo;
        graphicsPipelineCreateInfo.pRasterizationState = &rasterizationStateCreateInfo;
        graphicsPipelineCreateInfo.pMultisampleState = &pipelineMultisampleStateCreateInfo;
        graphicsPipelineCreateInfo.pDepthStencilState = &ds;
        graphicsPipelineCreateInfo.pColorBlendState = &pipelineColorBlendStateCreateInfo;
        graphicsPipelineCreateInfo.pDynamicState = &dynamicStateCreateInfo;
        graphicsPipelineCreateInfo.layout = m_vkPipelineLayout;
        graphicsPipelineCreateInfo.renderPass = m_vkRenderPassInitial;
        graphicsPipelineCreateInfo.subpass = 0;
        graphicsPipelineCreateInfo.basePipelineHandle = VK_NULL_HANDLE;
        graphicsPipelineCreateInfo.basePipelineIndex = -1;

        VkResult resultCreateGraphicsPipelines = vkCreateGraphicsPipelines(m_vkDevice, VK_NULL_HANDLE, 1, &graphicsPipelineCreateInfo, nullptr, &m_vkPipeline);

        if (resultCreateGraphicsPipelines != VK_SUCCESS)
        {
            std::cout << "ERROR: Failed to create graphics pipelines." << std::endl;
            return false;
        }

        // Modify existing state objects as needed to configure a GraphicsPipeline that will draw a wireframe around the cube
        fragmentShaderStateCreateInfo.module = m_fragmentShaderWireframeModule;

        VkPipelineShaderStageCreateInfo pipelineShaderStagesWireframe[] =
        {
            vertexShaderStateCreateInfo,
            fragmentShaderStateCreateInfo
        };

        // Modify the existing rasterization state to draw lines and to disable culling.
        // Make sure lineWidth is set to 1. In order to draw wider lines, the "wideLines"
        // feature would need to be supported and enabled on the device.
        rasterizationStateCreateInfo.polygonMode = VK_POLYGON_MODE_LINE;
        rasterizationStateCreateInfo.cullMode = VK_CULL_MODE_NONE;
        rasterizationStateCreateInfo.lineWidth = 1;

        VkGraphicsPipelineCreateInfo graphicsPipelineCreateInfoWireframe = graphicsPipelineCreateInfo;
        graphicsPipelineCreateInfoWireframe.stageCount = 2;
        graphicsPipelineCreateInfoWireframe.pStages = pipelineShaderStagesWireframe;
        graphicsPipelineCreateInfoWireframe.pRasterizationState = &rasterizationStateCreateInfo;
        graphicsPipelineCreateInfoWireframe.pColorBlendState = &pipelineColorBlendStateCreateInfo;

        VkResult resultCreateGraphicsPipelineWireframe = vkCreateGraphicsPipelines(m_vkDevice, VK_NULL_HANDLE, 1, &graphicsPipelineCreateInfoWireframe, nullptr, &m_vkPipelineWireframe);

        if (resultCreateGraphicsPipelineWireframe != VK_SUCCESS)
        {
            std::cout << "ERROR: Failed to create wireframe graphics pipelines." << std::endl;
            return false;
        }

        // Every Vulkan app will need at least one CommandPool in order to allocate CommandBuffers.
        // If an application is using multiple threads to distribute CommandBuffer building, then
        // one CommandPool should be created for each thread. And if the application is doing
        // both graphics and compute work, then it will need to create two different CommandPools,
        // one for each queueFamilyIndex.
        // To get even more efficient an application may want to create one CommandPool for each
        // swapchainImage (because that will limit the number of frames that can be processed or
        // queued) for each thread. This would allow for any thread to process its portion of any
        // upcoming frame based on when that frame's resources become available. There are certain
        // situations when this would become more useful, such as when CommandBuffers are being reset
        // and rebuilt each frame.
        // In this demo, there is only one thread doing graphics work and the CommandBuffers can all
        // be built ahead of time, so only one CommandPool is needed.
        VkCommandPoolCreateInfo cmdPoolCreateInfo = {};
        cmdPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        cmdPoolCreateInfo.pNext = nullptr;
        cmdPoolCreateInfo.flags = 0;
        cmdPoolCreateInfo.queueFamilyIndex = m_queueFamilyIndexGraphics;

        VkResult resultCreateCommandPool = vkCreateCommandPool(m_vkDevice, &cmdPoolCreateInfo, nullptr, &m_vkCommandPool);

        if (resultCreateCommandPool != VK_NULL_HANDLE)
        {
            std::cout << "ERROR: Failed to create command pool." << std::endl;
            return false;
        }

        // Create semaphores that are necessary to synchronize rendering and presenting.
        VkSemaphoreCreateInfo semaphoreCreateInfo = {};
        semaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
        semaphoreCreateInfo.pNext = nullptr;
        semaphoreCreateInfo.flags = 0;

        VkResult resultCreateSemaphore = vkCreateSemaphore(m_vkDevice, &semaphoreCreateInfo, nullptr, &m_vkSemaphoreAcquiredSwapchainImage);

        if (resultCreateSemaphore != VK_SUCCESS)
        {
            std::cout << "ERROR: Failed to create semaphore to acquire swapchain images." << std::endl;
            return false;
        }

        resultCreateSemaphore = vkCreateSemaphore(m_vkDevice, &semaphoreCreateInfo, nullptr, &m_vkSemaphoreFinishedRendering);

        if (resultCreateSemaphore != VK_SUCCESS)
        {
            std::cout << "ERROR: Failed to create semaphore to control rendering." << std::endl;
            return false;
        }

        // Build Command Buffers!
        // These are for normal execution and will NOT have GPA enabled.
        // There is a 1-1 relationship between the number of prebuiltPerFrameResources
        // and the number of framebuffers, so the same index can be used for both.
        for (size_t i = 0; i < m_prebuiltPerFrameResources.size(); i++)
        {
            bool enableGPA = false;
            gpa_uint32 gpaPassIndex = 0;

            PreBuildCommandBuffers(&m_prebuiltPerFrameResources[i], m_perSwapchainImageResources.vkFramebuffers[i], enableGPA, gpaPassIndex);
        }

        if (GPUPerfAPI.IsLoaded())
        {
            // Build additional command buffers to support GPA profiling.
            // There will be one of these for each of the passes that GPA needs to perform,
            // so the frame buffers will need to be cycled among them.
            for (size_t i = 0; i < m_prebuiltPerFrameResourcesWithGPA.size(); i++)
            {
                uint32_t swapchainIndex = i % swapchainImageCount;
                bool enableGPA = true;
                gpa_uint32 gpaPassIndex = static_cast<gpa_uint32>(i);

                PreBuildCommandBuffers(&m_prebuiltPerFrameResourcesWithGPA[i], m_perSwapchainImageResources.vkFramebuffers[swapchainIndex], enableGPA, gpaPassIndex);
            }
        }

        if (GPUPerfAPI.IsLoaded())
        {
            // All command buffers have been built; ending the session will confirm this.
            GPA_Status statusGPAEndSession = GPUPerfAPI.m_pGpaFuncTable->GPA_EndSession(m_GPASessionId);

            if (statusGPAEndSession != GPA_STATUS_OK)
            {
                std::cout << "ERROR: Failed to end GPA session." << std::endl;
            }
        }

        // Set the app as being successfully intialized;
        m_bInitialized = true;

        return true;
    }

    /// Draws the scene in a method that can be called on any platform.
    void DrawScene()
    {
        // Get the index of an image in the swapchain that is available to be rendered into.
        // The previously discussed presentation modes may affect the order that the swapchain images become available
        // for rendering, so it is necessary to ask which image the presentation engine wants to use next.
        // This call may stall until an image is available, so it may be advantagous to do other necessary processing prior
        // to this call to take advantage of the aschronous nature of the CPU, GPU, and presentation engines. For example,
        // render-to-texture operations could be submitted before this call, and other CPU-side operations could be done,
        // Then this call is executed to obtain an image index and do the final render and presentation.
        uint32_t swapchainImageIndex = 0;
        VkResult resultAcquireNextImage = vkAcquireNextImageKHR(m_vkDevice, m_vkSwapchain, std::numeric_limits<uint64_t>::max(), m_vkSemaphoreAcquiredSwapchainImage, VK_NULL_HANDLE, &swapchainImageIndex);

        if (resultAcquireNextImage != VK_SUCCESS)
        {
            std::cout << "ERROR: Failed to acquire next image." << std::endl;
        }

        std::vector<VkCommandBuffer> commandBuffersToSubmit;

        // Since GPA needs multiple passes, the command buffers also need to be cycled through similar to the swapchain image index.
        if (GPUPerfAPI.IsLoaded() &&
            m_frameCount < m_requiredPassCount)
        {
            // GPA is actively profiling, so make sure to use the resources with GPA Perf Counters enabled, and
            // use the frameCount to determine which set of resources (ie: which GPA pass) to submit. Each pass has
            // been specifically built to correspond to an existing swapchain image. That is to say, that there is
            // an assumption that the call to vkAcquireNextImageKHR() above will return the images in a cyclic manner.
            // This assumption may not hold true if a different PRESENT_MODE is used by the application.
            commandBuffersToSubmit.push_back(m_prebuiltPerFrameResourcesWithGPA[m_frameCount].cube.commandBuffer);
            commandBuffersToSubmit.push_back(m_prebuiltPerFrameResourcesWithGPA[m_frameCount].wireframe.commandBuffer);
            commandBuffersToSubmit.push_back(m_prebuiltPerFrameResourcesWithGPA[m_frameCount].cubeAndWireframe.commandBufferCube);
            commandBuffersToSubmit.push_back(m_prebuiltPerFrameResourcesWithGPA[m_frameCount].cubeAndWireframe.commandBufferWireframe);
        }
        else
        {
            // GPA is not profiling, so use the command buffers that do not have any counters enabled, and
            // use the swapchain index to select which resources to submit so that it draws to the correct swapchain image.
            commandBuffersToSubmit.push_back(m_prebuiltPerFrameResources[swapchainImageIndex].cube.commandBuffer);
            commandBuffersToSubmit.push_back(m_prebuiltPerFrameResources[swapchainImageIndex].wireframe.commandBuffer);
            commandBuffersToSubmit.push_back(m_prebuiltPerFrameResources[swapchainImageIndex].cubeAndWireframe.commandBufferCube);
            commandBuffersToSubmit.push_back(m_prebuiltPerFrameResources[swapchainImageIndex].cubeAndWireframe.commandBufferWireframe);
        }

        // Setup the submit.
        // With a waitDestStageMask of TOP_OF_PIPE, the submit will wait at the very beginning for the waitSemaphores
        // (AcquiredSwapchainImage) to get signaled, thus indicating that a new swapchain image is available to be
        // rendered into. This synchronizes the processing of the current frame until an earlier frame has completed
        // and a new swapchain image is available. Earlier, the numbers of requested swapchain images was +1 from the
        // minimum, so theoretically this synchronization shouldn't cause any significant delays.
        //
        // If the demo had a lot more vertex processing to do, it might be advantagous to set the waitDestStageMask to
        // COLOR_ATTACHMENT_OUTPUT so that vertex processing could happen even while earlier frames are still being
        // rendered or presented. That approach would have required that the RenderPass subpass was setup with a
        // dependency that would transition the color attachment from the external subpass (being presented) to
        // allowing read / write access from the "current" subpass.
        //
        // The submit info also specifies which command buffers to execute, and which semaphores to signal when those
        // command buffers have completed. This needs to be setup (or at least modified) each frame to update which
        // swapchainImageIndex was acquired for rendering. It may not always be round-robin or deterministic depending
        // on the selected present mode and other workloads on the system.
        VkPipelineStageFlags waitDestStageMask = { VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT };
        VkSemaphore waitSemaphores[] = { m_vkSemaphoreAcquiredSwapchainImage };
        VkSemaphore signalSemaphores[] = { m_vkSemaphoreFinishedRendering };
        VkSubmitInfo submitInfo = {};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.pNext = nullptr;
        submitInfo.waitSemaphoreCount = 1;
        submitInfo.pWaitSemaphores = waitSemaphores;
        submitInfo.pWaitDstStageMask = &waitDestStageMask;
        submitInfo.commandBufferCount = static_cast<uint32_t>(commandBuffersToSubmit.size());
        submitInfo.pCommandBuffers = commandBuffersToSubmit.data();
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = signalSemaphores;

        VkResult resultQueueSubmit = vkQueueSubmit(m_vkQueue, 1, &submitInfo, VK_NULL_HANDLE);

        if (resultQueueSubmit != VK_SUCCESS)
        {
            std::cout << "ERROR: Failed to submit to queue." << std::endl;
        }

        // Now present the rendered image to the screen!
        // The present info specifies that presentation shouldn't happen until the signalSemaphores have been signaled
        // (ie: the submitted workload has finished rendering).
        // It also specifies which swapchain to present to, and specifically the index of the swapchain image to use.
        VkPresentInfoKHR presentInfo = {};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
        presentInfo.pNext = nullptr;
        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = signalSemaphores;
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = &m_vkSwapchain;
        presentInfo.pImageIndices = &swapchainImageIndex;
        presentInfo.pResults = nullptr;

        VkResult resultPresent = vkQueuePresentKHR(m_vkQueue, &presentInfo);

        if (resultPresent != VK_SUCCESS)
        {
            std::cout << "ERROR: Failed to present queue." << std::endl;
        }

        if (GPUPerfAPI.IsLoaded() && m_frameCount == m_requiredPassCount)
        {

            bool isReady = false;
            const uint32_t timeout = 10000; // ms
            auto startTime = std::chrono::high_resolution_clock::now();

            do
            {
                isReady = GPA_STATUS_OK == GPUPerfAPI.m_pGpaFuncTable->GPA_IsSessionComplete(m_GPASessionId);

                if (!isReady)
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(0));

                    auto endTime = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double, std::milli> elapsedTime = endTime - startTime;

                    if (elapsedTime.count() > timeout)
                    {
                        break;
                    }
                }
            }
            while (!isReady);


            if (isReady)
            {
                gpa_uint32 sampleCount = 0;
                GPUPerfAPI.m_pGpaFuncTable->GPA_GetSampleCount(m_GPASessionId, &sampleCount);

                std::cout << "There were " << sampleCount << " GPA samples recorded." << std::endl;

                // Open the CSV file so that counter results also get output there.
                if (!GPUPerfAPI.OpenCSVFile())
                {
                    std::cout << "ERROR: Unable to open CSV file to output profile results." << std::endl;
                }

                // NOTE: we can't loop over these because it is not guaranteed that the sampleIds will be 0-based and monotonically increasing.
                GPUPerfAPI.PrintGPASampleResults(m_GPAContextId, m_GPASessionId, 0);
                GPUPerfAPI.PrintGPASampleResults(m_GPAContextId, m_GPASessionId, 1);
                GPUPerfAPI.PrintGPASampleResults(m_GPAContextId, m_GPASessionId, 2);

                // Close the CSV file so that it actually gets saved out.
                GPUPerfAPI.CloseCSVFile();

                // Since the goal is to demonstrate GPUPerfAPI, the demo can be exited now that the profile is complete.
                // UPDATE: For testing, it was requested to let the app continue running after the profile. Leaving the
                // exit flag here to demonstrate when this would happen.
                //m_bExit = true;
            }
        }

        ++m_frameCount;
    }

    /// General vulkan object destruction.
    void Destroy()
    {
        if (GPUPerfAPI.IsLoaded())
        {
            if (m_GPASessionId != nullptr)
            {
                GPA_Status statusGPADeleteSession = GPUPerfAPI.m_pGpaFuncTable->GPA_DeleteSession(m_GPASessionId);

                if (statusGPADeleteSession != GPA_STATUS_OK)
                {
                    std::cout << "ERROR: Failed to delete GPA session." << std::endl;
                }
            }

            if (m_GPAContextId != nullptr)
            {
                GPA_Status statusGPACloseContext = GPUPerfAPI.m_pGpaFuncTable->GPA_CloseContext(m_GPAContextId);

                if (statusGPACloseContext != GPA_STATUS_OK)
                {
                    std::cout << "ERROR: Failed to close GPA Context." << std::endl;
                }
            }
        }

        if (m_vkDevice != VK_NULL_HANDLE)
        {
            VkResult resultDeviceWaitIdle = vkDeviceWaitIdle(m_vkDevice);

            if (resultDeviceWaitIdle != VK_SUCCESS)
            {
                std::cout << "ERROR: Failed to wait for the device to idle." << std::endl;
            }

            if (m_vkSemaphoreAcquiredSwapchainImage != VK_NULL_HANDLE)
            {
                vkDestroySemaphore(m_vkDevice, m_vkSemaphoreAcquiredSwapchainImage, nullptr);
                m_vkSemaphoreAcquiredSwapchainImage = VK_NULL_HANDLE;
            }

            if (m_vkSemaphoreFinishedRendering != VK_NULL_HANDLE)
            {
                vkDestroySemaphore(m_vkDevice, m_vkSemaphoreFinishedRendering, nullptr);
                m_vkSemaphoreFinishedRendering = VK_NULL_HANDLE;
            }

            if (m_vkCommandPool != VK_NULL_HANDLE)
            {
                vkDestroyCommandPool(m_vkDevice, m_vkCommandPool, nullptr);
                m_vkCommandPool = VK_NULL_HANDLE;
            }

            if (m_vkPipelineLayout != VK_NULL_HANDLE)
            {
                vkDestroyPipelineLayout(m_vkDevice, m_vkPipelineLayout, nullptr);
                m_vkPipelineLayout = VK_NULL_HANDLE;
            }

            if (m_vertexShaderModule != VK_NULL_HANDLE)
            {
                vkDestroyShaderModule(m_vkDevice, m_vertexShaderModule, nullptr);
                m_vertexShaderModule = VK_NULL_HANDLE;
            }

            if (m_fragmentShaderModule != VK_NULL_HANDLE)
            {
                vkDestroyShaderModule(m_vkDevice, m_fragmentShaderModule, nullptr);
                m_fragmentShaderModule = VK_NULL_HANDLE;
            }

            if (m_vkPipeline != VK_NULL_HANDLE)
            {
                vkDestroyPipeline(m_vkDevice, m_vkPipeline, nullptr);
                m_vkPipeline = VK_NULL_HANDLE;
            }

            if (m_fragmentShaderWireframeModule != VK_NULL_HANDLE)
            {
                vkDestroyShaderModule(m_vkDevice, m_fragmentShaderWireframeModule, nullptr);
                m_fragmentShaderWireframeModule = VK_NULL_HANDLE;
            }

            if (m_vkPipelineWireframe != VK_NULL_HANDLE)
            {
                vkDestroyPipeline(m_vkDevice, m_vkPipelineWireframe, nullptr);
                m_vkPipeline = VK_NULL_HANDLE;
            }

            if (m_vkRenderPassInitial != VK_NULL_HANDLE)
            {
                vkDestroyRenderPass(m_vkDevice, m_vkRenderPassInitial, nullptr);
                m_vkRenderPassInitial = VK_NULL_HANDLE;
            }

            if (m_vkRenderPassMid != VK_NULL_HANDLE)
            {
                vkDestroyRenderPass(m_vkDevice, m_vkRenderPassMid, nullptr);
                m_vkRenderPassMid = VK_NULL_HANDLE;
            }

            if (m_vkRenderPassFinal != VK_NULL_HANDLE)
            {
                vkDestroyRenderPass(m_vkDevice, m_vkRenderPassFinal, nullptr);
                m_vkRenderPassFinal = VK_NULL_HANDLE;
            }

            for (uint32_t i = 0; i < m_perSwapchainImageResources.vkFramebuffers.size(); ++i)
            {
                vkDestroyFramebuffer(m_vkDevice, m_perSwapchainImageResources.vkFramebuffers[i], nullptr);
            }

            m_perSwapchainImageResources.vkFramebuffers.clear();

            for (uint32_t i = 0; i < m_perSwapchainImageResources.swapchainImageViews.size(); ++i)
            {
                VkImageView& view = m_perSwapchainImageResources.swapchainImageViews[i];

                if (view != VK_NULL_HANDLE)
                {
                    vkDestroyImageView(m_vkDevice, view, nullptr);
                }
            }

            m_perSwapchainImageResources.swapchainImageViews.clear();

            if (m_vkSwapchain != VK_NULL_HANDLE)
            {
                vkDestroySwapchainKHR(m_vkDevice, m_vkSwapchain, nullptr);
                m_vkSwapchain = VK_NULL_HANDLE;
            }

            vkDestroyDevice(m_vkDevice, nullptr);
            m_vkDevice = VK_NULL_HANDLE;
        }

        if (m_vkInstance != VK_NULL_HANDLE)
        {
            if (m_vkSurface != VK_NULL_HANDLE)
            {
                vkDestroySurfaceKHR(m_vkInstance, m_vkSurface, nullptr);
                m_vkSurface = VK_NULL_HANDLE;
            }

            if (m_vkDebugReportCallback != VK_NULL_HANDLE)
            {
                PFN_vkDestroyDebugReportCallbackEXT pvkDestroyDebugReportCallback;
                VK_INSTANCE_GET_PROC_ADDR_VOID(pvkDestroyDebugReportCallback, m_vkInstance, vkDestroyDebugReportCallbackEXT);
                pvkDestroyDebugReportCallback(m_vkInstance, m_vkDebugReportCallback, nullptr);
                m_vkDebugReportCallback = VK_NULL_HANDLE;
            }

            vkDestroyInstance(m_vkInstance, NULL);
            m_vkInstance = VK_NULL_HANDLE;
        }

        if (GPUPerfAPI.IsLoaded())
        {
            GPUPerfAPI.m_pGpaFuncTable->GPA_Destroy();

            GPUPerfAPI.Unload();
        }

#if defined(VK_USE_PLATFORM_XCB_KHR)

        if (m_pXcbConnection != nullptr)
        {
            xcb_destroy_window(m_pXcbConnection, m_xcbWindow);
            xcb_disconnect(m_pXcbConnection);
            m_pXcbConnection = nullptr;
        }

        if (m_xcbAtomWmDeleteWindow != nullptr)
        {
            free(m_xcbAtomWmDeleteWindow);
            m_xcbAtomWmDeleteWindow = nullptr;
        }

#endif

    }

public:
    /// Short name that will be used as the application name.
    const std::string m_cShortName = "AMD VkColorCube";

    /// Longer name that will be displayed in the window title bar.
    const std::string m_cLongName = "The AMD Vulkan Color Cube Sample";

    /// Default window width.
    const uint32_t m_cDefaultWindowWidth = 900;

    /// Default window height.
    const uint32_t m_cDefaultWindowHeight = 300;

private:

    /// Caches an extension name that should have been returned by vkEnumerateInstanceExtensionProperties.
    /// \param pExtensionName A name to add to the list of supported instance extensions.
    void AddSupportedInstanceExtension(const char* pExtensionName)
    {
        m_supportedInstanceExtensions.insert(std::pair<const std::string, bool>(std::string(pExtensionName), true));
    }

    /// Checks to see if the supplied extension is in the supported instance extension list.
    /// \param pExtensionName The name of the extension to seek.
    /// \return True if the extension is supported; false otherwise.
    bool IsInstanceExtensionSupported(const char* pExtensionName)
    {
        return m_supportedInstanceExtensions.end() != m_supportedInstanceExtensions.find(std::string(pExtensionName));
    }

    /// Caches an extension name that should have been returned by vkEnumerateDeviceExtensionProperties.
    /// \param pExtensionName A name to add to the list of supported device extensions.
    void AddSupportedDeviceExtension(const char* pExtensionName)
    {
        m_supportedDeviceExtensions.insert(std::pair<const std::string, bool>(std::string(pExtensionName), true));
    }

    /// Checks to see if the supplied extension is in the supported device extension list.
    /// \param pExtensionName The name of the extension to seek.
    /// \return True if the extension is supported; false otherwise.
    bool IsDeviceExtensionSupported(const char* pExtensionName)
    {
        return m_supportedDeviceExtensions.end() != m_supportedDeviceExtensions.find(std::string(pExtensionName));
    }

    /// List of instance extension names that are required by this demo.
    std::vector<const char*> m_requiredInstanceExtensions;

    /// List of device extension names that are required by this demo.
    std::vector<const char*> m_requiredDeviceExtensions;

#if defined(VK_USE_PLATFORM_WIN32_KHR)
    /// Application windowing instance
    HINSTANCE m_hInstance;

    /// Window handle
    HWND m_hWindow;
#elif defined(VK_USE_PLATFORM_XCB_KHR)
    Display* m_pDisplay;
    xcb_connection_t* m_pXcbConnection;
    xcb_screen_t* m_pXcbScreen;
    xcb_window_t m_xcbWindow;
public:
    xcb_intern_atom_reply_t* m_xcbAtomWmDeleteWindow;
private:
#endif

    /// The instance of the Vulkan API.
    VkInstance m_vkInstance;

    /// The default index of the physical device (ie: GPU) to use when running this demo.
    const uint32_t m_cDefaultPhysicalDeviceIndex = 0;

    /// The selected physical device that will execute this demo.
    VkPhysicalDevice m_vkPhysicalDevice;

    /// Properties of the selected physical device.
    VkPhysicalDeviceProperties m_vkPhysicalDeviceProperties;

    /// Available features of the selected physical device.
    VkPhysicalDeviceFeatures m_vkPhysicalDeviceFeatures;

    /// Properties of the selected physical device.
    VkPhysicalDeviceMemoryProperties m_vkPhysicalDeviceMemoryProperties;

    /// The logical device that will be used to render.
    VkDevice m_vkDevice;

    /// The queue on which rendering commands will be scheduled.
    VkQueue m_vkQueue;

    /// The index within the queue family from which the vkQueue was obtained.
    uint32_t m_queueIndex;

    /// The display surface that the demo will render to.
    VkSurfaceKHR m_vkSurface;

    /// The selected format of the presentation surface.
    VkSurfaceFormatKHR m_vkSurfaceFormat;

    /// Index of the queue family that supports graphics.
    /// Will be the same as m_queueFamilyIndexPresent.
    uint32_t m_queueFamilyIndexGraphics;

    /// Index of the queue family that supports present.
    /// Will be the same as m_queueFamilyIndexGraphics.
    uint32_t m_queueFamilyIndexPresent;

    /// The mode Vulkan WSI will use to present the swapchain images.
    VkPresentModeKHR m_vkPresentMode;

    /// Capabilities of the display surface.
    VkSurfaceCapabilitiesKHR m_vkSurfaceCapabilities;

    /// The swapchain that will be used to present.
    VkSwapchainKHR m_vkSwapchain;

    /// Swapchain image Extents (resolution)
    VkExtent2D m_swapchainImageExtent;

    /// These objects are unique to each swapchain image.
    /// Use the same index for each of these vectors to access corresponding objects.
    struct PerSwapchainImageResources
    {
        /// Handles to the swapchain images.
        std::vector<VkImage> swapchainImages;

        /// Views into the swapchain images.
        std::vector<VkImageView> swapchainImageViews;

        /// Framebuffers - one for each swapchain image.
        std::vector<VkFramebuffer> vkFramebuffers;
    } m_perSwapchainImageResources;

    /// Container for pre-built resources that are needed to render a single frame,
    /// but are also different for each frame. Namely, these command buffers are uniquely
    /// associated with different framebuffers
    struct PrebuiltPerFrameResources
    {
        /// Container for objects related to drawing the cube.
        struct Cube
        {
            /// The command buffer that will draw the cube.
            VkCommandBuffer commandBuffer;

            /// The GPA CommandList that will include the sample that draws the cube.
            GPA_CommandListId gpaCommandListId;

            /// Sample Id that the application (not GPA) assigns to the cube.
            /// The cube will have this same sampleId in all passes.
            const gpa_uint32 gpaSampleId = 0;
        } cube;

        /// Container for objects related to drawing the wireframe.
        struct Wireframe
        {
            /// The command buffer that will draw the wireframe
            VkCommandBuffer commandBuffer;

            /// The GPA CommandList that will include the sample that draws the cube.
            GPA_CommandListId gpaCommandListId;

            /// Sample Id that the application (not GPA) assigns to the wireframe.
            /// The wireframe will have this same sampleId in all passes.
            const gpa_uint32 gpaSampleId = 1;
        } wireframe;

        /// Container for objects related to drawing the cube and wireframe in two
        /// different command buffers, and a single GPA Sample that starts in the first
        /// command buffer and continues into the second.
        struct CubeAndWireframe
        {
            /// The command buffer that will draw the cube.
            VkCommandBuffer commandBufferCube;

            /// The command buffer that will draw the wireframe.
            VkCommandBuffer commandBufferWireframe;

            /// The GPA CommandListId that will draw the cube and start the GPA Sample.
            GPA_CommandListId gpaCommandListIdCube;

            /// The GPA CommandList that will draws the wireframe and will end the GPA Sample.
            GPA_CommandListId gpaCommandListIdWireframe;

            /// Sample Id that the application (not GPA) assigns to the cube wireframe.
            /// The combined cube + wireframe sample will have this same sampleId in all passes.
            const gpa_uint32 gpaSampleId = 2;
        } cubeAndWireframe;

    };

    /// Vector of pre-built per-frame resources.
    /// There will be one entry per swapchain image in this vector,
    /// as each one is pre-built to output to a specific swapchain image.
    /// When building these resources, GPA calls SHOULD NOT be inserted.
    std::vector<PrebuiltPerFrameResources> m_prebuiltPerFrameResources;

    /// Vector of pre-built per-frame resources.
    /// There will be one entry per swapchain image in this vector,
    /// as each one is pre-built to output to a specific swapchain image.
    /// When building these resources, GPA calls SHOULD be inserted.
    std::vector<PrebuiltPerFrameResources> m_prebuiltPerFrameResourcesWithGPA;

    /// The render pass that will be used first and will clear the screan.
    VkRenderPass m_vkRenderPassInitial;

    /// The render pass that is used for all mid-frame draws which leaves
    /// the rendertarget in a COLOR_ATTACHMENT_OPTIMAL layout.
    VkRenderPass m_vkRenderPassMid;

    /// The render pass that is used for the final draws which puts the
    /// rendertarget in a PRESENT_SRC layout. This could have also been
    /// done by using a pipeline barrier.
    VkRenderPass m_vkRenderPassFinal;

    /// The pipeline layout.
    VkPipelineLayout m_vkPipelineLayout;

    /// The graphics pipeline object.
    VkPipeline m_vkPipeline;

    /// The graphics pipeline object to draw wireframes.
    VkPipeline m_vkPipelineWireframe;

    /// The command pool which will contain the necessary command buffers.
    VkCommandPool m_vkCommandPool;

    /// Vertex shader module
    VkShaderModule m_vertexShaderModule;

    /// Fragment shader module
    VkShaderModule m_fragmentShaderModule;

    /// Fragment shader module for drawing wireframe
    VkShaderModule m_fragmentShaderWireframeModule;

    /// Semaphore to indicate when a swapchain image has been acquired.
    VkSemaphore m_vkSemaphoreAcquiredSwapchainImage;

    /// Semaphore to indicate when the rendering has completed.
    VkSemaphore m_vkSemaphoreFinishedRendering;

    /// Tracks the existence (or enabled state) of the debug report callback.
    VkDebugReportCallbackEXT m_vkDebugReportCallback;

    /// GPA Context
    GPA_ContextId m_GPAContextId;

    /// GPA session
    GPA_SessionId m_GPASessionId;

    /// Number of required GPA passes based on the set of enabled counters.
    uint32_t m_requiredPassCount;

    /// Number of frames that have been rendered.
    uint32_t m_frameCount;

    /// Flag to indicate whether or not to print debug output.
    bool m_bPrintDebugOutput;

    /// Flag to indicatee whether or not to print GPA counter names & descriptions
    // when GPA is initialized.
    bool m_bPrintGPACounterInfo;

    /// Flag to indicate that the demo has been successfully initialized.
    bool m_bInitialized;

    /// Flag to indicate that the demo should exit.
    bool m_bExit;

private:
    /// Stores the list of available instance extensions as exposed by the Vulkan implementation.
    std::map< const std::string, bool > m_supportedInstanceExtensions;

    /// Stores the list of available device extensions as exposed by the Vulkan implementation.
    std::map< const std::string, bool > m_supportedDeviceExtensions;

    /// Builds command buffers that will not be reset and rebuilt between frames.
    /// \param pPrebuiltResources Pointer to the set of resources that need to be built.
    /// \param framebuffer The framebuffer that is connected to specific swapchain images
    /// that should be rendered into by these command buffers.
    /// \param enableGPA Indicates whether GPA profiling should be enabled in these command buffers or not.
    /// \param gpaPassIndex If GPA is enabled for these command buffers, this indicates which profile pass is being built; ignored if enableGPA is false.
    void PreBuildCommandBuffers(PrebuiltPerFrameResources* pPrebuiltResources, VkFramebuffer framebuffer, bool enableGPA, uint32_t gpaPassIndex)
    {
        // Setup some standard structs that can be used for all sets of CommandBuffers since they all come from the same pool.

        // Information about allocating command buffers.
        VkCommandBufferAllocateInfo cmdBufferAllocInfo = {};
        cmdBufferAllocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        cmdBufferAllocInfo.pNext = nullptr;
        cmdBufferAllocInfo.commandPool = m_vkCommandPool;
        cmdBufferAllocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        cmdBufferAllocInfo.commandBufferCount = 1;

        // Information about beginning a command buffer.
        VkCommandBufferBeginInfo cmdBufferBeginInfo = {};
        cmdBufferBeginInfo.pNext = nullptr;
        cmdBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        cmdBufferBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
        cmdBufferBeginInfo.pInheritanceInfo = nullptr;

        // Create three viewports and scissors to divide the window into thirds.
        float fThirdWidth = static_cast<float>(m_swapchainImageExtent.width / 3);
        uint32_t uThirdWidth = m_swapchainImageExtent.width / 3;
        VkViewport viewports[3];
        VkRect2D scissorRects[3];

        for (uint32_t i = 0; i < 3; ++i)
        {
            viewports[i].x = static_cast<float>(i * uThirdWidth);
            viewports[i].y = 0.0f;
            viewports[i].width = fThirdWidth;
            viewports[i].height = static_cast<float>(m_swapchainImageExtent.height);
            viewports[i].minDepth = 0.0f;
            viewports[i].maxDepth = 1.0f;

            scissorRects[i].offset = VkOffset2D({ static_cast<int32_t>(i * uThirdWidth), 0 });
            scissorRects[i].extent.width = uThirdWidth;
            scissorRects[i].extent.height = m_swapchainImageExtent.height;
        }

        // Generate calls to draw the cube.
        {
            // Allocate a command buffer for the cube.
            VkResult resultAllocateCmdBuffers = vkAllocateCommandBuffers(m_vkDevice, &cmdBufferAllocInfo, &(pPrebuiltResources->cube.commandBuffer));

            if (resultAllocateCmdBuffers != VK_SUCCESS)
            {
                std::cout << "ERROR: Failed to allocate command buffers." << std::endl;
                return;
            }

            vkBeginCommandBuffer(pPrebuiltResources->cube.commandBuffer, &cmdBufferBeginInfo);

            if (enableGPA)
            {
                GPUPerfAPI.m_pGpaFuncTable->GPA_BeginCommandList(m_GPASessionId, gpaPassIndex, pPrebuiltResources->cube.commandBuffer, GPA_COMMAND_LIST_PRIMARY, &pPrebuiltResources->cube.gpaCommandListId);
            }

            VkClearValue clearColor = { 0.0f, 0.0f, 0.0f, 1.0f };

            VkRenderPassBeginInfo renderPassBeginInfo = {};
            renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
            renderPassBeginInfo.pNext = nullptr;
            renderPassBeginInfo.renderPass = m_vkRenderPassInitial;
            renderPassBeginInfo.framebuffer = framebuffer;
            renderPassBeginInfo.renderArea.offset = { 0, 0 };
            renderPassBeginInfo.renderArea.extent = m_swapchainImageExtent;
            renderPassBeginInfo.clearValueCount = 1;
            renderPassBeginInfo.pClearValues = &clearColor;

            vkCmdBeginRenderPass(pPrebuiltResources->cube.commandBuffer, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

            vkCmdSetViewport(pPrebuiltResources->cube.commandBuffer, 0, 1, &viewports[0]);
            vkCmdSetScissor(pPrebuiltResources->cube.commandBuffer, 0, 1, &scissorRects[0]);

            vkCmdBindPipeline(pPrebuiltResources->cube.commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, m_vkPipeline);

            if (enableGPA)
            {
                GPUPerfAPI.m_pGpaFuncTable->GPA_BeginSample(pPrebuiltResources->cube.gpaSampleId, pPrebuiltResources->cube.gpaCommandListId);
            }

            vkCmdDraw(pPrebuiltResources->cube.commandBuffer, 36, 1, 0, 0);

            if (enableGPA)
            {
                GPUPerfAPI.m_pGpaFuncTable->GPA_EndSample(pPrebuiltResources->cube.gpaCommandListId);
            }

            vkCmdEndRenderPass(pPrebuiltResources->cube.commandBuffer);

            if (enableGPA)
            {
                GPUPerfAPI.m_pGpaFuncTable->GPA_EndCommandList(pPrebuiltResources->cube.gpaCommandListId);
            }

            VkResult resultEndCmdBuffer = vkEndCommandBuffer(pPrebuiltResources->cube.commandBuffer);

            if (resultEndCmdBuffer != VK_SUCCESS)
            {
                std::cout << "ERROR: Failed to end command buffer." << std::endl;
            }
        }

        // Now generate calls to overlay the wireframe
        {
            VkResult resultAllocateCmdBuffers = vkAllocateCommandBuffers(m_vkDevice, &cmdBufferAllocInfo, &(pPrebuiltResources->wireframe.commandBuffer));

            if (resultAllocateCmdBuffers != VK_SUCCESS)
            {
                std::cout << "ERROR: Failed to allocate wireframe command buffers." << std::endl;
                return;
            }

            vkBeginCommandBuffer(pPrebuiltResources->wireframe.commandBuffer, &cmdBufferBeginInfo);

            if (enableGPA)
            {
                GPUPerfAPI.m_pGpaFuncTable->GPA_BeginCommandList(m_GPASessionId, gpaPassIndex, pPrebuiltResources->wireframe.commandBuffer, GPA_COMMAND_LIST_PRIMARY, &pPrebuiltResources->wireframe.gpaCommandListId);
            }

            VkRenderPassBeginInfo renderPassBeginInfoWireframe = {};
            renderPassBeginInfoWireframe.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
            renderPassBeginInfoWireframe.pNext = nullptr;
            renderPassBeginInfoWireframe.renderPass = m_vkRenderPassMid;
            renderPassBeginInfoWireframe.framebuffer = framebuffer;
            renderPassBeginInfoWireframe.renderArea.offset = { 1 * static_cast<int32_t>(m_swapchainImageExtent.width) / 3, 0 };
            renderPassBeginInfoWireframe.renderArea.extent = m_swapchainImageExtent;
            renderPassBeginInfoWireframe.renderArea.extent.width /= 3u;
            renderPassBeginInfoWireframe.clearValueCount = 0;
            renderPassBeginInfoWireframe.pClearValues = nullptr;

            vkCmdBeginRenderPass(pPrebuiltResources->wireframe.commandBuffer, &renderPassBeginInfoWireframe, VK_SUBPASS_CONTENTS_INLINE);

            vkCmdSetViewport(pPrebuiltResources->wireframe.commandBuffer, 0, 1, &viewports[1]);
            vkCmdSetScissor(pPrebuiltResources->wireframe.commandBuffer, 0, 1, &scissorRects[1]);

            vkCmdBindPipeline(pPrebuiltResources->wireframe.commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, m_vkPipelineWireframe);

            if (enableGPA)
            {
                GPUPerfAPI.m_pGpaFuncTable->GPA_BeginSample(pPrebuiltResources->wireframe.gpaSampleId, pPrebuiltResources->wireframe.gpaCommandListId);
            }

            vkCmdDraw(pPrebuiltResources->wireframe.commandBuffer, 36, 1, 0, 0);

            if (enableGPA)
            {
                GPUPerfAPI.m_pGpaFuncTable->GPA_EndSample(pPrebuiltResources->wireframe.gpaCommandListId);
            }

            vkCmdEndRenderPass(pPrebuiltResources->wireframe.commandBuffer);

            if (enableGPA)
            {
                GPUPerfAPI.m_pGpaFuncTable->GPA_EndCommandList(pPrebuiltResources->wireframe.gpaCommandListId);
            }

            VkResult resultEndCmdBufferWireframe = vkEndCommandBuffer(pPrebuiltResources->wireframe.commandBuffer);

            if (resultEndCmdBufferWireframe != VK_SUCCESS)
            {
                std::cout << "ERROR: Failed to end wireframe command buffer." << std::endl;
            }
        }

        // Generate calls to draw the cube in one command buffer, the wireframe in a second command buffer,
        // and have a GPA Sample continue between the two command buffers.
        {
            // Allocate a command buffer for the cube.
            VkResult resultAllocateCmdBuffers = vkAllocateCommandBuffers(m_vkDevice, &cmdBufferAllocInfo, &(pPrebuiltResources->cubeAndWireframe.commandBufferCube));

            if (resultAllocateCmdBuffers != VK_SUCCESS)
            {
                std::cout << "ERROR: Failed to allocate command buffers." << std::endl;
                return;
            }

            vkBeginCommandBuffer(pPrebuiltResources->cubeAndWireframe.commandBufferCube, &cmdBufferBeginInfo);

            if (enableGPA)
            {
                GPUPerfAPI.m_pGpaFuncTable->GPA_BeginCommandList(m_GPASessionId, gpaPassIndex, pPrebuiltResources->cubeAndWireframe.commandBufferCube, GPA_COMMAND_LIST_PRIMARY, &pPrebuiltResources->cubeAndWireframe.gpaCommandListIdCube);
            }

            VkClearValue clearColor = { 0.0f, 0.0f, 0.0f, 1.0f };

            VkRenderPassBeginInfo renderPassBeginInfo = {};
            renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
            renderPassBeginInfo.pNext = nullptr;
            renderPassBeginInfo.renderPass = m_vkRenderPassMid;
            renderPassBeginInfo.framebuffer = framebuffer;
            renderPassBeginInfo.renderArea.offset = { 2 * static_cast<int32_t>(m_swapchainImageExtent.width) / 3, 0 };
            renderPassBeginInfo.renderArea.extent = m_swapchainImageExtent;
            renderPassBeginInfo.renderArea.extent.width /= 3u;
            renderPassBeginInfo.clearValueCount = 0;// 1;
            renderPassBeginInfo.pClearValues = nullptr;// &clearColor;

            vkCmdBeginRenderPass(pPrebuiltResources->cubeAndWireframe.commandBufferCube, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

            vkCmdSetViewport(pPrebuiltResources->cubeAndWireframe.commandBufferCube, 0, 1, &viewports[2]);
            vkCmdSetScissor(pPrebuiltResources->cubeAndWireframe.commandBufferCube, 0, 1, &scissorRects[2]);

            vkCmdBindPipeline(pPrebuiltResources->cubeAndWireframe.commandBufferCube, VK_PIPELINE_BIND_POINT_GRAPHICS, m_vkPipeline);

            if (enableGPA)
            {
                GPUPerfAPI.m_pGpaFuncTable->GPA_BeginSample(pPrebuiltResources->cubeAndWireframe.gpaSampleId, pPrebuiltResources->cubeAndWireframe.gpaCommandListIdCube);
            }

            vkCmdDraw(pPrebuiltResources->cubeAndWireframe.commandBufferCube, 36, 1, 0, 0);

            // COMMENT FOR DEMONSTRATION PURPOSES:
            // Do not end the GPA Sample, because it will be continued on another command list.
            //if (enableGPA)
            //{
            //    GPUPerfAPI.m_pGpaFuncTable->GPA_EndSample(pPrebuiltResources->cubeAndWireframe.gpaCommandListId);
            //}

            vkCmdEndRenderPass(pPrebuiltResources->cubeAndWireframe.commandBufferCube);

            if (enableGPA)
            {
                GPUPerfAPI.m_pGpaFuncTable->GPA_EndCommandList(pPrebuiltResources->cubeAndWireframe.gpaCommandListIdCube);
            }

            VkResult resultEndCmdBuffer = vkEndCommandBuffer(pPrebuiltResources->cubeAndWireframe.commandBufferCube);

            if (resultEndCmdBuffer != VK_SUCCESS)
            {
                std::cout << "ERROR: Failed to end command buffer." << std::endl;
            }
        }

        // Now generate calls to overlay the wireframe
        {
            VkResult resultAllocateCmdBuffers = vkAllocateCommandBuffers(m_vkDevice, &cmdBufferAllocInfo, &(pPrebuiltResources->cubeAndWireframe.commandBufferWireframe));

            if (resultAllocateCmdBuffers != VK_SUCCESS)
            {
                std::cout << "ERROR: Failed to allocate wireframe command buffers." << std::endl;
                return;
            }

            vkBeginCommandBuffer(pPrebuiltResources->cubeAndWireframe.commandBufferWireframe, &cmdBufferBeginInfo);

            if (enableGPA)
            {
                GPUPerfAPI.m_pGpaFuncTable->GPA_BeginCommandList(m_GPASessionId, gpaPassIndex, pPrebuiltResources->cubeAndWireframe.commandBufferWireframe, GPA_COMMAND_LIST_PRIMARY, &pPrebuiltResources->cubeAndWireframe.gpaCommandListIdWireframe);

                // COMMENT FOR DEMONSTRATION PURPOSES:
                // Tell GPA that a sample that has previously been started will be continued onto the GPACommandListId that was just begun.
                GPUPerfAPI.m_pGpaFuncTable->GPA_ContinueSampleOnCommandList(pPrebuiltResources->cubeAndWireframe.gpaSampleId, pPrebuiltResources->cubeAndWireframe.gpaCommandListIdWireframe);
            }

            VkRenderPassBeginInfo renderPassBeginInfoWireframe = {};
            renderPassBeginInfoWireframe.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
            renderPassBeginInfoWireframe.pNext = nullptr;
            renderPassBeginInfoWireframe.renderPass = m_vkRenderPassFinal;
            renderPassBeginInfoWireframe.framebuffer = framebuffer;
            renderPassBeginInfoWireframe.renderArea.offset = { 2 * static_cast<int32_t>(m_swapchainImageExtent.width) / 3, 0 };
            renderPassBeginInfoWireframe.renderArea.extent = m_swapchainImageExtent;
            renderPassBeginInfoWireframe.renderArea.extent.width /= 3u;
            renderPassBeginInfoWireframe.clearValueCount = 0;
            renderPassBeginInfoWireframe.pClearValues = nullptr;

            vkCmdBeginRenderPass(pPrebuiltResources->cubeAndWireframe.commandBufferWireframe, &renderPassBeginInfoWireframe, VK_SUBPASS_CONTENTS_INLINE);

            vkCmdSetViewport(pPrebuiltResources->cubeAndWireframe.commandBufferWireframe, 0, 1, &viewports[2]);
            vkCmdSetScissor(pPrebuiltResources->cubeAndWireframe.commandBufferWireframe, 0, 1, &scissorRects[2]);

            vkCmdBindPipeline(pPrebuiltResources->cubeAndWireframe.commandBufferWireframe, VK_PIPELINE_BIND_POINT_GRAPHICS, m_vkPipelineWireframe);

            // COMMENT FOR DEMONSTRATION PURPOSES:
            // Do not begin a GPA Sample here, because it is automatically continued by GPA_ContinueSampleOnCommandList() above.
            //if (enableGPA)
            //{
            //    GPUPerfAPI.m_pGpaFuncTable->GPA_BeginSample(pPrebuiltResources->cubeAndWireframe.gpaSampleId, pPrebuiltResources->cubeAndWireframe.gpaCommandListIdWireframe);
            //}

            vkCmdDraw(pPrebuiltResources->cubeAndWireframe.commandBufferWireframe, 36, 1, 0, 0);

            if (enableGPA)
            {
                GPUPerfAPI.m_pGpaFuncTable->GPA_EndSample(pPrebuiltResources->cubeAndWireframe.gpaCommandListIdWireframe);
            }

            vkCmdEndRenderPass(pPrebuiltResources->cubeAndWireframe.commandBufferWireframe);

            if (enableGPA)
            {
                GPUPerfAPI.m_pGpaFuncTable->GPA_EndCommandList(pPrebuiltResources->cubeAndWireframe.gpaCommandListIdWireframe);
            }

            VkResult resultEndCmdBufferWireframe = vkEndCommandBuffer(pPrebuiltResources->cubeAndWireframe.commandBufferWireframe);

            if (resultEndCmdBufferWireframe != VK_SUCCESS)
            {
                std::cout << "ERROR: Failed to end wireframe command buffer." << std::endl;
            }
        }
    }
};

/// A global instance of the Demo.
static AMDVulkanDemo gs_Demo;

#if defined(VK_USE_PLATFORM_WIN32_KHR)

/// Window message processing callback
LRESULT CALLBACK demoWindowMessageProcessorWin32(HWND hWindow, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
    switch (uMessage)
    {
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }

        case WM_PAINT:
        {
            // Only draw if the demo has been initialized successfully. This may not be the case
            // if there was an error during initiailization which would display a message box and
            // cause the window to paint. If this happens, skip drawing and let the default windowing
            // behavior occur.
            if (gs_Demo.Initialized())
            {
                gs_Demo.DrawScene();
                return 0;
            }
        }

        default:
            return DefWindowProc(hWindow, uMessage, wParam, lParam);
    }
}

/// Main entrypoint for Windows applications.
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(pCmdLine);

    MSG message;
    memset(&message, 0, sizeof(MSG));

    // Flags that should become command-line options.
    bool bUseGPA = true;
    bool bPrintDebugOutput = false;
    bool bPrintGPACounterInfo = false;

    gs_Demo.SetPrintGPACounterInfo(bPrintGPACounterInfo);
    gs_Demo.SetPrintDebugOutput(bPrintDebugOutput);

    // First load GPUPerfAPI if needed
    if (bUseGPA)
    {
        if (!gs_Demo.InitializeGPA())
        {
            return -1;
        }
    }

    // Create a window for the demo to render into before initializing Vulkan since the window
    // surface is needed as part of the vulkan initialization.
    HWND hWindow = gs_Demo.InitializeWindowWin32(hInstance, demoWindowMessageProcessorWin32, nCmdShow);

    if (hWindow == nullptr)
    {
        return -1;
    }

    if (gs_Demo.InitializeVulkan())
    {
        // Main message loop
        while (!gs_Demo.Exit())
        {
            PeekMessage(&message, NULL, 0, 0, PM_REMOVE);

            if (message.message == WM_QUIT)
            {
                gs_Demo.Exit(true);
            }
            else
            {
                /* Translate and dispatch to event queue */
                TranslateMessage(&message);
                DispatchMessage(&message);
            }

            RedrawWindow(hWindow, NULL, NULL, RDW_INTERNALPAINT);
        }
    }

    return (int)message.wParam;
}

#elif defined(VK_USE_PLATFORM_XCB_KHR)

/// Window message processing callback
void demoWindowMessageProcessorXcb(xcb_generic_event_t* pEvent)
{
    uint8_t event_code = pEvent->response_type & ~0x80;

    switch (event_code)
    {
        case XCB_CLIENT_MESSAGE:
        {
            const xcb_client_message_event_t* pClientMessage = (const xcb_client_message_event_t*)pEvent;

            if (pClientMessage->data.data32[0] == gs_Demo.m_xcbAtomWmDeleteWindow->atom)
            {
                gs_Demo.Exit(true);
            }
        }

        case XCB_KEY_RELEASE:
        {
            const xcb_key_release_event_t* pKeyRelease = (const xcb_key_release_event_t*)pEvent;

            //std::cout << "DEBUG: Key Release detail: '" << (uint32_t)pKeyRelease->detail << "'." << std::endl;

            if (pKeyRelease->detail == 0x9) // Escape key
            {
                gs_Demo.Exit(true);
            }
        }
    }
}

int main(const int argc, const char* argv[])
{
    UNREFERENCED_PARAMETER(argc);
    UNREFERENCED_PARAMETER(argv);

    // Flags that should be come command-line options.
    bool bUseGPA = true;
    bool bPrintDebugOutput = false;
    bool bPrintGPACounterInfo = false;

    gs_Demo.SetPrintGPACounterInfo(bPrintGPACounterInfo);
    gs_Demo.SetPrintDebugOutput(bPrintDebugOutput);

    // First load GPUPerfAPI if needed
    if (bUseGPA)
    {
        if (!gs_Demo.InitializeGPA())
        {
            return -1;
        }
    }

    // Create a window for the demo to render into before initializing Vulkan since the window
    // surface is needed as part of the vulkan initialization.
    xcb_connection_t* pConnection = gs_Demo.InitializeWindowXCB();

    if (pConnection == nullptr)
    {
        return -1;
    }

    if (gs_Demo.InitializeVulkan())
    {
        xcb_flush(pConnection);
        xcb_generic_event_t* event;

        // Main message loop
        while (!gs_Demo.Exit())
        {
            event = xcb_poll_for_event(pConnection);

            while (event)
            {
                demoWindowMessageProcessorXcb(event);
                free(event);
                event = xcb_poll_for_event(pConnection);
            }

            // Only draw if the demo has been initialized successfully. This may not be the case
            // if there was an error during initiailization which would display a message box and
            // cause the window to paint. If this happens, skip drawing and let the default windowing
            // behavior occur.
            if (gs_Demo.Initialized())
            {
                gs_Demo.DrawScene();
            }
        }
    }

    return 0;
}

#endif
