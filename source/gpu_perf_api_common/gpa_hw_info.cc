//==============================================================================
// Copyright (c) 2016-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  A class for managing hardware information
//==============================================================================

#include <assert.h>
#include <DeviceInfoUtils.h>
#include "gpa_hw_info.h"
#include "logging.h"

GPA_HWInfo::GPA_HWInfo()
    : m_deviceId(0)
    , m_deviceIdSet(false)
    , m_revisionId(0)
    , m_revisionIdSet(false)
    , m_vendorId(0)
    , m_vendorIdSet(false)
    , m_deviceNameSet(false)
    , m_gpuIndex(0)
    , m_gpuIndexSet(false)
    , m_generation(GDT_HW_GENERATION_NONE)
    , m_generationSet(false)
    , m_timeStampFrequency(1)
    , m_timeStampFrequencySet(false)
    , m_numSIMDs(0)
    , m_numSIMDsSet(false)
    , m_numCUs(0)
    , m_numCUsSet(false)
    , m_asicType(GDT_ASIC_TYPE_NONE)
    , m_numShaderEngines(0)
    , m_numShaderEnginesSet(false)
    , m_numShaderArrays(0)
    , m_numShaderArraysSet(false)
    , m_suClockPrim(0)
    , m_numPrimPipes(0)
{
}

bool GPA_HWInfo::GetDeviceID(gpa_uint32& id) const
{
    id = m_deviceId;
    return m_deviceIdSet;
}

bool GPA_HWInfo::GetRevisionID(gpa_uint32& id) const
{
    id = m_revisionId;
    return m_revisionIdSet;
}

bool GPA_HWInfo::GetVendorID(gpa_uint32& vid) const
{
    vid = m_vendorId;
    return m_vendorIdSet;
}

bool GPA_HWInfo::GetDeviceName(const char*& pName) const
{
    pName = m_deviceName.c_str();
    return m_deviceNameSet;
}

bool GPA_HWInfo::GetGpuIndex(unsigned int& gpuIndex) const
{
    gpuIndex = m_gpuIndex;
    return m_gpuIndexSet;
}

bool GPA_HWInfo::GetHWGeneration(GDT_HW_GENERATION& gen) const
{
    gen = m_generation;
    return m_generationSet;
}

bool GPA_HWInfo::GetHWAsicType(GDT_HW_ASIC_TYPE& type) const
{
    type = m_asicType;
    return m_asicType != GDT_ASIC_TYPE_NONE;
}

void GPA_HWInfo::SetDeviceID(const gpa_uint32& id)
{
    m_deviceIdSet = true;
    m_deviceId    = id;
}

void GPA_HWInfo::SetRevisionID(const gpa_uint32& id)
{
    m_revisionIdSet = true;
    m_revisionId    = id;
}

void GPA_HWInfo::SetVendorID(const gpa_uint32& vid)
{
    m_vendorIdSet = true;
    m_vendorId    = vid;
}

void GPA_HWInfo::SetDeviceName(const char* pName)
{
    m_deviceNameSet = true;
    m_deviceName    = pName;
}

void GPA_HWInfo::SetGpuIndex(const unsigned int& gpuIndex)
{
    m_gpuIndexSet = true;
    m_gpuIndex    = gpuIndex;
}

void GPA_HWInfo::SetHWGeneration(const GDT_HW_GENERATION& generation)
{
    m_generationSet = true;
    m_generation    = generation;
}

void GPA_HWInfo::SetTimeStampFrequency(const gpa_uint64& frequency)
{
    m_timeStampFrequencySet = true;
    m_timeStampFrequency    = frequency;
}

void GPA_HWInfo::SetNumberSIMDs(const size_t& numSIMDs)
{
    m_numSIMDsSet = true;
    m_numSIMDs    = numSIMDs;
}

void GPA_HWInfo::SetNumberCUs(const size_t& numCUs)
{
    m_numCUsSet = true;
    m_numCUs    = numCUs;
}

void GPA_HWInfo::SetNumberShaderEngines(const size_t& numSEs)
{
    m_numShaderEnginesSet = true;
    m_numShaderEngines    = numSEs;
}

void GPA_HWInfo::SetNumberShaderArrays(const size_t& numSAs)
{
    m_numShaderArraysSet = true;
    m_numShaderArrays    = numSAs;
}

//-----------------------------------------------------------------------------
bool GPA_HWInfo::UpdateDeviceInfoBasedOnDeviceID()
{
    std::vector<GDT_GfxCardInfo> cardList;
    GDT_GfxCardInfo cardInfo = {};
    GDT_DeviceInfo deviceInfo = {};
    bool deviceInfoFound = false;

    if (m_deviceNameSet)
    {
        if (AMDTDeviceInfoUtils::Instance()->GetAllCardsWithDeviceId(m_deviceId, cardList))
        {
            for (auto it = cardList.begin(); it != cardList.end(); ++it)
            {
                if (m_revisionIdSet && m_revisionId != REVISION_ID_ANY && it->m_revID != m_revisionId)
                {
                    continue;
                }

                // first check for CAL name matches
                std::string thisCALName(it->m_szCALName);

                if (0 == thisCALName.compare(m_deviceName))
                {
                    cardInfo = *it;

                    if (AMDTDeviceInfoUtils::Instance()->GetDeviceInfo(it->m_szCALName, deviceInfo))
                    {
                        deviceInfoFound = true;
                        break;
                    }
                }

                // next check for marketing name matches
                std::string thisMarketingName(it->m_szMarketingName);

                if (0 == thisMarketingName.compare(m_deviceName))
                {
                    cardInfo = *it;

                    if (AMDTDeviceInfoUtils::Instance()->GetDeviceInfo(cardInfo.m_deviceID, cardInfo.m_revID, deviceInfo))
                    {
                        deviceInfoFound = true;
                        break;
                    }
                }
            }
        }
    }

    if (!deviceInfoFound)
    {
        if (AMDTDeviceInfoUtils::Instance()->GetDeviceInfo(m_deviceId, m_revisionId, cardInfo))
        {
            GPA_LogDebugMessage("Found device ID: %X which is generation %d.", cardInfo.m_deviceID, cardInfo.m_generation);

            if (AMDTDeviceInfoUtils::Instance()->GetDeviceInfo(m_deviceId, m_revisionId, deviceInfo))
            {
                deviceInfoFound = true;
            }
        }
    }

    if (deviceInfoFound)
    {
        if (!m_numShaderEnginesSet)
        {
            SetNumberShaderEngines(deviceInfo.m_nNumShaderEngines);
        }

        if (!m_numShaderArraysSet)
        {
            SetNumberShaderArrays(deviceInfo.numberSHs());
        }

        if (!m_numCUsSet)
        {
            SetNumberCUs(deviceInfo.numberCUs());
        }

        if (!m_numSIMDsSet)
        {
            SetNumberSIMDs(deviceInfo.numberSIMDs());
        }

        m_suClockPrim = deviceInfo.m_suClocksPrim;
        m_numPrimPipes = deviceInfo.m_nNumPrimPipes;
        m_asicType = cardInfo.m_asicType;
        SetDeviceName(cardInfo.m_szMarketingName);
        SetHWGeneration(cardInfo.m_generation);
        return true;
    }

    // only emit an error for AMD devices
    if (IsAMD())
    {
        std::stringstream ss;
        ss << "Unrecognized device ID: " << m_deviceId << ".";
        GPA_LogError(ss.str().c_str());
    }

    return false;
}

bool GPA_HWInfo::UpdateRevisionIdBasedOnDeviceIDAndName()
{
    std::vector<GDT_GfxCardInfo> cardList;

    if (m_deviceNameSet)
    {
        if (AMDTDeviceInfoUtils::Instance()->GetAllCardsWithDeviceId(m_deviceId, cardList))
        {
            // first check for exact matches
            for (auto it = cardList.begin(); it != cardList.end(); ++it)
            {
                std::string thisMarketingName(it->m_szMarketingName);

                if (0 == thisMarketingName.compare(m_deviceName))
                {
                    SetRevisionID(static_cast<gpa_uint32>(it->m_revID));
                    return true;
                }
            }

            // if no exact match is found, try a substring match (first part of string should match marketing name)
            for (auto it = cardList.begin(); it != cardList.end(); ++it)
            {
                std::string thisMarketingName(it->m_szMarketingName);

                if (0 == m_deviceName.find(thisMarketingName))
                {
                    SetRevisionID(static_cast<gpa_uint32>(it->m_revID));
                    return true;
                }
            }
        }
    }

    SetRevisionID(REVISION_ID_ANY);
    return false;
}

bool GPA_HWInfo::UpdateDeviceInfoBasedOnASICTypeAndName(GDT_HW_ASIC_TYPE asicType)
{
    std::vector<GDT_GfxCardInfo> cardList;

    if (m_deviceNameSet)
    {
        if (AMDTDeviceInfoUtils::Instance()->GetAllCardsWithAsicType(asicType, cardList))
        {
            // first check for exact matches
            for (auto it = cardList.begin(); it != cardList.end(); ++it)
            {
                std::string thisMarketingName(it->m_szMarketingName);

                if (0 == thisMarketingName.compare(m_deviceName))
                {
                    SetDeviceID(static_cast<gpa_uint32>(it->m_deviceID));
                    SetRevisionID(static_cast<gpa_uint32>(it->m_revID));
                    return true;
                }
            }

            // if no exact match is found, try a substring match (first part of string should match marketing name)
            for (auto it = cardList.begin(); it != cardList.end(); ++it)
            {
                std::string thisMarketingName(it->m_szMarketingName);

                if (0 == m_deviceName.find(thisMarketingName))
                {
                    SetDeviceID(static_cast<gpa_uint32>(it->m_deviceID));
                    SetRevisionID(static_cast<gpa_uint32>(it->m_revID));
                    return true;
                }
            }
        }
    }

    // if a match has not been found, try to match using the already set device id
    return UpdateRevisionIdBasedOnDeviceIDAndName();
}

bool GPA_HWInfo::operator==(GPA_HWInfo otherHwInfo) const
{
    bool isSame = false;

    if (!m_vendorIdSet)
    {
        GPA_LogError("Failed to get vendor Id.");
    }
    else if (!m_deviceIdSet)
    {
        GPA_LogError("Failed to get device Id.");
    }
    else if (!m_revisionIdSet)
    {
        GPA_LogError("Failed to get revision Id.");
    }
    else if (m_vendorId != otherHwInfo.m_vendorId)
    {
        GPA_LogDebugError("Vendor ID mismatch.");
    }
    else if (m_deviceId != otherHwInfo.m_deviceId)
    {
        GPA_LogDebugError("Device Id Mismatch.");
    }
    else if (m_revisionId != REVISION_ID_ANY && otherHwInfo.m_revisionId != REVISION_ID_ANY && m_revisionId != otherHwInfo.m_revisionId)
    {
        GPA_LogDebugError("Revision Id Mismatch.");
    }
    else
    {
        isSame = true;
    }

    return isSame;
}
