//==============================================================================
// Copyright (c) 2010-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief PublicCounterDefinitions for CLGFX6
//==============================================================================

#include "PublicCounterDefsCLGfx6.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

void AutoDefinePublicCountersCLGfx6(GPA_PublicCounters& p)
{
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1639);

        p.DefinePublicCounter("Wavefronts", "General", "Total wavefronts.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0", "e8999836-489d-80a6-8e94-2c3ea191fd58" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1649);
        internalCounters.push_back(1639);

        p.DefinePublicCounter("VALUInsts", "General", "The average number of vector ALU instructions executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "17c27c10-3d5c-64c2-e7b4-4ee1abdbbb46" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1653);
        internalCounters.push_back(1639);

        p.DefinePublicCounter("SALUInsts", "General", "The average number of scalar ALU instructions executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "e5693881-8d63-951d-1f4f-f9e4c84236f5" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1651);
        internalCounters.push_back(1639);

        p.DefinePublicCounter("VFetchInsts", "General", "The average number of vector fetch instructions from the video memory executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "d45b0277-03fa-9480-eada-4871ec89c504" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1654);
        internalCounters.push_back(1639);

        p.DefinePublicCounter("SFetchInsts", "General", "The average number of scalar fetch instructions from the video memory executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "7d9e4356-a8f5-04c7-f7a8-fe68dc01c441" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1650);
        internalCounters.push_back(1639);

        p.DefinePublicCounter("VWriteInsts", "General", "The average number of vector write instructions to the video memory executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "d33f2e7c-3198-cf69-2432-d2a32f385d46" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1655);
        internalCounters.push_back(1639);

        p.DefinePublicCounter("LDSInsts", "LocalMemory", "The average number of LDS read or LDS write instructions executed per work item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "852ccd67-d2eb-d238-567a-0d1f7bf5f34f" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1656);
        internalCounters.push_back(1639);

        p.DefinePublicCounter("GDSInsts", "General", "The average number of GDS read or GDS write instructions executed per work item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "c63fc276-151e-3b88-6edb-a0c92507aadb" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1693);
        internalCounters.push_back(1685);

        p.DefinePublicCounter("VALUUtilization", "General", "The percentage of active vector ALU threads in a wave. A lower number can mean either more thread divergence in a wave or that the work-group size is not a multiple of 64. Value range: 0% (bad), 100% (ideal - no thread divergence).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,(64),*,/,(100),*,(100),min", "ffea5f90-624f-67dd-4ca6-74911f4c85d3" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1685);
        internalCounters.push_back(976);

        p.DefinePublicCounter("VALUBusy", "General", "The percentage of GPUTime vector ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,(4),*,NUM_SIMDS,/,1,/,(100),*", "51800108-e003-3c1f-b92a-e224aaab3c1b" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1690);
        internalCounters.push_back(976);

        p.DefinePublicCounter("SALUBusy", "General", "The percentage of GPUTime scalar ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/,1,/,(100),*", "f1d53e7a-0182-42f8-7d2c-6029bff6bc2d" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5801);
        internalCounters.push_back(5929);
        internalCounters.push_back(6057);
        internalCounters.push_back(6185);
        internalCounters.push_back(6313);
        internalCounters.push_back(6441);
        internalCounters.push_back(6569);
        internalCounters.push_back(6697);
        internalCounters.push_back(6825);
        internalCounters.push_back(6953);
        internalCounters.push_back(7081);
        internalCounters.push_back(7209);

        p.DefinePublicCounter("FetchSize", "GlobalMemory", "The total kilobytes fetched from the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_KILOBYTES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,sum12,(32),*,(1024),/", "d91ac445-b44f-f821-9123-9d829e544c33" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5795);
        internalCounters.push_back(5923);
        internalCounters.push_back(6051);
        internalCounters.push_back(6179);
        internalCounters.push_back(6307);
        internalCounters.push_back(6435);
        internalCounters.push_back(6563);
        internalCounters.push_back(6691);
        internalCounters.push_back(6819);
        internalCounters.push_back(6947);
        internalCounters.push_back(7075);
        internalCounters.push_back(7203);

        p.DefinePublicCounter("WriteSize", "GlobalMemory", "The total kilobytes written to the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_KILOBYTES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,sum12,(32),*,(1024),/", "e09d95da-2772-f7cb-51f5-4fad27bb998b" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5787);
        internalCounters.push_back(5915);
        internalCounters.push_back(6043);
        internalCounters.push_back(6171);
        internalCounters.push_back(6299);
        internalCounters.push_back(6427);
        internalCounters.push_back(6555);
        internalCounters.push_back(6683);
        internalCounters.push_back(6811);
        internalCounters.push_back(6939);
        internalCounters.push_back(7067);
        internalCounters.push_back(7195);
        internalCounters.push_back(5788);
        internalCounters.push_back(5916);
        internalCounters.push_back(6044);
        internalCounters.push_back(6172);
        internalCounters.push_back(6300);
        internalCounters.push_back(6428);
        internalCounters.push_back(6556);
        internalCounters.push_back(6684);
        internalCounters.push_back(6812);
        internalCounters.push_back(6940);
        internalCounters.push_back(7068);
        internalCounters.push_back(7196);

        p.DefinePublicCounter("CacheHit", "GlobalMemory", "The percentage of fetch, write, atomic, and other instructions that hit the data cache. Value range: 0% (no hit) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,sum12,0,1,2,3,4,5,6,7,8,9,10,11,sum12,12,13,14,15,16,17,18,19,20,21,22,23,sum12,+,/,(100),*", "dfbeebab-f7c1-1211-e502-4aae361e2ad7" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4859);
        internalCounters.push_back(4965);
        internalCounters.push_back(5071);
        internalCounters.push_back(5177);
        internalCounters.push_back(5283);
        internalCounters.push_back(5389);
        internalCounters.push_back(5495);
        internalCounters.push_back(5601);
        internalCounters.push_back(976);

        p.DefinePublicCounter("MemUnitBusy", "GlobalMemory", "The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,max,2,max,3,max,4,max,5,max,6,max,7,max,8,/,NUM_SHADER_ENGINES,/,(100),*", "a1efa380-4a72-e066-e06a-2ab71a488521" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(7708);
        internalCounters.push_back(7818);
        internalCounters.push_back(7928);
        internalCounters.push_back(8038);
        internalCounters.push_back(8148);
        internalCounters.push_back(8258);
        internalCounters.push_back(8368);
        internalCounters.push_back(8478);
        internalCounters.push_back(976);

        p.DefinePublicCounter("MemUnitStalled", "GlobalMemory", "The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,max,2,max,3,max,4,max,5,max,6,max,7,max,8,/,NUM_SHADER_ENGINES,/,(100),*", "465ba54f-d250-1453-790a-731b10d230b1" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5796);
        internalCounters.push_back(5924);
        internalCounters.push_back(6052);
        internalCounters.push_back(6180);
        internalCounters.push_back(6308);
        internalCounters.push_back(6436);
        internalCounters.push_back(6564);
        internalCounters.push_back(6692);
        internalCounters.push_back(6820);
        internalCounters.push_back(6948);
        internalCounters.push_back(7076);
        internalCounters.push_back(7204);
        internalCounters.push_back(976);

        p.DefinePublicCounter("WriteUnitStalled", "GlobalMemory", "The percentage of GPUTime the Write unit is stalled. Value range: 0% to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,max,2,max,3,max,4,max,5,max,6,max,7,max,8,max,9,max,10,max,11,max,12,/,(100),*", "594ad3ce-d1ec-10fc-7d59-25738e397d72" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1697);
        internalCounters.push_back(976);

        p.DefinePublicCounter("LDSBankConflict", "LocalMemory", "The percentage of GPUTime LDS is stalled by bank conflicts. Value range: 0% (optimal) to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,/,NUM_SIMDS,/,(100),*", "b3387100-3d5a-3235-e612-58b941683eb6" );
    }
}

