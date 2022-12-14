//==============================================================================
// Copyright (c) 2018-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Cube Sample header.
//==============================================================================

#ifndef GPU_PERF_API_EXAMPLES_DX12_DX12_COLOR_CUBE_CUBE_SAMPLE_
#define GPU_PERF_API_EXAMPLES_DX12_DX12_COLOR_CUBE_CUBE_SAMPLE_

#include <atomic>
#include <fstream>
#include <functional>
#include <sstream>
#include <stack>
#include <vector>

#ifdef _DEBUG
#include <dxgidebug.h>
#endif

#include <dxgi1_4.h>
#include <d3d12.h>

#include "gpu_performance_api/gpu_perf_api_interface_loader.h"

#include "examples/dx12/sample.h"

/// @brief Class for cube sample, demonstraing usage of GPA by drawing a cube.
class CubeSample
{
public:
    /// @brief Get the static instance of the cube sample.
    ///
    /// @return Static instance of the cube sample.
    static CubeSample* Instance();

    /// @brief Initializes the cube sample.
    ///
    /// @param app Pointer to the GPA sample application contesxt.
    /// @return true if initialization succeeds, false otherwise.
    void Init(gpa_example::Dx12SampleApp* app);

    /// @brief Draw the cube sample.
    void Draw();

    /// @brief Release the cube sample resources.
    void Destroy();

    /// @brief Toggles the profiling.
    void ToggleProfiling();

    /// @brief Toggles the wireframe.
    void ToggleWireFrame();

private:
    /// @brief struct for vertex data.
    struct VertexData
    {
        float position[4];  ///< Position.
        float color[4];     ///< Color.
    };

    /// @brief Pointer to the GPA sample application context.
    gpa_example::Dx12SampleApp* app_;

    /// @brief Constructor.
    CubeSample();

    /// @brief Initializes the common resource.
    ///
    /// @return True upon successful execution.
    bool InitializeCommonResource();

    /// @brief Initializes the view port resources.
    ///
    /// @param app Pointer the the GPA sample application context.
    /// @return True upon successful execution.
    bool InitializeViewPortResource(gpa_example::Dx12SampleApp* app);

    /// @brief Uploads the cube data to the GPU.
    bool UploadCubeData();

    /// @brief Wait for the GPU to finish executing.
    void WaitForGpuToFinish();

    /// @brief Adds the IUnknown to the list and adds a name for it.
    void AddIUnknown(IUnknown* unknown, const std::string& name);

    using IUnknownNamePair    = std::pair<std::wstring, IUnknown*>;       ///< Type alias for IUnknown name pair.
    using IUnknownNameCache   = std::stack<IUnknownNamePair>;             ///< Type alias for stack of IUnknownNamePairs.
    using GraphicsCommandList = std::vector<ID3D12GraphicsCommandList*>;  ///< Type alias for the list of graphics command. list.

    static constexpr unsigned int kFrameCount    = 2;  ///< Frame count.
    static constexpr unsigned int kViewportCount = 4;  ///< Number of viewports.
    static CubeSample*            cube_sample;         ///< Static instance of the cube sample.

    /// @brief Adds the command list to a list for housekeeping.
    ///
    /// @param [in] graphics_command_list Graphics command list.
    void AddCommandList(ID3D12GraphicsCommandList* graphics_command_list);

    /// Resets the pass resources.
    void ResetGpaPassInfo();

#pragma region CommonResource
    ID3D12Device*        d3d12_device_;          ///< D3D12 Device.
    ID3D12RootSignature* d3d12_root_signature_;  ///< D3D12 root signature.
#ifdef _DEBUG
    ID3D12Debug* d3d12_debug_interface;  ///< D3D12 debug interface.
    IDXGIDebug*  dxgi_debug_;            ///< DXGI debug interface.
#endif
    IDXGIFactory2*           dxgi_factory_2_;             ///< DXGI Factory 2.
    ID3D12PipelineState*     fill_draw_pipeline_;         ///< Solid draw pipeline state.
    ID3D12PipelineState*     wire_frame_pipeline_;        ///< Wireframe draw pipeline state.
    ID3D12Resource*          vertex_buffer_;              ///< D3D12 vertex buffer.
    D3D12_VERTEX_BUFFER_VIEW vertex_buffer_view_;         ///< Vertex buffer view.
    ID3D12Resource*          index_buffer_;               ///< D3D12 index buffer.
    D3D12_INDEX_BUFFER_VIEW  index_buffer_view_;          ///< Index buffer view.
    D3D12_RECT               scissor_rect_;               ///< Scissor rectangle.
    ID3D12Resource*          rtv_resource_[kFrameCount];  ///< D3D12 render target view resource - for dx12 allowed swap effect, we need minimum of two.
    HANDLE                   fence_event_;                ///< Fence event.
    ID3D12Fence*             d3d12_fence_;                ///< Fence.
    unsigned int             fence_value_;                ///< Fence value.
    IDXGISwapChain3*         dxgi_swap_chain_3_;          ///< Swap chain.
    unsigned int             current_back_buffer_index_;  ///< Current back buffer index of the swap chain.
    ID3D12PipelineState*     current_pipeline_state_;     ///< D3D12 current pipeline state.
    ID3D12DescriptorHeap*    d3d12_descriptor_heap_;      ///< D3D12 Descriptor heap.
    UINT                     rtv_view_desc_size;          ///< RTV Descriptor heap increment size.
    ID3D12CommandQueue*      d3d12_command_queue_;        ///< D3D12 command queue.
    GraphicsCommandList      graphics_command_queue_;     ///< D3D12 Graphics Command list vector.
    bool                     pipeline_state_changed_;     ///< Flag indicating if the pipeline state has changed.

#pragma endregion

#pragma region Viewports
    /// @brief Viewport class.
    ///
    /// Will be inherited by demo viewports.
    class Viewport
    {
    public:
        static constexpr unsigned int kUndefinedSampleId = 0xFFFF;  ///< Unassigned sample id.

        D3D12_VIEWPORT             viewport_;                             ///< Viewport.
        ID3D12GraphicsCommandList* d3d_command_list_;                     ///< D3D12 command list.
        ID3D12CommandAllocator*    d3d12_direct_command_list_allocator_;  ///< D3D12 Command Allocator.
        bool                       viewport_initialized_;                 ///< Flag indicating viewport size is initialized.
        D3D12_RECT                 viewport_rect_;                        ///< Viewport size rect.
        GpaCommandListId           gpa_command_list_;                     ///< GPA command list id.
        unsigned int               sample_id_;                            ///< Sample id.

        /// @brief Constructor.
        Viewport();

        /// @brief Initialize the view port.
        ///
        /// @param app Pointer to the GPA sample application context.
        /// @return True upon successful operation.
        virtual bool Init(gpa_example::Dx12SampleApp* app) = 0;

        /// @brief Draws the view port.
        virtual void Draw() = 0;

        /// @brief Resets for the next pass.
        virtual void ResetForNextPass() = 0;

        /// @brief Iterates over the viewport sample(s).
        virtual void IterateSamples(std::function<void(const unsigned int& sample_index)> func) const = 0;

        /// @brief Destructor.
        virtual ~Viewport() = default;

    protected:
        gpa_example::Dx12SampleApp* app_;
    };

#pragma region TopLeftViewport
    /// @brief TopLeftViewport class.
    ///
    /// Demonstrates GPA with single command list.
    class TopLeftViewport : Viewport
    {
    public:
        const float kClearColor[4] = {0.1f, 0.0f, 0.0f, 0.1f};  ///< Light Red.

        /// @brief Constructor.
        TopLeftViewport();

        /// @copydoc Viewport::Init()
        bool Init(gpa_example::Dx12SampleApp* app) override;

        /// @copydoc Viewport::Draw()
        void Draw() override;

        /// @copydoc Viewport::ResetForNextPass()
        void ResetForNextPass() override;

        /// @copydoc Viewport::IterateSamples()
        void IterateSamples(std::function<void(const unsigned int& sample_index)> func) const override;
    };
#pragma endregion

#pragma region TopRightViewport
    /// @brief TopRightViewport class.
    ///
    /// Demonstrates GPA with bundles.
    class TopRightViewport : Viewport
    {
    public:
        const float kClearColor[4] = {0.0f, 0.1f, 0.0f, 0.1f};  ///< Light Green.

        /// @brief Constructor.
        TopRightViewport();

        /// @copydoc Viewport::Init()
        bool Init(gpa_example::Dx12SampleApp* app) override;

        /// @copydoc Viewport::Draw()
        void Draw() override;

        /// @copydoc Viewport::ResetForNextPass()
        void ResetForNextPass() override;

        /// @copydoc Viewport::IterateSamples()
        void IterateSamples(std::function<void(const unsigned int& sample_index)> func) const override;

    private:
        ID3D12CommandAllocator*    bundle_command_allocator_;     ///< D3D12 Command allocator.
        ID3D12GraphicsCommandList* bundle_command_list_;          ///< D3D12 bundle command list.
        GpaCommandListId           gpa_command_list_for_bundle_;  ///< GPA command list id for the bundle.
        unsigned int               bundle_sample_id_;             ///< Sample id on the bundle.
    };
#pragma endregion

#pragma region BottomLeftViewport
    /// @brief BottomLeftViewport class.
    ///
    /// Demonstrates GPA usage across command lists.
    class BottomLeftViewport : Viewport
    {
    public:
        const float kClearColor[4] = {0.0f, 0.0f, 0.1f, 0.1f};  ///< Light Blue.

        /// @brief Constructor.
        BottomLeftViewport();

        /// @copydoc Viewport::Init()
        bool Init(gpa_example::Dx12SampleApp* app) override;

        /// @copydoc Viewport::Draw()
        void Draw() override;

        /// @copydoc Viewport::ResetForNextPass()
        void ResetForNextPass() override;

        /// @copydoc Viewport::IterateSamples()
        void IterateSamples(std::function<void(const unsigned int& sample_index)> func) const override;

    private:
        ID3D12CommandAllocator*    second_command_list_allocator_;             ///< D3D12 Command Allocator.
        ID3D12GraphicsCommandList* second_command_list_;                       ///< D3D12 Command list.
        GpaCommandListId           gpa_command_list_for_second_command_list_;  ///< GPA command list id of the second direct command list.
    };
#pragma endregion

#pragma region BottomRightViewport
    /// @brief BottomRightViewport class.
    ///
    /// Demonstrates GPA usage across command lists and bundles.
    class BottomRightViewport : Viewport
    {
    public:
        const float kClearColor[4] = {0.1f, 0.1f, 0.1f, 0.1f};  ///< Gray.

        /// Constructor.
        BottomRightViewport();

        /// @copydoc Viewport::Init()
        bool Init(gpa_example::Dx12SampleApp* app) override;

        /// @copydoc Viewport::Draw()
        void Draw() override;

        /// @copydoc Viewport::ResetForNextPass()
        void ResetForNextPass() override;

        /// @copydoc Viewport::IterateSamples()
        void IterateSamples(std::function<void(const unsigned int& sample_index)> func) const override;

    private:
        ID3D12CommandAllocator*    second_command_list_allocator_;             ///< D3D12 Command allocator.
        ID3D12CommandAllocator*    bundle_command_list_allocator_;             ///< D3D12 command allocator.
        ID3D12GraphicsCommandList* bundle_;                                    ///< D3D12 bundle command list.
        GpaCommandListId           gpa_command_list_for_bundle_;               ///< GPA command list id for the bundle.
        unsigned int               bundle_sample_id_;                          ///< Sample id for the bundle.
        unsigned int               bundle_sample_id_on_primary_command_list_;  ///< Sample id of the copied bundle sample.
        ID3D12GraphicsCommandList* second_command_list_;                       ///< D3D12 second command list.
        GpaCommandListId           gpa_command_list_for_second_command_list_;  ///< GPA command list id for the second direct command list.
    };
#pragma endregion

#pragma endregion

#pragma region ViewportResource
    TopLeftViewport           top_left_viewport_;          ///< Top left view port.
    TopRightViewport          top_right_viewport_;         ///< Top right view port.
    BottomLeftViewport        bottom_left_viewport_;       ///< Bottom left view port.
    BottomRightViewport       bottom_right_viewport_;      ///< Bottom right view port.
    std::atomic<bool>         wire_frame_;                 ///< Flag indicating wireframe mode is enabled.
    IUnknownNameCache         app_created_unknown_cache_;  ///< List of all the created unknowns.
    std::atomic<bool>         profiling_enable_;           ///< Flag indicating profiling is enabled or not.
    std::vector<unsigned int> profiled_frame_;             ///< List of frame profiled using GPA.
    unsigned int              frame_counter_;              ///< Frame counter.
    std::stringstream         content_;                    ///< Content stream.
    std::stringstream         header_;                     ///< Header stream.
    bool                      is_header_written_;          ///< Flag indicating header is written or not.

    GpaFunctionTable* gpa_function_table_;  ///< GPA function table.
    GpaContextId      gpa_context_id_;      ///< GPA context id.
    GpaSessionId      gpa_session_id_;      ///< GPA session id.
    GpaUInt32         device_id_;           ///< Device Id.
    GpaUInt32         revision_id_;         ///< Revision Id.
    std::string       device_name_;         ///< Device Name.
    GpaHwGeneration   device_generation_;   ///< Device Generation.

    unsigned int num_passes_required_;       ///< Number of pass required for the enabled set of counters.
    int          current_pass_;              ///< Current pass.
    int          sample_counter_;            ///< Sample counter.
    std::string  counter_data_name_;         ///< Name of the counter data file.
    std::string  gpa_log_file_name_;         ///< Name of the GPA log file.
    std::fstream gpa_log_file_stream_;       ///< GPA log file stream.
    std::fstream counter_data_file_stream_;  ///< Counter data file stream.
    std::string  executable_path_;           ///< Path of the sample executable.
#pragma endregion

public:
#pragma region GPA_Wrappers
    /// @brief Initializes GPA and open its context.
    ///
    /// @return True upon successful operation.
    bool GpaInitializeAndOpenContext();

    /// @brief Releases the GPA and closes its context.
    ///
    /// @return True upon successful operation.
    bool GpaReleaseContextAndDestroy();

    /// @brief Enables GPA counters.
    ///
    /// @return True upon successful operation.
    bool GpaEnableCounters();

    /// @brief Creates the GPA profiling session.
    ///
    /// @return True upon successful operation.
    bool GpaCreateProfilingSession();

    /// @brief Deletes the GPA profiling session.
    ///
    /// @return True upon successful operation.
    bool GpaDeleteProfilingSession();

    /// @brief Begins the GPA profiling session.
    ///
    /// @return True upon successful operation.
    bool GpaBeginProfilingSession();

    /// @brief Ends the GPA profiling session.
    ///
    /// @return True upon successful operation.
    bool GpaEndProfilingSession() const;

    /// @brief Begins workload for the GPA session pass.
    ///
    /// @return True upon successful operation.
    bool GpaBeginPass();

    /// @brief Ends the GPA session pass.
    ///
    /// @return True upon successful operation.
    bool GpaEndPass();

    /// @brief Resets the information needed for the next pass.
    ///
    /// @return True upon successful operation.
    bool GpaNextPassNeeded() const;

    /// @brief Begins the command list for sampling.
    ///
    /// @param [in] graphics_command_list Graphics command list.
    /// @param [in,out] gpa_command_list_id GPA command list upon successful execution otherwise nullptr.
    ///
    /// @return True upon successful execution otherwise false.
    bool GpaBeginCommandListForSampling(ID3D12GraphicsCommandList* graphics_command_list, GpaCommandListId& gpa_command_list_id) const;

    /// @brief Ends the command list for sampling.
    ///
    /// @param [in] gpa_command_list_id GPA command list.
    ///
    /// @return True upon successful operation.
    bool GpaEndCommandListForSampling(GpaCommandListId& gpa_command_list_id) const;

    /// @brief Begins GPA sample.
    ///
    /// @param [in] gpa_command_list_id GPA command list.
    /// @param [in] sample_id Sample id.
    ///
    /// @return True upon successful operation.
    bool GpaBeginSample(GpaCommandListId gpa_command_list_id, const unsigned int& sample_id) const;

    /// @brief Ends a GPA sample.
    ///
    /// @param [in] gpa_command_list_id GPA command list.
    ///
    /// @return True upon successful operation.
    bool GpaEndSample(GpaCommandListId gpa_command_list_id) const;

    /// @brief Copies a GPA secondary command list samples on primary command list.
    //
    /// @param [in] secondary_gpa_command_list Secondary gpa command list.
    /// @param [in] primary_gpa_command_list Primary command list.
    /// @param [in] sample_id_list List of sample ids.
    ///
    /// @return True upon successful operation.
    bool GpaCopyBundleSample(GpaCommandListId       secondary_gpa_command_list,
                             GpaCommandListId       primary_gpa_command_list,
                             std::vector<GpaUInt32> sample_id_list) const;

    /// @brief Continues the sample on another command list.
    ///
    /// @param [in] src_sample_id Source sample id.
    /// @param [in] gpa_command_list_id GPA command list id.
    ///
    /// @return True upon successful execution otherwise false.
    bool GpaContinueSample(unsigned int src_sample_id, GpaCommandListId gpa_command_list_id) const;

    /// @brief Enum to define type of counter validation to perform.
    typedef enum
    {
        kCompareTypeEqual,                 ///< Counter value must be equal to a specified value.
        kCompareTypeGreaterThan,           ///< Counter value must be greater than a specified value.
        kCompareTypeGreaterThanOrEqualTo,  ///< Counter value must be greater than or equal to a specified value.
        kCompareTypeLessThan,              ///< Counter value must be less than a specified value.
        kCompareTypeLessThanOrEqualTo,     ///< Counter value must be less than or equal to a specified value.
        kCompareTypeEpsilon,               ///< Counter value must be within range of the specified value +/- the epsilon value, inclusive.
        kCompareTypeRangeInclusive,        ///< Counter value must be within the range of the specified values, inclusive.
    } CompareType;

    /// @brief Compare retrieved counter value to an expected value.
    ///
    /// @param [in] profile_set The index of the profile set being validated.
    /// @param [in] sample_index The sample index of the counter being compared.
    /// @param [in] counter_name The name of the counter being compared.
    /// @param [in] counter_value The retrieved counter value.
    /// @param [in] compare_type The type of compare to perform.
    /// @param [in] compare_value The expected counter value (subject to the compare type).
    /// @param [in] compare_value2 A secondary value that may be used depending on the CompareType that is supplied.
    ///
    /// @return True if the counter value compares successfully, false otherwise.
    bool GpaCounterValueCompare(unsigned int profile_set,
                                unsigned int sample_index,
                                const char*  counter_name,
                                GpaFloat64   counter_value,
                                CompareType  compare_type,
                                GpaFloat64   compare_value,
                                GpaFloat64   compare_value2 = 0);

    /// @brief  Validate a specified counter in a specified sample.
    ///
    /// @param [in] frame_number The frame number containing the counter being compared.
    /// @param [in] sample_index The index of the sample containing the counter.
    /// @param [in] counter_name The name of the counter to validate.
    /// @param [in] counter_value The value of the counter to validate.
    /// @param [in] counter_usage_type The usage type of the counter being compared.
    ///
    /// @return True if the counter value validates successfully, false otherwise.
    bool GpaValidateData(unsigned int frame_number,
                         unsigned int sample_index,
                         const char*  counter_name,
                         GpaFloat64   counter_value,
                         GpaUsageType counter_usage_type);

    /// @brief  Validate a specified counter in a specified sample for GFX8 hardware.
    ///
    /// @param [in] frame_number The frame number containing the counter being compared.
    /// @param [in] sample_index The index of the sample containing the counter.
    /// @param [in] counter_name The name of the counter to validate.
    /// @param [in] counter_value The value of the counter to validate.
    /// @param [in] counter_usage_type The usage type of the counter being compared.
    ///
    /// @return True if the counter value validates successfully, false otherwise.
    bool GpaValidateDataGfx8(unsigned int frame_number,
                             unsigned int sample_index,
                             const char*  counter_name,
                             GpaFloat64   counter_value,
                             GpaUsageType counter_usage_type);

    /// @brief Validate a specified counter in a specified sample against expectations for GFX9 hardware.
    ///
    /// @param [in] frame_number The frame number containing the counter being compared.
    /// @param [in] sample_index The index of the sample containing the counter.
    /// @param [in] counter_name The name of the counter to validate.
    /// @param [in] counter_value The value of the counter to validate.
    /// @param [in] counter_usage_type The usage type of the counter being compared.
    ///
    /// @return True if the counter value validates successfully, false otherwise.
    bool GpaValidateDataGfx9(unsigned int frame_number,
                             unsigned int sample_index,
                             const char*  counter_name,
                             GpaFloat64   counter_value,
                             GpaUsageType counter_usage_type);

    /// @brief Validate a specified counter in a specified sample against expectations for GFX10 hardware.
    ///
    /// @param [in] frame_number The frame number containing the counter being compared.
    /// @param [in] sample_index The index of the sample containing the counter.
    /// @param [in] counter_name The name of the counter to validate.
    /// @param [in] counter_value The value of the counter to validate.
    /// @param [in] counter_usage_type The usage type of the counter being compared.
    ///
    /// @return True if the counter value validates successfully, false otherwise.
    bool GpaValidateDataGfx10(unsigned int frame_number,
                              unsigned int sample_index,
                              const char*  counter_name,
                              GpaFloat64   counter_value,
                              GpaUsageType counter_usage_type);

    /// @brief Validate a specified counter in a specified sample against expectations for GFX103 hardware.
    ///
    /// @param [in] frame_number The frame number containing the counter being compared.
    /// @param [in] sample_index The index of the sample containing the counter.
    /// @param [in] counter_name The name of the counter to validate.
    /// @param [in] counter_value The value of the counter to validate.
    /// @param [in] counter_usage_type The usage type of the counter being compared.
    ///
    /// @return True if the counter value validates successfully, false otherwise.
    bool GpaValidateDataGfx103(unsigned int frame_number,
                               unsigned int sample_index,
                               const char*  counter_name,
                               GpaFloat64   counter_value,
                               GpaUsageType counter_usage_type);

    /// @brief Validate a specified counter in a specified sample against expectations for GFX11 hardware.
    ///
    /// @param [in] frame_number The frame number containing the counter being compared.
    /// @param [in] sample_index The index of the sample containing the counter.
    /// @param [in] counter_name The name of the counter to validate.
    /// @param [in] counter_value The value of the counter to validate.
    /// @param [in] counter_usage_type The usage type of the counter being compared.
    ///
    /// @return True if the counter value validates successfully, false otherwise.
    bool GpaValidateDataGfx11(unsigned int frame_number,
                              unsigned int sample_index,
                              const char*  counter_name,
                              GpaFloat64   counter_value,
                              GpaUsageType counter_usage_type);

    /// @brief Populates the session result.
    ///
    /// @return True upon successful operation.
    bool GpaPopulateSessionResult();

    /// @brief Logs the GPA messages.
    ///
    /// @param [in] logging_type The type of GPA log message.
    /// @param [in] log_message The GPA log message.
    ///
    /// @return True upon successful operation.
    bool GpaLog(GpaLoggingType logging_type, const char* log_message);
#pragma endregion
};

#endif  // GPU_PERF_API_EXAMPLES_DX12_DX12_COLOR_CUBE_CUBE_SAMPLE_
