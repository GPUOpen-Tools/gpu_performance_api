//==============================================================================
// Copyright (c) 2016-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  Query adapters' info from GDI32.
//==============================================================================

#include "gpu_perf_api_common/adapter.h"

#include <cassert>
#include <sstream>

#include "gpu_perf_api_common/logging.h"
#include "gpu_perf_api_common/utility.h"

bool Adapter::GetAsicInfoList(AsicInfoList& asic_info_list) const
{
    IDXGIFactory* dxgi_factory = nullptr;
    HRESULT       hr           = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&dxgi_factory));
    bool          ret_val      = false;

    if (SUCCEEDED(hr))
    {
        ret_val = true;
        typedef std::vector<DXGI_ADAPTER_DESC> DxgiAdapterDescList;
        static const size_t                    kDxgiAdapterDescListInitialSize = 32;
        DxgiAdapterDescList                    dxgi_adapter_desc_list(kDxgiAdapterDescListInitialSize);
        UINT                                   adapter_index = 0;

        while (SUCCEEDED(hr))
        {
            IDXGIAdapter* dxgi_adapter = nullptr;
            hr                         = dxgi_factory->EnumAdapters(adapter_index, &dxgi_adapter);

            if (SUCCEEDED(hr))
            {
                hr = dxgi_adapter->GetDesc(&(dxgi_adapter_desc_list[adapter_index]));
#ifdef _DEBUG
                assert(SUCCEEDED(hr));
#endif
                dxgi_adapter->Release();
            }

            ++adapter_index;

            if (dxgi_adapter_desc_list.size() <= adapter_index)
            {
                dxgi_adapter_desc_list.resize(2 * dxgi_adapter_desc_list.size());
            }
        }

        // DXGI_ERROR_NOT_FOUND means enum adapters reached the last adapter.
        if (DXGI_ERROR_NOT_FOUND != hr)
        {
            ret_val = false;
        }
        else
        {
            const size_t list_size = adapter_index > 0 ? adapter_index - 1 : 0;
            asic_info_list.resize(list_size);

            for (size_t aii = 0; list_size > aii; ++aii)
            {
                DxgiAdapterDescToAsicInfo(dxgi_adapter_desc_list[aii], asic_info_list[aii]);
            }
        }

        dxgi_factory->Release();
    }

    return ret_val;
}

void Adapter::DxgiAdapterDescToAsicInfo(const DXGI_ADAPTER_DESC& dxgi_adapter_desc, ADLUtil_ASICInfo& asic_info)
{
    gpa_util::WideCharArrayToString(dxgi_adapter_desc.Description, asic_info.adapterName);
    std::stringstream str_stream;
    str_stream << std::hex << dxgi_adapter_desc.DeviceId;
    asic_info.deviceIDString = str_stream.str();
    asic_info.vendorID       = dxgi_adapter_desc.VendorId;
    asic_info.deviceID       = dxgi_adapter_desc.DeviceId;
    asic_info.revID          = dxgi_adapter_desc.Revision;
}
