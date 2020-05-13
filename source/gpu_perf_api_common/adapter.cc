//==============================================================================
// Copyright (c) 2016-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Query adapters' info from GDI32.
//==============================================================================

#include <cassert>
#include <sstream>

#include "adapter.h"
#include "logging.h"
#include "utility.h"

bool Adapter::getAsicInfoList(AsicInfoList& asicInfoList) const
{
    IDXGIFactory* pDxgiFactory = nullptr;
    HRESULT       hr           = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&pDxgiFactory));
    bool          retVal       = false;

    if (SUCCEEDED(hr))
    {
        retVal = true;
        typedef std::vector<DXGI_ADAPTER_DESC> DxgiAdapterDescList;
        static const size_t                    DxgiAdapterDescListInitalSize = 32;
        DxgiAdapterDescList                    dxgiAdapterDescList(DxgiAdapterDescListInitalSize);
        UINT                                   adapterIndex = 0;

        while (SUCCEEDED(hr))
        {
            IDXGIAdapter* pDxgiAdapter = nullptr;
            hr                         = pDxgiFactory->EnumAdapters(adapterIndex, &pDxgiAdapter);

            if (SUCCEEDED(hr))
            {
                hr = pDxgiAdapter->GetDesc(&(dxgiAdapterDescList[adapterIndex]));
#ifdef _DEBUG
                assert(SUCCEEDED(hr));
#endif  // _DEBUG
                pDxgiAdapter->Release();
            }

            ++adapterIndex;

            if (dxgiAdapterDescList.size() <= adapterIndex)
            {
                dxgiAdapterDescList.resize(2 * dxgiAdapterDescList.size());
            }
        }

        // DXGI_ERROR_NOT_FOUND means enum adapters reached the last adapter
        if (DXGI_ERROR_NOT_FOUND != hr)
        {
            retVal = false;
        }
        else
        {
            const size_t listSize = adapterIndex > 0 ? adapterIndex - 1 : 0;
            asicInfoList.resize(listSize);

            for (size_t aii = 0; listSize > aii; ++aii)
            {
                dxgiAdapterDescToAsicInfo(dxgiAdapterDescList[aii], asicInfoList[aii]);
            }
        }

        pDxgiFactory->Release();
    }

    return retVal;
}

void Adapter::dxgiAdapterDescToAsicInfo(const DXGI_ADAPTER_DESC& dxgiAdapterDesc, ADLUtil_ASICInfo& asicInfo)
{
    GPAUtil::wcstringToString(dxgiAdapterDesc.Description, asicInfo.adapterName);
    std::stringstream strStream;
    strStream << std::hex << dxgiAdapterDesc.DeviceId;
    asicInfo.deviceIDString = strStream.str();
    asicInfo.vendorID       = dxgiAdapterDesc.VendorId;
    asicInfo.deviceID       = dxgiAdapterDesc.DeviceId;
    asicInfo.revID          = dxgiAdapterDesc.Revision;
}
