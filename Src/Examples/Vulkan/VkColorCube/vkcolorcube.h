//==============================================================================
// Copyright (c) 2018-2019 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Vulkan Color Cube Sample
//==============================================================================

#ifndef _VK_COLOR_CUBE_H_
#define _VK_COLOR_CUBE_H_

// platform-specific headers
#ifdef _WIN32
// Tell the linker that this is a windowed app, not a console app;
// defining this in code allows for flexibility with other operating systems.
#pragma comment(linker, "/subsystem:windows")
#define VK_USE_PLATFORM_WIN32_KHR
#endif  // _WIN32

#ifdef __linux__
#define VK_USE_PLATFORM_XCB_KHR
#endif  // __linux__

// Headers needed on all platforms
#include <algorithm>
#include <fstream>
#include <map>
#include <vector>
#include <vulkan/vulkan.h>
#include "GPAInterfaceLoader.h"
#include "GPAHelper.h"

#if defined(VK_USE_PLATFORM_XCB_KHR) || defined(VK_USE_PLATFORM_XLIB_KHR)
#include <X11/Xutil.h>
#include <xcb/xcb.h>
#include <dlfcn.h>
#include <unistd.h>
#endif

/// \brief Stores all the data needed for this demo.
/// Assists with available and enabled extensions, but not much other functionality. The reason for this
/// is so that the majority of Vulkan related functionality flows as a linear progression rather than being
/// split up into multiple smaller functions.
class AMDVulkanDemo
{
public:
    /// Constructor
    AMDVulkanDemo();

    /// Destructor
    ~AMDVulkanDemo();

    /// Indicates whether or not the app should exit.
    /// \return true if the app should exit; false otherwise;
    bool Exit() const;

    /// Sets whether or not the demo should exit at the next appropriate opportunity.
    /// \param bExit True to indicate that the demo should exit at the next appropriate opportunity;
    ///              False will clear the exit flag, but this may not prevent the demo from exiting if the exit process has already started.
    void Exit(bool bExit);

    /// Sets whether or not to print GPA Counter names & description on GPA initialization.
    /// \param bPrint True to print counter info; false to prevent it from printing.
    void SetPrintGPACounterInfo(bool bPrint);

    /// Sets whether or not to print debug output.
    /// \param bPrint True to print debug output; false to prevent debug output from being printed.
    void SetPrintDebugOutput(bool bPrint);

    /// Sets whether or not to exit after collecting counter values.
    /// \param bExitAfterProfile True to exit the application after counter values have been collected; false to continue running until the user closes the application.
    void SetExitAfterProfile(bool bExitAfterProfile);

    /// Sets whether or not to verify counter values.
    /// \param bVerifyCounters True to perform some basic validation of counter values -- application will return a non-zero exit code if counter verification fails
    void SetVerifyCounters(bool bVerifyCounters);

    /// Sets whether or not to include hardware counters in non-internal builds.
    /// \param bIncludeHwCounters True to include hardware counters in the set of enabled counters in non-internal builds
    void SetIncludeHwCounters(bool bIncludeHwCounters);

    /// Indicates that the Demo has been fully initialized.
    /// \return True if initialization has completed; false otherwise.
    bool Initialized() const;

#ifdef VK_USE_PLATFORM_WIN32_KHR
    /// Registers a new window class and creates a window from that class.
    /// \param demoWindowProcessor Callback function to process windowing messages.
    /// \return Handle to the created window, or nullptr on error;
    HWND CreateWindowWin32(WNDPROC demoWindowProcessor);

    /// Initialize a window on Win32 platforms.
    /// \param hInstance The application instance handle.
    /// \param windowMessageProcessor The function that will process window messages.
    /// \param nCmdShow Indicates how the window will be shown.
    /// \return A Handle to the created window, or nullptr if the instance was already set or the window was already created, or there was an error creating the window.
    HWND InitializeWindowWin32(HINSTANCE hInstance, WNDPROC windowMessageProcessor, int nCmdShow);

#elif defined(VK_USE_PLATFORM_XCB_KHR)

    /// Registers a new window class and creates a window from that class.
    /// \return Handle to the created window, or nullptr on error;
    xcb_connection_t* InitializeWindowXCB();

#endif  // VK_USE_PLATFORM_XCB_KHR

    /// Loads a shader from the specified filename and creates a vkShaderModule for it.
    /// \param filename The relative or absolute path to a filename of the SPIR-V shader to load.
    /// \return A valid VkShaderModule if the shader could be loaded, or VK_NULL_HANDLE on error.
    VkShaderModule LoadShader(const char* filename);

    /// Load & Initialize GPA
    /// \return True if GPA could be loaded and initialized; false on error.
    bool InitializeGPA();

    /// General initialization that just about every Vulkan application would need to do.
    /// \return false if an error occurs, otherwise true.
    bool InitializeVulkan();

    /// Draws the scene in a method that can be called on any platform.
    void DrawScene();

    /// General vulkan object destruction.
    void Destroy();

    /// Short name that will be used as the application name.
    const std::string m_cShortName = "AMD VkColorCube";

    /// Longer name that will be displayed in the window title bar.
    const std::wstring m_cLongName = L"The AMD Vulkan Color Cube Sample";

    /// Default window width.
    const uint32_t m_cDefaultWindowWidth = 900;

    /// Default window height.
    const uint32_t m_cDefaultWindowHeight = 300;

private:
    /// Caches an extension name that should have been returned by vkEnumerateInstanceExtensionProperties.
    /// \param pExtensionName A name to add to the list of supported instance extensions.
    void AddSupportedInstanceExtension(const char* pExtensionName);

    /// Checks to see if the supplied extension is in the supported instance extension list.
    /// \param pExtensionName The name of the extension to seek.
    /// \return True if the extension is supported; false otherwise.
    bool IsInstanceExtensionSupported(const char* pExtensionName);

    /// Caches an extension name that should have been returned by vkEnumerateDeviceExtensionProperties.
    /// \param pExtensionName A name to add to the list of supported device extensions.
    void AddSupportedDeviceExtension(const char* pExtensionName);

    /// Checks to see if the supplied extension is in the supported device extension list.
    /// \param pExtensionName The name of the extension to seek.
    /// \return True if the extension is supported; false otherwise.
    bool IsDeviceExtensionSupported(const char* pExtensionName);

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
    Display*          m_pDisplay;
    xcb_connection_t* m_pXcbConnection;
    xcb_screen_t*     m_pXcbScreen;
    xcb_window_t      m_xcbWindow;

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

        /// Frame buffers - one for each swapchain image.
        std::vector<VkFramebuffer> vkFramebuffers;
    } m_perSwapchainImageResources;

    /// Container for pre-built resources that are needed to render a single frame,
    /// but are also different for each frame. Namely, these command buffers are uniquely
    /// associated with different frame buffers
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

    /// The render pass that will be used first and will clear the screen.
    VkRenderPass m_vkRenderPassInitial;

    /// The render pass that is used for all mid-frame draws which leaves
    /// the render target in a COLOR_ATTACHMENT_OPTIMAL layout.
    VkRenderPass m_vkRenderPassMid;

    /// The render pass that is used for the final draws which puts the
    /// render target in a PRESENT_SRC layout. This could have also been
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

    /// Vertex shader module.
    VkShaderModule m_vertexShaderModule;

    /// Fragment shader module.
    VkShaderModule m_fragmentShaderModule;

    /// Fragment shader module for drawing wireframe.
    VkShaderModule m_fragmentShaderWireframeModule;

    /// Semaphore to indicate when a swapchain image has been acquired.
    VkSemaphore m_vkSemaphoreAcquiredSwapchainImage;

    /// Semaphore to indicate when the rendering has completed.
    VkSemaphore m_vkSemaphoreFinishedRendering;

    /// Tracks the existence (or enabled state) of the debug report callback.
    VkDebugReportCallbackEXT m_vkDebugReportCallback;

    /// GPA Context.
    GPA_ContextId m_GPAContextId;

    /// GPA session.
    GPA_SessionId m_GPASessionId;

    /// Number of required GPA passes based on the set of enabled counters.
    uint32_t m_requiredPassCount;

    /// Number of frames that have been rendered.
    uint32_t m_frameCount;

    /// Flag to indicate whether or not to print debug output.
    bool m_bPrintDebugOutput;

    /// Flag to indicate whether or not to print GPA counter names & descriptions.
    /// when GPA is initialized.
    bool m_bPrintGPACounterInfo;

    /// Flag to indicate whether or not to exit after counters are collected.
    bool m_bExitAfterProfile;

    /// Flag to indicate whether or not to verify some counter values.
    bool m_bVerifyCounters;

    /// Flag to indicate whether or not to include hardware counters in non-internal builds
    bool m_bIncludeHwCounters;

    /// Flag to indicate that the demo has been successfully initialized.
    bool m_bInitialized;

    /// Flag to indicate that the demo should exit.
    bool m_bExit;

    /// Stores the list of available instance extensions as exposed by the Vulkan implementation.
    std::map<const std::string, bool> m_supportedInstanceExtensions;

    /// Stores the list of available device extensions as exposed by the Vulkan implementation.
    std::map<const std::string, bool> m_supportedDeviceExtensions;

    /// Builds command buffers that will not be reset and rebuilt between frames.
    /// \param pPrebuiltResources Pointer to the set of resources that need to be built.
    /// \param framebuffer The framebuffer that is connected to specific swapchain images
    /// that should be rendered into by these command buffers.
    /// \param enableGPA Indicates whether GPA profiling should be enabled in these command buffers or not.
    /// \param gpaPassIndex If GPA is enabled for these command buffers, this indicates which profile pass is being built; ignored if enableGPA is false.
    void PreBuildCommandBuffers(PrebuiltPerFrameResources* pPrebuiltResources, VkFramebuffer framebuffer, bool enableGPA, uint32_t gpaPassIndex);

    /// GPA helper
    GPAHelper m_GpuPerfApiHelper;
};

/// Struct to hold values of command line arguments.
struct CommandLineArgs
{
    /// Flag indicating whether GPA should be used to collect performance counter values.
    bool m_bUseGPA = true;

    /// Flag indicating whether verbose debug output should be displayed.
    bool m_bPrintDebugOutput = false;

    /// Flag indicating whether available counter information should be displayed.
    bool m_bPrintGPACounterInfo = false;

    /// Flag indicating whether the application should automatically exit after collecting performance counters.
    bool m_bExitAfterProfile = false;

    /// Flag indicating whether the application should verify some counter values.
    bool m_bVerifyCounters = false;

    /// Flag indicating whether or not hardware counters should be enabled in non-internal builds
    bool m_bIncludeHwCounters = false;
};

#endif  // _VK_COLOR_CUBE_H_
