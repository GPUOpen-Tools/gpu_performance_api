//==============================================================================
// Copyright (c) 2019 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  DX11 Triangle Sample header
//==============================================================================

#ifndef _D3D11_TRIANGLE_H_
#define _D3D11_TRIANGLE_H_

#include <dxgi1_3.h>

#ifdef _DEBUG
#include <dxgidebug.h>
#endif

#include <d3d11.h>
#include <stack>
#include <fstream>
#include <sstream>
#include <atomic>

//#define DISABLE_GPA 1 - Uncomment to disable GPA

#include "GPAInterfaceLoader.h"
#include <vector>

/*
 * This sample demonstrates usage of GPA
 * by drawing a triangle.
 */

/// class for D3D11 triangle sample
class D3D11Triangle
{
public:
    /// Get the static instance of the triangle sample
    /// \return static instance of the triangle sample
    static D3D11Triangle* Instance();

    /// Initializes the triangle sample
    bool Init();

    /// Draw the triangle sample
    void Draw();

    /// Toggles the profiling
    void ToggleProfiling();

    /// Destructor
    ~D3D11Triangle() = default;

    /// De-allocates all the resources
    void Destroy() const;

private:
    /// struct for vertex data
    struct VertexData
    {
        float m_position[4];  ///< position
        float m_color[4];     ///< color
    };

    ID3D11Device*               m_pDx11Device;              ///< DX11 Device
    ID3D11DeviceContext*        m_pDx11ImmediateContext;    ///< DX11 Immediate device context
    IDXGIFactory1*              m_pdxgiFactory1;            ///< DXGI Factory 2
    IDXGISwapChain*             m_pdxgiSwapChain;           ///< DXGI Swap chain
    ID3D11Buffer*               m_pVertexBuffer;            ///< Vertex Buffer
    ID3D11VertexShader*         m_pVertexShader;            ///< Vertex shader
    ID3D11PixelShader*          m_pPixelShader;             ///< Pixel shader
    ID3D11RenderTargetView*     m_pRTV;                     ///< Render target view
    ID3D11InputLayout*          m_pdx11InputLayout;         ///< IA Input layout
    ID3D11DepthStencilState*    m_pDepthStencilState;       ///< Depth-Stencil state
    ID3D11RasterizerState*      m_pRasterizerState;         ///< rasterizer state
    D3D11_VIEWPORT              m_viewPort;                 ///< view port

    unsigned int                m_frameCounter;        ///< frame counter
    std::stringstream           m_content;             ///< content stream
    std::stringstream           m_header;              ///< header stream
    bool                        m_isHeaderWritten;     ///< flag indicating header is written or not

    GPAFunctionTable* m_pGpaFunctionTable;  ///< GPA function table
    GPA_ContextId     m_gpaContextId;       ///< GPA context id
    GPA_SessionId     m_gpaSessionId;       ///< GPA session id
    GPA_CommandListId m_gpaCommandListId;   ///< GPA command list
    gpa_uint32        m_deviceId;           ///< Device Id
    gpa_uint32        m_revisionId;         ///< Revision Id
    std::string       m_deviceName;         ///< Device Name

    unsigned int m_passRequired;           ///< number of pass required for the enabled set of counters
    int          m_currentPass;            ///< current pass
    int          m_sampleCounter;          ///< sample counter
    std::vector<int> m_sampleList;         ///< sample list
    std::string  m_counterFileName;        ///< name of the counter data file
    std::string  m_gpaLogFileName;         ///< name of the GPA log file
    std::fstream m_gpaLogFileStream;       ///< GPA log file stream
    std::fstream m_counterDataFileStream;  ///< counter data file stream
    std::wstring m_executablePath;         ///< path of the sample executable
    bool         m_profilingEnable;        ///< flag indicating profiling is enabled or not

    /// constructor
    D3D11Triangle();

    static constexpr unsigned int ms_frameCount    = 2;  ///< frame count
    static constexpr unsigned int ms_viewPortCount = 4;  ///< number of viewports
    static D3D11Triangle*          ms_pDx11Triangle;     ///< static instance of the d3d11 triangle sample

    /// Resets the pass resources;
    void ResetGpaPassInfo();

public:

#pragma region GPA_Wrappers
    /// Initializes GPA and open its context
    /// \return true upon successful operation
    bool GPA_InitializeAndOpenContext();

    /// Releases the GPA and closes its context
    /// \return true upon successful operation
    bool GPA_ReleaseContextAndDestroy();

    /// Enables GPA counters
    /// \return true upon successful operation
    bool GPA_EnableCounters();

    /// Creates the GPA profiling session
    /// \return true upon successful operation
    bool GPA_CreateProfilingSession();

    /// Deletes the GPA profiling session
    /// \return true upon successful operation
    bool GPA_DeleteProfilingSession();

    /// Begins the GPA profiling session
    /// \return true upon successful operation
    bool GPA_BeginProfilingSession();

    /// Ends the GPA profiling session
    /// \return true upon successful operation
    bool GPA_EndProfilingSession() const;

    /// Begins workload for the GPA session pass
    /// \return true upon successful operation
    bool GPA_BeginPass();

    /// Ends the GPA session pass
    /// \return true upon successful operation
    bool GPA_EndPass();

    /// Resets the information needed for the next pass
    /// \return true upon successful operation
    bool GPA_NextPassNeeded() const;

    /// Begins GPA sample
    /// \return true upon successful operation
    bool GPA_BeginSample();

    /// Ends a GPA sample
    /// \return true upon successful operation
    bool GPA_EndSample();

    /// Enum to define type of counter validation to perform
    typedef enum
    {
        COMPARE_TYPE_EQUAL,                     ///< Counter value must be equal to a specified value
        COMPARE_TYPE_GREATER_THAN,              ///< Counter value must be greater than a specified value
        COMPARE_TYPE_GREATER_THAN_OR_EQUAL_TO,  ///< Counter value must be greater than or equal to a specified value
        COMPARE_TYPE_LESS_THAN,                 ///< Counter value must be less than a specified value
        COMPARE_TYPE_LESS_THAN_OR_EQUAL_TO,     ///< Counter value must be less than or equal to a specified value
    } CompareType;

    /// Compare retrieved counter value to an expected value
    /// \param frameNumber the frame number containing the counter being compared
    /// \param sampleIndex the sample index of the counter being compared
    /// \param pCounterName the name of the counter being compared
    /// \param counterValue the retrieved counter value
    /// \param compareType the type of compare to perform
    /// \param compareVal the expected counter value (subject to the compare type)
    /// \return true if the counter value compares successfully, false otherwise
    bool GPA_CounterValueCompare(unsigned int frameNumber,
                                 unsigned int sampleIndex,
                                 const char*  pCounterName,
                                 gpa_float64  counterValue,
                                 CompareType  compareType,
                                 gpa_float64  compareVal);

    /// Validate a specified counter in a specified sample
    /// \param frameNumber the frame number containing the counter being compared
    /// \param sampleIndex the index of the sample containing the counter
    /// \param pCounterName the name of the counter to validate
    /// \param counterValue the value of the counter to validate
    /// \param counterUsageType the usage type of the counter being compared
    /// \return true if the counter value validates successfully, false otherwise
    bool GPA_ValidateData(unsigned int   frameNumber,
                          unsigned int   sampleIndex,
                          const char*    pCounterName,
                          gpa_float64    counterValue,
                          GPA_Usage_Type counterUsageType);

    /// Populates the session result
    /// \return true upon successful operation
    bool GPA_PopulateSessionResult();

    /// Logs the GPA messages
    /// \param loggingType the type of GPA log message
    /// \param logMessage the GPA log message
    /// \return true upon successful operation
    bool GPA_Log(GPA_Logging_Type loggingType, const char* logMessage);
#pragma endregion
};

#endif  // _D3D11_TRIANGLE_H_