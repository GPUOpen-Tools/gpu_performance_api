//==============================================================================
// Copyright (c) 2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  A class for managing hardware information
//==============================================================================

#include "GPAHWInfo.h"
#include <assert.h>
#include <DeviceInfoUtils.h>
#include "Logging.h"
#include "Logging.h"

GPA_HWInfo::GPA_HWInfo()
    :
    m_deviceId(0),
    m_deviceIdSet(false),
    m_revisionId(0),
    m_revisionIdSet(false),
    m_vendorId(0),
    m_vendorIdSet(false),
    m_deviceName(""),
    m_deviceNameSet(false),
    m_gpuIndex(0),
    m_gpuIndexSet(false),
    m_generation(GDT_HW_GENERATION_NONE),
    m_generationSet(false),
    m_timeStampFrequency(1),
    m_timeStampFrequencySet(false),
    m_asicType(GDT_ASIC_TYPE_NONE),
    m_numShaderEngines(0),
    m_numSIMDs(0),
    m_suClockPrim(0),
    m_numPrimPipes(0)
{
}

GPA_HWInfo::~GPA_HWInfo()
{
}

bool GPA_HWInfo::GetDeviceID(gpa_uint32& id)
{
    id = m_deviceId;
    return m_deviceIdSet;
}

bool GPA_HWInfo::GetRevisionID(gpa_uint32& id)
{
    id = m_revisionId;
    return m_revisionIdSet;
}

bool GPA_HWInfo::GetVendorID(gpa_uint32& vid)
{
    vid = m_vendorId;
    return m_vendorIdSet;
}

bool GPA_HWInfo::GetDeviceName(const char*& pName)
{
    pName = m_deviceName.c_str();
    return m_deviceNameSet;
}

bool GPA_HWInfo::GetGpuIndex(unsigned int& gpuIndex)
{
    gpuIndex = m_gpuIndex;
    return m_gpuIndexSet;
}

bool GPA_HWInfo::GetHWGeneration(GDT_HW_GENERATION& gen)
{
    gen = m_generation;
    return m_generationSet;
}

bool GPA_HWInfo::GetHWAsicType(GDT_HW_ASIC_TYPE& type)
{
    type = m_asicType;
    return m_asicType != GDT_ASIC_TYPE_NONE;
}

void GPA_HWInfo::SetDeviceID(gpa_uint32 id)
{
    m_deviceIdSet = true;
    m_deviceId = id;
}

void GPA_HWInfo::SetRevisionID(gpa_uint32 id)
{
    m_revisionIdSet = true;
    m_revisionId = id;
}

void GPA_HWInfo::SetVendorID(gpa_uint32 vid)
{
    m_vendorIdSet = true;
    m_vendorId = vid;
}

void GPA_HWInfo::SetDeviceName(const char* pName)
{
    m_deviceNameSet = true;
    m_deviceName = pName;
}

void GPA_HWInfo::SetGpuIndex(const unsigned int gpuIndex)
{
    m_gpuIndexSet = true;
    m_gpuIndex = gpuIndex;
}

void GPA_HWInfo::SetHWGeneration(GDT_HW_GENERATION generation)
{
    m_generationSet = true;
    m_generation = generation;
}

void GPA_HWInfo::SetTimeStampFrequency(gpa_uint64 frequency)
{
    m_timeStampFrequencySet = true;
    m_timeStampFrequency = frequency;
}

//-----------------------------------------------------------------------------
bool GPA_HWInfo::UpdateDeviceInfoBasedOnDeviceID()
{
    GDT_GfxCardInfo cardInfo;

    if (AMDTDeviceInfoUtils::Instance()->GetDeviceInfo(m_deviceId, m_revisionId, cardInfo))
    {
        GPA_LogDebugMessage("Found device ID: %X which is generation %d", cardInfo.m_deviceID, cardInfo.m_generation);

        GDT_DeviceInfo deviceInfo;

        if (AMDTDeviceInfoUtils::Instance()->GetDeviceInfo(m_deviceId, m_revisionId, deviceInfo))
        {
            this->m_numShaderEngines = deviceInfo.m_nNumShaderEngines;
            this->m_numSIMDs = deviceInfo.numberSIMDs();
            this->m_suClockPrim = deviceInfo.m_suClocksPrim;
            this->m_numPrimPipes = deviceInfo.m_nNumPrimPipes;
            this->m_asicType = cardInfo.m_asicType;
            this->SetDeviceName(cardInfo.m_szMarketingName);
            this->SetHWGeneration(cardInfo.m_generation);
            return true;
        }
    }

#if defined(WIN32) && defined(GDT_INTERNAL)

    //only emit an error for AMD devices
    if (IsAMD())
    {
        GPA_LogDebugError("Unrecognized device ID %X", this->m_deviceId);
        GPA_LogError("Unrecognized device ID.");
    }

#else
    GPA_LogDebugError("Unrecognized device ID %X", this->m_deviceId);
    GPA_LogError("Unrecognized device ID.");
#endif
    return false;
}

bool GPA_HWInfo::UpdateRevisionIdBasedOnDeviceIDAndName()
{
    std::vector<GDT_GfxCardInfo> cardList;

    if (m_deviceNameSet)
    {
        if (AMDTDeviceInfoUtils::Instance()->GetAllCardsWithDeviceId(m_deviceId, cardList))
        {
            for (auto it = cardList.begin(); it != cardList.end(); ++it)
            {
                string thisMarketingName(it->m_szMarketingName);

                if (thisMarketingName.compare(this->m_deviceName) == 0)
                {
                    SetRevisionID(static_cast<gpa_uint32>(it->m_revID));
                    return true;
                }
            }
        }
    }

    SetRevisionID(0);
    return false;
}

GPA_Status CompareHwInfo(GPA_HWInfo* pFirst, GPA_HWInfo* pSecond)
{
    GPA_Status result = GPA_STATUS_OK;

    if ((nullptr == pFirst) || (nullptr == pSecond))
    {
        result = GPA_STATUS_ERROR_NULL_POINTER;
    }
    else
    {
        gpa_uint32 firstVendorId;

        if (pFirst->GetVendorID(firstVendorId))
        {
            gpa_uint32 secondVendorId;

            if (pSecond->GetVendorID(secondVendorId))
            {
                if (firstVendorId != secondVendorId)
                {
                    GPA_LogError("Vendor ID mismatch");
                    result = GPA_STATUS_ERROR_FAILED;
                }
                else
                {
                    if (pFirst->IsAMD() && pSecond->IsAMD())
                    {
                        gpa_uint32 firstDeviceId;

                        if (pFirst->GetDeviceID(firstDeviceId))
                        {
                            gpa_uint32 secondDeviceId;

                            if (pSecond->GetDeviceID(secondDeviceId))
                            {
                                if (firstDeviceId != secondDeviceId)
                                {
                                    GPA_LogError("Device ID mismatch");
                                    result = GPA_STATUS_ERROR_FAILED;
                                }
                                else
                                {
                                    gpa_uint32 firstRevisionId;

                                    if (pFirst->GetRevisionID(firstRevisionId))
                                    {
                                        gpa_uint32 secondRevisionId;

                                        if (pSecond->GetRevisionID(secondRevisionId))
                                        {
                                            if (firstRevisionId != secondRevisionId)
                                            {
                                                GPA_LogError("Revision ID mismatch");
                                                result = GPA_STATUS_ERROR_FAILED;
                                            }
                                        }
                                        else
                                        {
                                            GPA_LogError("Failed to get revision ID");
                                            result = GPA_STATUS_ERROR_FAILED;
                                        }
                                    }
                                    else
                                    {
                                        GPA_LogError("Failed to get revision ID");
                                        result = GPA_STATUS_ERROR_FAILED;
                                    }

                                }
                            }
                            else
                            {
                                GPA_LogError("Failed to get device ID");
                                result = GPA_STATUS_ERROR_FAILED;
                            }
                        }
                        else
                        {
                            GPA_LogError("Failed to get device ID");
                            result = GPA_STATUS_ERROR_FAILED;
                        }
                    }
                }
            }
            else
            {
                GPA_LogError("Failed to get vendor ID");
                result = GPA_STATUS_ERROR_FAILED;
            }
        }
        else
        {
            GPA_LogError("Failed to get vendor ID");
            result = GPA_STATUS_ERROR_FAILED;
        }
    }

    return result;
}
