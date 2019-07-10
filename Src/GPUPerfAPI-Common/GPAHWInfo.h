//==============================================================================
// Copyright (c) 2011-2019 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  A class for managing hardware information
//==============================================================================

#ifndef _GPA_HW_INFO_H_
#define _GPA_HW_INFO_H_

#include "GPUPerfAPITypes.h"
#include "DeviceInfo.h"
#include <string>
#include <vector>

static const int AMD_VENDOR_ID    = 0x1002;  ///< the AMD vendor ID
static const int NVIDIA_VENDOR_ID = 0x10DE;  ///< the NVidia vendor ID
static const int INTEL_VENDOR_ID  = 0x8086;  ///< the Intel vendor ID

/// Stores information about the hardware installed in the machine.
class GPA_HWInfo
{
public:
    /// default constructor
    GPA_HWInfo();

    /// destructor
    ~GPA_HWInfo() = default;

    /// Sets the revision ID.
    /// \param id The revision ID of the available device.
    void SetRevisionID(const gpa_uint32& id);

    /// Sets the device ID.
    /// \param id The ID of the available device.
    void SetDeviceID(const gpa_uint32& id);

    /// Sets the vendor ID.
    /// \param vid The vendor ID of the available device.
    void SetVendorID(const gpa_uint32& vid);

    /// Sets the hardware generation that the device belongs to.
    /// \param generation The hardware generation.
    void SetHWGeneration(const GDT_HW_GENERATION& generation);

    /// Sets the device name
    /// \param pName A name of the device (ie "ATI Radeon HD 2600 series")
    void SetDeviceName(const char* pName);

    /// Set the GPU index of the GPU in the system
    /// \param gpuIndex The GPU index in the system
    void SetGpuIndex(const unsigned int& gpuIndex);

    /// Sets the frequency of the clock that the timestamps are based on.
    /// \param frequency The timestamp clock frequency.
    void SetTimeStampFrequency(const gpa_uint64& frequency);

    /// Sets the number of SIMDs
    /// \param numSIMDs The number of SIMDs
    void SetNumberSIMDs(const size_t& numSIMDs);

    /// Sets the number of compute units
    /// \param numCUs The number of compute units
    void SetNumberCUs(const size_t& numCUs);

    /// Sets the number of shader engines
    /// \param numSEs The number of shader engines
    void SetNumberShaderEngines(const size_t& numSEs);

    /// Sets the number of shader arrays
    /// \param numShaderArrays The number of shader arrays
    void SetNumberShaderArrays(const size_t& numSAs);

    /// Gets the number of shader engines
    /// \return the number of shader engines
    size_t GetNumberShaderEngines() const
    {
        return m_numShaderEngines;
    }

    /// Gets the number of shader arrays
    /// \return the number of shader arrays
    size_t GetNumberShaderArrays() const
    {
        return m_numShaderArrays;
    }

    /// Gets the number of SIMDs
    /// \return the number of SIMDs
    size_t GetNumberSIMDs() const
    {
        return m_numSIMDs;
    }

    /// Gets the number of CUs
    /// \return the number of CUs
    size_t GetNumberCUs() const
    {
        return m_numCUs;
    }

    /// Gets the number of clocks per primitive
    /// \return the number of clocks per primitive
    size_t GetSUClocksPrim() const
    {
        return m_suClockPrim;
    }

    /// Gets the number of primitive pipes
    /// \return the number of primitive pipes
    size_t GetNumberPrimPipes() const
    {
        return m_numPrimPipes;
    }

    /// Gets the revision ID.
    /// \param id [out] The revision ID.
    /// \return True if the revision ID is available; false otherwise.
    bool GetRevisionID(gpa_uint32& id) const;

    /// Gets the device ID.
    /// \param id [out] The device ID.
    /// \return True if the device ID is available; false otherwise.
    bool GetDeviceID(gpa_uint32& id) const;

    /// Gets the vendor id.
    /// \param vid [out] The vendor id.
    /// \return True if the vendor id is available; false otherwise.
    bool GetVendorID(gpa_uint32& vid) const;

    /// Gets the device name.
    /// \param pName [out] The device name.
    /// \return True if the device name is available; false otherwise.
    bool GetDeviceName(const char*& pName) const;

    /// Get the GPU index in the system
    /// \param[out] gpuIndex The GPU index in the system
    /// \return True if the gpu index is available, false otherwise
    bool GetGpuIndex(unsigned int& gpuIndex) const;

    /// Gets the hardware generation.
    /// \param gen [out] The HW generation
    /// \return True if the HW generation is available; false otherwise.
    bool GetHWGeneration(GDT_HW_GENERATION& gen) const;

    /// Gets the ASIC type.
    /// \param type [out] The ASIC type.
    /// \return True if the ASIC type is available; false otherwise.
    bool GetHWAsicType(GDT_HW_ASIC_TYPE& type) const;

    /// Gets the timestamp clock frequency.
    /// \param[out] timestampFrequency timestamp frequency
    /// \return the clock frequency.
    bool GetTimeStampFrequency(gpa_uint64& timestampFrequency) const
    {
        timestampFrequency = m_timeStampFrequency;
        return m_timeStampFrequencySet;
    }

    /// uses the DeviceId to find the correct DeviceMapping and DeviceInfo.
    /// Sets devInfo and sets DeviceName and HWGeneration if not previously set.
    /// \return true if HW should be supported and information is obtained correctly.
    bool UpdateDeviceInfoBasedOnDeviceID();

    /// uses the device id and name to assign a revision id
    /// Will assign zero if it cannot find a matching device
    /// \return true if HW should be supported and information is obtained correctly.
    bool UpdateRevisionIdBasedOnDeviceIDAndName();

    /// uses the asic type and name to assign a device and revision id
    /// Will leave device id alone and assign REVISION_ID_ANY if it cannot find a matching device
    /// \param asicType the asic Type
    /// \return true if HW should be supported and information is obtained correctly.
    bool UpdateDeviceInfoBasedOnASICTypeAndName(GDT_HW_ASIC_TYPE asicType);

    /// Check if the current hardware is AMD hardware
    /// \return true if the current hardware is AMD hardware
    bool IsAMD() const
    {
        return m_vendorIdSet && AMD_VENDOR_ID == m_vendorId;
    };

    /// Check if the current hardware is NVidia hardware
    /// \return true if the current hardware is NVidia hardware
    bool IsNVidia() const
    {
        return m_vendorIdSet && NVIDIA_VENDOR_ID == m_vendorId;
    };

    /// Check if the current hardware is Intel hardware
    /// \return true if the current hardware is Intel hardware
    bool IsIntel() const
    {
        return m_vendorIdSet && INTEL_VENDOR_ID == m_vendorId;
    };

    /// check whether the hardware infos are same or not
    /// \param[in] otherHwInfo hardware info
    /// \return true if both hardware info are same otherwise false
    bool operator==(GPA_HWInfo otherHwInfo) const;

private:
    gpa_uint32 m_deviceId;     ///< The device ID
    bool       m_deviceIdSet;  ///< Indicates if the Device ID has been set

    gpa_uint32 m_revisionId;     ///< The revision ID
    bool       m_revisionIdSet;  ///< Indicates if the Revision ID has been set

    gpa_uint32 m_vendorId;     ///< The vendor ID
    bool       m_vendorIdSet;  ///< Indicates if the vendor ID has been set

    std::string m_deviceName;     ///< the device name
    bool        m_deviceNameSet;  ///< Indicates if the device name has been set

    unsigned int m_gpuIndex;     ///< Index of the GPU in the system
    bool         m_gpuIndexSet;  ///< Indicates the GPU index has been set

    GDT_HW_GENERATION m_generation;     ///< the hardware generation
    bool              m_generationSet;  ///< Indicates if the hardware generation has been set

    gpa_uint64 m_timeStampFrequency;     ///< the frequency of the time stamp clock
    bool       m_timeStampFrequencySet;  ///< Indicates if the timestamp frequency has been set

    size_t m_numSIMDs;     ///< Number of SIMDs
    bool   m_numSIMDsSet;  ///< Indicates if the number of SIMDs has been set

    size_t m_numCUs;     ///< Number of CUs
    bool   m_numCUsSet;  ///< Indicates the CUs has been set or not

    GDT_HW_ASIC_TYPE m_asicType;  ///< Indicates the ASIC type of this device

    size_t m_numShaderEngines;     ///< Number of shader engines
    bool   m_numShaderEnginesSet;  ///< Indicates the shader engines has been set or not

    size_t m_numShaderArrays;     ///< Number of shader arrays
    bool   m_numShaderArraysSet;  ///< Indicates the shader engines has been set or not

    size_t m_suClockPrim;  ///< Number of clocks it takes to process a primitive
    size_t m_numPrimPipes; ///< Number of primitive pipes
};

#endif  //_GPA_HW_INFO_H_
