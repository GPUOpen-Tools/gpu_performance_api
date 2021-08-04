//==============================================================================
// Copyright (c) 2018-2020 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief CL GPA Implementation declarations
//==============================================================================

#ifndef _CL_GPA_IMPLEMENTOR_H_
#define _CL_GPA_IMPLEMENTOR_H_

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

    bool init_perf_counter_amd_extension_;  ///< flag indicating if the CL extension function pointers have been initialized
};

#endif  // _CL_GPA_IMPLEMENTOR_H_
