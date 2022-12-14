//==============================================================================
// Copyright (c) 2019-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief DX11 Triangle Sample header.
//==============================================================================

#ifndef GPU_PERF_API_EXAMPLES_DX11_DX11_TRIANGLE_DX11_TRIANGLE_H_
#define GPU_PERF_API_EXAMPLES_DX11_DX11_TRIANGLE_DX11_TRIANGLE_H_

#include <atomic>
#include <fstream>
#include <sstream>
#include <stack>
#include <vector>

#include <dxgi1_3.h>
#include <d3d11.h>

#ifdef _DEBUG
#include <dxgidebug.h>
#endif


#include "gpu_performance_api/gpu_perf_api_interface_loader.h"

#include "examples/dx11/sample.h"

/// @brief Class for D3D11 triangle sample.
///
/// This sample demonstrates usage of GPA by drawing a triangle.
class D3D11Triangle
{
public:
    /// @brief Get the static instance of the triangle sample.
    ///
    /// @return Static instance of the triangle sample.
    static D3D11Triangle* Instance();

    /// @brief Initializes the triangle sample.
    ///
    /// @param A pointer to the sample application context.
    /// @return true if initialization succeeds, and false otherwise.
    bool Init(gpa_example::Dx11SampleApp* app);

    /// @brief Draw the triangle.
    void Draw();

    /// @brief Present the drawn triangle.
    void Present();

    /// @brief Toggles the profiling.
    void ToggleProfiling();

    /// @brief Destructor.
    ~D3D11Triangle() = default;

    /// @brief De-allocates all the resources.
    void Destroy() const;

private:
    /// @brief Struct for vertex data.
    struct VertexData
    {
        float position[4];  ///< Position.
        float color[4];     ///< Color.
    };

    ID3D11Device*            dx11_device_;             ///< DX11 Device.
    ID3D11DeviceContext*     dx11_immediate_context_;  ///< DX11 Immediate device context.
    IDXGIFactory1*           dxgi_factory_1_;          ///< DXGI Factory 2.
    IDXGISwapChain*          dxgi_swap_chain_;         ///< DXGI Swap chain.
    ID3D11Buffer*            vertex_bufffer_;          ///< Vertex Buffer.
    ID3D11VertexShader*      vertex_shader_;           ///< Vertex shader.
    ID3D11PixelShader*       pixel_shader_;            ///< Pixel shader.
    ID3D11RenderTargetView*  render_target_view_;      ///< Render target view.
    ID3D11InputLayout*       input_layout_;            ///< IA Input layout.
    ID3D11DepthStencilState* depth_setncil_state_;     ///< Depth-Stencil state.
    ID3D11RasterizerState*   rasterizer_state_;        ///< Rasterizer state.
    D3D11_VIEWPORT           view_port_;               ///< Viewport.

    unsigned int      frame_counter_;      ///< Frame counter.
    std::stringstream content_stream_;     ///< Content stream.
    std::stringstream header_stream_;      ///< Header stream.
    bool              is_header_written_;  ///< Flag indicating header is written or not.

    GpaFunctionTable* gpa_function_table_;   ///< GPA function table.
    GpaContextId      gpa_context_id_;       ///< GPA context id.
    GpaSessionId      gpa_session_id_;       ///< GPA session id.
    GpaCommandListId  gpa_command_list_id_;  ///< GPA command list.
    GpaUInt32         device_id_;            ///< Device Id.
    GpaUInt32         revision_id_;          ///< Revision Id.
    std::string       device_name_;          ///< Device Name.

    unsigned int     num_passes_required_;       ///< Number of passes required for the enabled set of counters.
    int              current_pass_;              ///< Current pass.
    int              sample_counter_;            ///< Sample counter.
    std::vector<int> sample_list_;               ///< Sample list.
    std::string      counter_file_name_;         ///< Name of the counter data file.
    std::string      gpa_log_file_name_;         ///< Name of the GPA log file.
    std::fstream     gpa_log_file_stream_;       ///< GPA log file stream.
    std::fstream     counter_data_file_stream_;  ///< Counter data file stream.
    std::string      executable_path_;           ///< Path of the sample executable.
    bool             is_profiling_enabled_;      ///< Flag indicating profiling is enabled or not.

    gpa_example::Dx11SampleApp* app_;  ///< Pointer the the sample application context.

    /// @brief Constructor.
    D3D11Triangle();

    static constexpr unsigned int kFrameCount    = 2;  ///< Frame count.
    static constexpr unsigned int kViewportCount = 4;  ///< Number of viewports.
    static D3D11Triangle*         dx11_triangle_;      ///< Static instance of the d3d11 triangle sample.

    /// @brief Resets the pass resources.
    void ResetGpaPassInfo();

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

    /// @brief Begins GPA sample.
    ///
    /// @return True upon successful operation.
    bool GpaBeginSample();

    /// @brief Ends a GPA sample.
    ///
    /// @return True upon successful operation.
    bool GpaEndSample();

    /// @brief Enum to define type of counter validation to perform.
    typedef enum
    {
        kCompareTypeEqual,                 ///< Counter value must be equal to a specified value.
        kCompareTypeGreaterThan,           ///< Counter value must be greater than a specified value.
        kCompareTypeGreaterThanOrEqualTo,  ///< Counter value must be greater than or equal to a specified value.
        kCompareTypeLessThan,              ///< Counter value must be less than a specified value.
        kCompareTypeLessThanOrEqualTo,     ///< Counter value must be less than or equal to a specified value.
    } CompareType;

    /// @brief Compare retrieved counter value to an expected value.
    ///
    /// @param [in] frame_number The frame number containing the counter being compared.
    /// @param [in] sample_index The sample index of the counter being compared.
    /// @param [in] counter_name The name of the counter being compared.
    /// @param [in] counter_value The retrieved counter value.
    /// @param [in] compare_type The type of compare to perform.
    /// @param [in] compare_value The expected counter value (subject to the compare type).
    ///
    /// @return True if the counter value compares successfully, false otherwise.
    bool GpaCounterValueCompare(unsigned int frame_number,
                                unsigned int sample_index,
                                const char*  counter_name,
                                GpaFloat64   counter_value,
                                CompareType  compare_type,
                                GpaFloat64   compare_value);

    /// @brief Validate a specified counter in a specified sample.
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

#endif  // GPU_PERF_API_EXAMPLES_DX11_DX11_TRIANGLE_DX11_TRIANGLE_H_
