//==============================================================================
// Copyright (c) 2018-2023 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief CL GPA Implementation declarations
//==============================================================================

#ifndef GPU_PERF_API_CL_CL_GPA_IMPLEMENTOR_H_
#define GPU_PERF_API_CL_CL_GPA_IMPLEMENTOR_H_

// Common
#include "TSingleton.h"

// GPA Common
#include "gpa_implementor.h"

/// Class for CL GPA Implementation
class ClGpaImplementor : public GpaImplementor, public TSingleton<ClGpaImplementor>
{
    friend class TSingleton<ClGpaImplementor>;  ///< friend declaration to allow access to the constructor

public:
    /// Destructor
    ~ClGpaImplementor() = default;

    /// @copydoc IGpaInterfaceTrait::GetApiType()
    GpaApiType GetApiType() const override final;

    /// @copydoc GpaImplementor::GetHwInfoFromApi
    bool GetHwInfoFromApi(const GpaContextInfoPtr context_info, GpaHwInfo& hw_info) const override final;

    /// @copydoc GpaImplementor::VerifyApiHwSupport
    bool VerifyApiHwSupport(const GpaContextInfoPtr context_info, const GpaHwInfo& hw_info) const override final;

private:
    /// Constructor
    ClGpaImplementor()
        : init_perf_counter_amd_extension_(false)
    {};

    /// @copydoc GpaImplementor::OpenApiContext
    IGpaContext* OpenApiContext(GpaContextInfoPtr context_info, GpaHwInfo& hw_info, GpaOpenContextFlags flags) override final;

    /// @copydoc GpaImplementor::CloseApiContext
    bool CloseApiContext(GpaDeviceIdentifier device_identifier, IGpaContext* context) override final;

    /// @copydoc GpaImplementor::GetDeviceIdentifierFromContextInfo()
    GpaDeviceIdentifier GetDeviceIdentifierFromContextInfo(GpaContextInfoPtr context_info) const override final;

    bool init_perf_counter_amd_extension_;  ///< Flag indicating if the CL extension function pointers have been initialized.
};

#endif  // GPU_PERF_API_CL_CL_GPA_IMPLEMENTOR_H_
