//==============================================================================
// Copyright (c) 2018-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Vulkan Color Cube Sample.
//==============================================================================

#ifndef GPU_PERF_API_EXAMPLES_VULKAN_VK_COLOR_CUBE_VK_COLOR_CUBE_H_
#define GPU_PERF_API_EXAMPLES_VULKAN_VK_COLOR_CUBE_VK_COLOR_CUBE_H_

#ifdef ANDROID
#define VK_USE_PLATFORM_ANDROID_KHR
#include <android_native_app_glue.h>
#else

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
#endif

#include <algorithm>
#include <fstream>
#include <map>
#include <vector>

#include <vulkan/vulkan.h>

#if defined(VK_USE_PLATFORM_XCB_KHR) || defined(VK_USE_PLATFORM_XLIB_KHR)
#include <X11/Xutil.h>
#include <xcb/xcb.h>
#include <dlfcn.h>
#include <unistd.h>
#endif

#include "gpu_performance_api/gpu_perf_api_interface_loader.h"

#include "examples/vulkan/vk_color_cube/gpa_helper.h"

#include "examples/common/cmdline_parser.h"
#include "examples/common/gpa_sample_app.h"

/// @brief Stores all the data needed for this demo.
///
/// Assists with available and enabled extensions, but not much other functionality. The reason for this
/// is so that the majority of Vulkan related functionality flows as a linear progression rather than being
/// split up into multiple smaller functions.
class AMDVulkanDemo : public gpa_example::GpaSampleApp
{
public:
    /// @brief Constructor.
    ///
    /// @param app_name The name of the application.
    /// @param cmdline_parser The command line parser to be used by this application.
    AMDVulkanDemo(const std::string app_name, gpa_example::CmdlineParser& cmdline_parser);

    /// @brief Destructor.
    ~AMDVulkanDemo() override;

    /// @brief Indicates whether or not the app should exit.
    ///
    /// @return True if the app should exit; false otherwise;
    bool Exit() const;

    /// @brief Sets whether or not the demo should exit at the next appropriate opportunity.
    ///
    /// @param [in] exit True to indicate that the demo should exit at the next appropriate opportunity;
    ///             False will clear the exit flag, but this may not prevent the demo from exiting if the exit process has already started.
    void Exit(bool exit);

    /// @brief Indicates that the Demo has been fully initialized.
    ///
    /// @return True if initialization has completed; false otherwise.
    bool Initialized() const;

#ifdef VK_USE_PLATFORM_WIN32_KHR
    /// @brief Registers a new window class and creates a window from that class.
    ///
    /// @param [in] demo_window_procedure Callback function to process windowing messages.
    void CreateWindowWin32(WNDPROC demo_window_procedure);

    /// @brief Initialize a window on Win32 platforms.
    ///
    /// @param [in] instance_handle The application instance handle.
    /// @param [in] demo_window_message_procedure The function that will process window messages.
    /// @param [in] cmd_show Indicates how the window will be shown.
    void InitializeWindowWin32(HINSTANCE instance_handle, WNDPROC demo_window_message_procedure, int cmd_show);

    /// @brief Retrieve the Win32 window instance used by this application.
    ///
    /// @return A pointer to the Win32 window, or nullptr if the window has not yet been successfully created.
    HWND GetWindowWin32() const;

#elif defined(VK_USE_PLATFORM_XCB_KHR)

    /// @brief Registers a new window class and creates a window from that class.
    ///
    /// @return Handle to the created window, or nullptr on error;
    xcb_connection_t* InitializeWindowXcb();

#endif  // VK_USE_PLATFORM_XCB_KHR

    /// @brief Loads a shader from the specified file_name and creates a VkShaderModule for it.
    ///
    /// @param [in] file_name The relative or absolute path to a file_name of the SPIR-V shader to load.
    ///
    /// @return A valid VkShaderModule if the shader could be loaded, or VK_NULL_HANDLE on error.
    VkShaderModule LoadShader(const char* file_name);

    /// @brief Load & Initialize GPA
    ///
    /// @return True if GPA could be loaded and initialized; false on error.
    bool InitializeGpa();

    /// @brief General initialization that just about every Vulkan application would need to do.
    ///
    /// @return False if an error occurs, otherwise true.
    bool InitializeVulkan();

    /// @brief Draws the scene in a method that can be called on any platform.
    void DrawScene();

    /// @brief General vulkan object destruction.
    void Destroy();

    /// @brief Specifies whether or not GPA will be used by this application to profile counters.
    ///
    /// @return true if specified on the command line, otherwise false.
    bool NoGpa();

    const std::string  kShortName          = "AMD VkColorCube";                    ///< Short name that will be used as the application name.
    const std::wstring kLongName           = L"The AMD Vulkan Color Cube Sample";  ///< Longer name displayed in the title bar.
    const uint32_t     kDefaultWindowWidth = 900;                                  ///< Default window width.

    /// Default window height.
    const uint32_t kDefaultWindowHeight = 300;

    /// Note that GPA sample IDs are client defined. However, the Vulkan GPA
    /// extension assigns an ID to each sample (they are not client defined).
    /// The GPA library manages the mapping between them. These are the former.
    static constexpr GpaUInt32 kGpaSampleIdCube = 0;
    static constexpr GpaUInt32 kGpaSampleIdWireframe = 1;
    static constexpr GpaUInt32 kGpaSampleIdCubeAndWireframe = 2;

#ifdef ANDROID
    inline void SetWindow(ANativeWindow* native_window)
    {
        native_window_ = native_window;
    }

    inline void SetNativeActivity(ANativeActivity* native_activity)
    {
        native_activity_ = native_activity;
    }
#endif

private:
    /// @brief Caches an extension name that should have been returned by vkEnumerateInstanceExtensionProperties.
    ///
    /// @param [in] extension_name A name to add to the list of supported instance extensions.
    void AddSupportedInstanceExtension(const char* extension_name);

    /// @brief Checks to see if the supplied extension is in the supported instance extension list.
    ///
    /// @param [in] extension_name The name of the extension to seek.
    ///
    /// @return True if the extension is supported; false otherwise.
    bool IsInstanceExtensionSupported(const char* extension_name);

    /// @brief Caches an extension name that should have been returned by vkEnumerateDeviceExtensionProperties.
    ///
    /// @param [in] extension_name A name to add to the list of supported device extensions.
    void AddSupportedDeviceExtension(const char* extension_name);

    /// @brief Checks to see if the supplied extension is in the supported device extension list.
    ///
    /// @param [in] extension_name The name of the extension to seek.
    ///
    /// @return True if the extension is supported; false otherwise.
    bool IsDeviceExtensionSupported(const char* extension_name);

    std::vector<const char*> required_instance_extensions_;  ///< List of instance extension names that are required by this demo.
    std::vector<const char*> required_device_extensions_;    ///< List of device extension names that are required by this demo.
    std::vector<const char*> optional_device_extensions_;    ///< List of device extension names that are optional for this demo.

#if defined(VK_USE_PLATFORM_WIN32_KHR)
    HINSTANCE hInstance_;  ///< Application windowing instance.
    HWND      hWindow_;    ///< Window handle.
#elif defined(VK_USE_PLATFORM_XCB_KHR)
    Display*          display_;
    xcb_connection_t* xcb_conntection_;
    xcb_screen_t*     xcb_screen_;
    xcb_window_t      xcb_window_;

public:
    xcb_intern_atom_reply_t* xcb_atom_delete_window_;

private:
#endif

    VkInstance                       vk_instance_;                        ///< The instance of the Vulkan API.
    const uint32_t                   default_physical_device_index_ = 0;  ///< The default index of the physical device (ie: GPU) to use when running this demo.
    VkPhysicalDevice                 default_physical_device_;            ///< The selected physical device that will execute this demo.
    VkPhysicalDeviceProperties       physical_device_properties_;         ///< Properties of the selected physical device.
    VkPhysicalDeviceFeatures         phsyical_device_features_;           ///< Available features of the selected physical device.
    VkPhysicalDeviceMemoryProperties physical_device_memory_properties_;  ///< Properties of the selected physical device.
    VkDevice                         vk_device_;                          ///< The logical device that will be used to render.
    VkQueue                          vk_queue_;                           ///< The queue on which rendering commands will be scheduled.
    uint32_t                         queue_index_;                        ///< The index within the queue family from which the vkQueue was obtained.
    VkSurfaceKHR                     vk_surface_;                         ///< The display surface that the demo will render to.
    VkSurfaceFormatKHR               vk_surface_format_;                  ///< The selected format of the presentation surface.
    uint32_t                         queue_family_index_graphics_;        ///< Index of the queue family that supports graphics.
    uint32_t                         queue_family_index_present_;         ///< Index of the queue family that supports present
    VkPresentModeKHR                 vk_present_mode_;                    ///< The mode Vulkan WSI will use to present the swapchain images.
    VkSurfaceCapabilitiesKHR         vk_surface_capabilities_;            ///< Capabilities of the display surface.
    VkSwapchainKHR                   vk_swap_chain_;                      ///< The swapchain that will be used to present.
    VkExtent2D                       swap_chain_image_extent_;            ///< Swapchain image Extents (resolution)

    /// @brief These objects are unique to each swapchain image.
    ///
    /// Use the same index for each of these vectors to access corresponding objects.
    struct PerSwapchainImageResources
    {
        std::vector<VkImage>       swap_chain_images;       ///< Handles to the swapchain images.
        std::vector<VkImageView>   swap_chain_image_views;  ///< Views into the swapchain images.
        std::vector<VkFramebuffer> vk_frame_buffers;        ///< Frame buffers - one for each swapchain image.
    } per_swap_chain_image_resources_;

    /// @brief Container for pre-built resources that are needed to render a single frame,
    /// but are also different for each frame. Namely, these command buffers are uniquely
    /// associated with different frame buffers.
    struct PrebuiltPerFrameResources
    {
        /// @brief Container for objects related to drawing the cube.
        struct Cube
        {
            /// The command buffer that will draw the cube.
            VkCommandBuffer command_buffer;

            /// The GPA CommandList that will include the sample that draws the cube.
            GpaCommandListId gpa_command_list_id;

            /// Sample Id that the application (not GPA) assigns to the cube.
            /// The cube will have this same sample_id in all passes.
            const GpaUInt32 gpa_sample_id = kGpaSampleIdCube;
        } cube_;

        /// @brief Container for objects related to drawing the wireframe.
        struct Wireframe
        {
            /// The command buffer that will draw the wireframe.
            VkCommandBuffer command_buffer;

            /// The GPA CommandList that will include the sample that draws the cube.
            GpaCommandListId gpa_command_list_id;

            /// Sample Id that the application (not GPA) assigns to the wireframe.
            /// The wireframe will have this same sample_id in all passes.
            const GpaUInt32 gpa_sample_id = kGpaSampleIdWireframe;
        } wire_frame_;

        /// @brief Container for objects related to drawing the cube and wireframe.
        ///
        /// Draws them in two different command buffers, with a single GPA Sample that starts in the first
        /// command buffer and continues into the second.
        struct CubeAndWireframe
        {
            /// The command buffer that will draw the cube.
            VkCommandBuffer command_buffer_cube;

            /// The command buffer that will draw the wireframe.
            VkCommandBuffer command_buffer_wire_frame;

            /// The GPA CommandListId that will draw the cube and start the GPA Sample.
            GpaCommandListId gpa_command_list_id_cube;

            /// The GPA CommandList that will draws the wireframe and will end the GPA Sample.
            GpaCommandListId gpa_command_list_id_wire_frame;

            /// Sample Id that the application (not GPA) assigns to the cube wireframe.
            /// The combined cube + wireframe sample will have this same sample_id in all passes.
            const GpaUInt32 gpa_sample_id = kGpaSampleIdCubeAndWireframe;
        } cube_and_wire_frame_;
    };

    /// Vector of pre-built per-frame resources.
    /// There will be one entry per swapchain image in this vector,
    /// as each one is pre-built to output to a specific swapchain image.
    /// When building these resources, GPA calls SHOULD NOT be inserted.
    std::vector<PrebuiltPerFrameResources> prebuilt_frame_resources_;

    /// Vector of pre-built per-frame resources.
    /// There will be one entry per swapchain image in this vector,
    /// as each one is pre-built to output to a specific swapchain image.
    /// When building these resources, GPA calls SHOULD be inserted.
    std::vector<PrebuiltPerFrameResources> prebuilt_per_frame_resources_with_gpa_;

    /// The render pass that will be used first and will clear the screen.
    VkRenderPass vk_render_pass_initial_;

    /// The render pass that is used for all mid-frame draws which leaves
    /// the render target in a COLOR_ATTACHMENT_OPTIMAL layout.
    VkRenderPass vk_render_pass_mid_;

    /// The render pass that is used for the final draws which puts the
    /// render target in a PRESENT_SRC layout. This could have also been
    /// done by using a pipeline barrier.
    VkRenderPass vk_render_pass_final_;

    /// The pipeline layout.
    VkPipelineLayout vk_pipeline_layout_;

    /// The graphics pipeline object.
    VkPipeline vk_pipeline_;

    /// The graphics pipeline object to draw wireframes.
    VkPipeline vk_pipeline_wire_frame_;

    /// The command pool which will contain the necessary command buffers.
    VkCommandPool vk_command_pool_;

    /// Vertex shader module.
    VkShaderModule vertex_shader_module_;

    /// Fragment shader module.
    VkShaderModule fragment_shader_module_;

    /// Fragment shader module for drawing wireframe.
    VkShaderModule fragment_shader_wire_frame_module_;

    /// Semaphore to indicate when a swapchain image has been acquired.
    VkSemaphore vk_semaphore_acquired_swapchain_image_;

    /// Semaphore to indicate when the rendering has completed.
    VkSemaphore vk_sempahore_fineshed_rendering_;

    /// Tracks the existence (or enabled state) of the debug report callback.
    VkDebugReportCallbackEXT vk_debug_report_callback_;

    /// GPA Context.
    GpaContextId gpa_context_id_;

    /// GPA session.
    GpaSessionId gpa_session_id_;

    /// Number of required GPA passes based on the set of enabled counters.
    uint32_t required_pass_count_;

    /// Number of frames that have been rendered.
    uint32_t num_frames_rendered_;

    /// Flag to indicate whether or not to print debug output.
    bool print_debug_output_;

    /// Flag to indicate whether or not to print GPA counter names & descriptions when GPA is initialized.
    bool print_gpa_counter_info_;

    /// Flag to indicate whether or not to exit after counters are collected.
    bool exit_after_profile_;

    /// Flag to indicate whether or not to include hardware counters in non-internal builds
    bool include_hw_counters_;

    /// Flag to indicate that the demo has been successfully initialized.
    bool initialized_;

    /// Counter file name.
    std::string counter_file_name_;

    /// Flag to indicate that the demo should exit.
    bool exit_;

    /// Flag which specifies whether or not GPA will be used by this application to profile counters.
    bool nogpa_;

    /// Stores the list of available instance extensions as exposed by the Vulkan implementation.
    std::map<const std::string, bool> supported_instance_extensions_;

    /// Stores the list of available device extensions as exposed by the Vulkan implementation.
    std::map<const std::string, bool> supported_device_extensions_;

    /// @brief Builds command buffers that will not be reset and rebuilt between frames.
    ///
    /// @param [out] prebuilt_resources Pointer to the set of resources that need to be built.
    /// @param [in] frame_buffer The frame_buffer that is connected to specific swapchain images that should be rendered into by these command buffers.
    /// @param [in] enable_gpa Indicates whether GPA profiling should be enabled in these command buffers or not.
    /// @param [in] gpa_pass_index If GPA is enabled for these command buffers, this indicates which profile pass is being built; ignored if enable_gpa is false.
    void PreBuildCommandBuffers(PrebuiltPerFrameResources* prebuilt_resources, VkFramebuffer frame_buffer, bool enable_gpa, uint32_t gpa_pass_index);

    /// @brief Log the textual representation of a failure status code
    ///
    /// @param [in] status the failure code
    /// @param [in] msg optional additional context. Should not contain trailing punctuation.
    void LogStatus(GpaStatus status, const char* msg=nullptr);

    /// GPA helper.
    GpaHelper gpu_perf_api_helper_;

#ifdef ANDROID
    ANativeWindow*   native_window_;    ///< Android Native window.
    ANativeActivity* native_activity_;  ///< Android Native activity.
#endif
    static AMDVulkanDemo* amd_vulkan_demo_;  ///< Static instance of the app.
};

#endif  // GPU_PERF_API_EXAMPLES_VULKAN_VK_COLOR_CUBE_VK_COLOR_CUBE_H_
