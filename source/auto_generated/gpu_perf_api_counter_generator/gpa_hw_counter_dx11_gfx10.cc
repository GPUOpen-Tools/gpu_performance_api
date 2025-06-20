//==============================================================================
// Copyright (c) 2010-2025 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief DX11 counter definitions for GFX10.
//==============================================================================

#include "gpu_perf_api_counter_generator/gpa_counter.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_gfx10.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_dx11_gfx10.h"

// This file is autogenerated by the ConvertHWEnums project

// clang-format off

namespace counter_dx11_gfx10
{
    using namespace counter_gfx10;

    std::vector<std::vector<GpaHardwareCounterDesc>*> kDx11CounterGroupArrayGfx10 = {
        &kCpfCountersGfx10,
        &kCb0CountersGfx10,
        &kCb1CountersGfx10,
        &kCb2CountersGfx10,
        &kCb3CountersGfx10,
        &kCb4CountersGfx10,
        &kCb5CountersGfx10,
        &kCb6CountersGfx10,
        &kCb7CountersGfx10,
        &kCb8CountersGfx10,
        &kCb9CountersGfx10,
        &kCb10CountersGfx10,
        &kCb11CountersGfx10,
        &kCb12CountersGfx10,
        &kCb13CountersGfx10,
        &kCb14CountersGfx10,
        &kCb15CountersGfx10,
        &kDb0CountersGfx10,
        &kDb1CountersGfx10,
        &kDb2CountersGfx10,
        &kDb3CountersGfx10,
        &kDb4CountersGfx10,
        &kDb5CountersGfx10,
        &kDb6CountersGfx10,
        &kDb7CountersGfx10,
        &kDb8CountersGfx10,
        &kDb9CountersGfx10,
        &kDb10CountersGfx10,
        &kDb11CountersGfx10,
        &kDb12CountersGfx10,
        &kDb13CountersGfx10,
        &kDb14CountersGfx10,
        &kDb15CountersGfx10,
        &kGrbmCountersGfx10,
        &kPaSu0CountersGfx10,
        &kPaSu1CountersGfx10,
        &kPaSu2CountersGfx10,
        &kPaSu3CountersGfx10,
        &kPaSc0CountersGfx10,
        &kPaSc1CountersGfx10,
        &kPaSc2CountersGfx10,
        &kPaSc3CountersGfx10,
        &kPaSc4CountersGfx10,
        &kPaSc5CountersGfx10,
        &kPaSc6CountersGfx10,
        &kPaSc7CountersGfx10,
        &kSx0CountersGfx10,
        &kSx1CountersGfx10,
        &kSx2CountersGfx10,
        &kSx3CountersGfx10,
        &kSpi0CountersGfx10,
        &kSpi1CountersGfx10,
        &kSq0CountersGfx10,
        &kSq1CountersGfx10,
        &kSqEs0CountersGfx10,
        &kSqEs1CountersGfx10,
        &kSqGs0CountersGfx10,
        &kSqGs1CountersGfx10,
        &kSqVs0CountersGfx10,
        &kSqVs1CountersGfx10,
        &kSqPs0CountersGfx10,
        &kSqPs1CountersGfx10,
        &kSqLs0CountersGfx10,
        &kSqLs1CountersGfx10,
        &kSqHs0CountersGfx10,
        &kSqHs1CountersGfx10,
        &kSqCs0CountersGfx10,
        &kSqCs1CountersGfx10,
        &kTa0CountersGfx10,
        &kTa1CountersGfx10,
        &kTa2CountersGfx10,
        &kTa3CountersGfx10,
        &kTa4CountersGfx10,
        &kTa5CountersGfx10,
        &kTa6CountersGfx10,
        &kTa7CountersGfx10,
        &kTa8CountersGfx10,
        &kTa9CountersGfx10,
        &kTa10CountersGfx10,
        &kTa11CountersGfx10,
        &kTa12CountersGfx10,
        &kTa13CountersGfx10,
        &kTa14CountersGfx10,
        &kTa15CountersGfx10,
        &kTa16CountersGfx10,
        &kTa17CountersGfx10,
        &kTa18CountersGfx10,
        &kTa19CountersGfx10,
        &kTa20CountersGfx10,
        &kTa21CountersGfx10,
        &kTa22CountersGfx10,
        &kTa23CountersGfx10,
        &kTa24CountersGfx10,
        &kTa25CountersGfx10,
        &kTa26CountersGfx10,
        &kTa27CountersGfx10,
        &kTa28CountersGfx10,
        &kTa29CountersGfx10,
        &kTa30CountersGfx10,
        &kTa31CountersGfx10,
        &kTa32CountersGfx10,
        &kTa33CountersGfx10,
        &kTa34CountersGfx10,
        &kTa35CountersGfx10,
        &kTa36CountersGfx10,
        &kTa37CountersGfx10,
        &kTa38CountersGfx10,
        &kTa39CountersGfx10,
        &kTcp0CountersGfx10,
        &kTcp1CountersGfx10,
        &kTcp2CountersGfx10,
        &kTcp3CountersGfx10,
        &kTcp4CountersGfx10,
        &kTcp5CountersGfx10,
        &kTcp6CountersGfx10,
        &kTcp7CountersGfx10,
        &kTcp8CountersGfx10,
        &kTcp9CountersGfx10,
        &kTcp10CountersGfx10,
        &kTcp11CountersGfx10,
        &kTcp12CountersGfx10,
        &kTcp13CountersGfx10,
        &kTcp14CountersGfx10,
        &kTcp15CountersGfx10,
        &kTcp16CountersGfx10,
        &kTcp17CountersGfx10,
        &kTcp18CountersGfx10,
        &kTcp19CountersGfx10,
        &kTcp20CountersGfx10,
        &kTcp21CountersGfx10,
        &kTcp22CountersGfx10,
        &kTcp23CountersGfx10,
        &kTcp24CountersGfx10,
        &kTcp25CountersGfx10,
        &kTcp26CountersGfx10,
        &kTcp27CountersGfx10,
        &kTcp28CountersGfx10,
        &kTcp29CountersGfx10,
        &kTcp30CountersGfx10,
        &kTcp31CountersGfx10,
        &kTcp32CountersGfx10,
        &kTcp33CountersGfx10,
        &kTcp34CountersGfx10,
        &kTcp35CountersGfx10,
        &kTcp36CountersGfx10,
        &kTcp37CountersGfx10,
        &kTcp38CountersGfx10,
        &kTcp39CountersGfx10,
        &kGcea0CountersGfx10,
        &kGcea1CountersGfx10,
        &kGcea2CountersGfx10,
        &kGcea3CountersGfx10,
        &kGcea4CountersGfx10,
        &kGcea5CountersGfx10,
        &kGcea6CountersGfx10,
        &kGcea7CountersGfx10,
        &kGcea8CountersGfx10,
        &kGcea9CountersGfx10,
        &kGcea10CountersGfx10,
        &kGcea11CountersGfx10,
        &kGcea12CountersGfx10,
        &kGcea13CountersGfx10,
        &kGcea14CountersGfx10,
        &kGcea15CountersGfx10,
        &kGeCountersGfx10,
        &kGl1c0CountersGfx10,
        &kGl1c1CountersGfx10,
        &kGl1c2CountersGfx10,
        &kGl1c3CountersGfx10,
        &kGl1c4CountersGfx10,
        &kGl1c5CountersGfx10,
        &kGl1c6CountersGfx10,
        &kGl1c7CountersGfx10,
        &kGl1c8CountersGfx10,
        &kGl1c9CountersGfx10,
        &kGl1c10CountersGfx10,
        &kGl1c11CountersGfx10,
        &kGl1c12CountersGfx10,
        &kGl1c13CountersGfx10,
        &kGl1c14CountersGfx10,
        &kGl1c15CountersGfx10,
        &kGl2c0CountersGfx10,
        &kGl2c1CountersGfx10,
        &kGl2c2CountersGfx10,
        &kGl2c3CountersGfx10,
        &kGl2c4CountersGfx10,
        &kGl2c5CountersGfx10,
        &kGl2c6CountersGfx10,
        &kGl2c7CountersGfx10,
        &kGl2c8CountersGfx10,
        &kGl2c9CountersGfx10,
        &kGl2c10CountersGfx10,
        &kGl2c11CountersGfx10,
        &kGl2c12CountersGfx10,
        &kGl2c13CountersGfx10,
        &kGl2c14CountersGfx10,
        &kGl2c15CountersGfx10,
        &kGl2c16CountersGfx10,
        &kGl2c17CountersGfx10,
        &kGl2c18CountersGfx10,
        &kGl2c19CountersGfx10,
        &kGl2c20CountersGfx10,
        &kGl2c21CountersGfx10,
        &kGl2c22CountersGfx10,
        &kGl2c23CountersGfx10,
        &kGpuTimeCountersGfx10,
    };


    std::vector<GpaCounterGroupDesc> kHwDx11GroupsGfx10 = {
        {0, "CPF", 0, 40, 2, 4},
        {1, "CB0", 0, 461, 4, 4},
        {2, "CB1", 1, 461, 4, 4},
        {3, "CB2", 2, 461, 4, 4},
        {4, "CB3", 3, 461, 4, 4},
        {5, "CB4", 4, 461, 4, 4},
        {6, "CB5", 5, 461, 4, 4},
        {7, "CB6", 6, 461, 4, 4},
        {8, "CB7", 7, 461, 4, 4},
        {9, "CB8", 8, 461, 4, 4},
        {10, "CB9", 9, 461, 4, 4},
        {11, "CB10", 10, 461, 4, 4},
        {12, "CB11", 11, 461, 4, 4},
        {13, "CB12", 12, 461, 4, 4},
        {14, "CB13", 13, 461, 4, 4},
        {15, "CB14", 14, 461, 4, 4},
        {16, "CB15", 15, 461, 4, 4},
        {17, "DB0", 0, 370, 4, 8},
        {18, "DB1", 1, 370, 4, 8},
        {19, "DB2", 2, 370, 4, 8},
        {20, "DB3", 3, 370, 4, 8},
        {21, "DB4", 4, 370, 4, 8},
        {22, "DB5", 5, 370, 4, 8},
        {23, "DB6", 6, 370, 4, 8},
        {24, "DB7", 7, 370, 4, 8},
        {25, "DB8", 8, 370, 4, 8},
        {26, "DB9", 9, 370, 4, 8},
        {27, "DB10", 10, 370, 4, 8},
        {28, "DB11", 11, 370, 4, 8},
        {29, "DB12", 12, 370, 4, 8},
        {30, "DB13", 13, 370, 4, 8},
        {31, "DB14", 14, 370, 4, 8},
        {32, "DB15", 15, 370, 4, 8},
        {33, "GRBM", 0, 47, 2, 0},
        {34, "GRBMSE0", 0, 19, 4, 0},
        {35, "GRBMSE1", 1, 19, 4, 0},
        {36, "RLC", 0, 7, 2, 0},
        {37, "PA_SU0", 0, 266, 4, 16},
        {38, "PA_SU1", 1, 266, 4, 16},
        {39, "PA_SU2", 2, 266, 4, 16},
        {40, "PA_SU3", 3, 266, 4, 16},
        {41, "PA_SC0", 0, 552, 8, 4},
        {42, "PA_SC1", 1, 552, 8, 4},
        {43, "PA_SC2", 2, 552, 8, 4},
        {44, "PA_SC3", 3, 552, 8, 4},
        {45, "PA_SC4", 4, 552, 8, 4},
        {46, "PA_SC5", 5, 552, 8, 4},
        {47, "PA_SC6", 6, 552, 8, 4},
        {48, "PA_SC7", 7, 552, 8, 4},
        {49, "SX0", 0, 225, 4, 8},
        {50, "SX1", 1, 225, 4, 8},
        {51, "SX2", 2, 225, 4, 8},
        {52, "SX3", 3, 225, 4, 8},
        {53, "SPI0", 0, 329, 6, 16},
        {54, "SPI1", 1, 329, 6, 16},
        {55, "SQ0", 0, 512, 16, 16},
        {56, "SQ1", 1, 512, 16, 16},
        {57, "SQ_ES0", 0, 512, 16, 16},
        {58, "SQ_ES1", 1, 512, 16, 16},
        {59, "SQ_GS0", 0, 512, 16, 16},
        {60, "SQ_GS1", 1, 512, 16, 16},
        {61, "SQ_VS0", 0, 512, 16, 16},
        {62, "SQ_VS1", 1, 512, 16, 16},
        {63, "SQ_PS0", 0, 512, 16, 16},
        {64, "SQ_PS1", 1, 512, 16, 16},
        {65, "SQ_LS0", 0, 512, 16, 16},
        {66, "SQ_LS1", 1, 512, 16, 16},
        {67, "SQ_HS0", 0, 512, 16, 16},
        {68, "SQ_HS1", 1, 512, 16, 16},
        {69, "SQ_CS0", 0, 512, 16, 16},
        {70, "SQ_CS1", 1, 512, 16, 16},
        {71, "TA0", 0, 226, 2, 4},
        {72, "TA1", 1, 226, 2, 4},
        {73, "TA2", 2, 226, 2, 4},
        {74, "TA3", 3, 226, 2, 4},
        {75, "TA4", 4, 226, 2, 4},
        {76, "TA5", 5, 226, 2, 4},
        {77, "TA6", 6, 226, 2, 4},
        {78, "TA7", 7, 226, 2, 4},
        {79, "TA8", 8, 226, 2, 4},
        {80, "TA9", 9, 226, 2, 4},
        {81, "TA10", 10, 226, 2, 4},
        {82, "TA11", 11, 226, 2, 4},
        {83, "TA12", 12, 226, 2, 4},
        {84, "TA13", 13, 226, 2, 4},
        {85, "TA14", 14, 226, 2, 4},
        {86, "TA15", 15, 226, 2, 4},
        {87, "TA16", 16, 226, 2, 4},
        {88, "TA17", 17, 226, 2, 4},
        {89, "TA18", 18, 226, 2, 4},
        {90, "TA19", 19, 226, 2, 4},
        {91, "TA20", 20, 226, 2, 4},
        {92, "TA21", 21, 226, 2, 4},
        {93, "TA22", 22, 226, 2, 4},
        {94, "TA23", 23, 226, 2, 4},
        {95, "TA24", 24, 226, 2, 4},
        {96, "TA25", 25, 226, 2, 4},
        {97, "TA26", 26, 226, 2, 4},
        {98, "TA27", 27, 226, 2, 4},
        {99, "TA28", 28, 226, 2, 4},
        {100, "TA29", 29, 226, 2, 4},
        {101, "TA30", 30, 226, 2, 4},
        {102, "TA31", 31, 226, 2, 4},
        {103, "TA32", 32, 226, 2, 4},
        {104, "TA33", 33, 226, 2, 4},
        {105, "TA34", 34, 226, 2, 4},
        {106, "TA35", 35, 226, 2, 4},
        {107, "TA36", 36, 226, 2, 4},
        {108, "TA37", 37, 226, 2, 4},
        {109, "TA38", 38, 226, 2, 4},
        {110, "TA39", 39, 226, 2, 4},
        {111, "TD0", 0, 61, 2, 4},
        {112, "TD1", 1, 61, 2, 4},
        {113, "TD2", 2, 61, 2, 4},
        {114, "TD3", 3, 61, 2, 4},
        {115, "TD4", 4, 61, 2, 4},
        {116, "TD5", 5, 61, 2, 4},
        {117, "TD6", 6, 61, 2, 4},
        {118, "TD7", 7, 61, 2, 4},
        {119, "TD8", 8, 61, 2, 4},
        {120, "TD9", 9, 61, 2, 4},
        {121, "TD10", 10, 61, 2, 4},
        {122, "TD11", 11, 61, 2, 4},
        {123, "TD12", 12, 61, 2, 4},
        {124, "TD13", 13, 61, 2, 4},
        {125, "TD14", 14, 61, 2, 4},
        {126, "TD15", 15, 61, 2, 4},
        {127, "TD16", 16, 61, 2, 4},
        {128, "TD17", 17, 61, 2, 4},
        {129, "TD18", 18, 61, 2, 4},
        {130, "TD19", 19, 61, 2, 4},
        {131, "TD20", 20, 61, 2, 4},
        {132, "TD21", 21, 61, 2, 4},
        {133, "TD22", 22, 61, 2, 4},
        {134, "TD23", 23, 61, 2, 4},
        {135, "TD24", 24, 61, 2, 4},
        {136, "TD25", 25, 61, 2, 4},
        {137, "TD26", 26, 61, 2, 4},
        {138, "TD27", 27, 61, 2, 4},
        {139, "TD28", 28, 61, 2, 4},
        {140, "TD29", 29, 61, 2, 4},
        {141, "TD30", 30, 61, 2, 4},
        {142, "TD31", 31, 61, 2, 4},
        {143, "TD32", 32, 61, 2, 4},
        {144, "TD33", 33, 61, 2, 4},
        {145, "TD34", 34, 61, 2, 4},
        {146, "TD35", 35, 61, 2, 4},
        {147, "TD36", 36, 61, 2, 4},
        {148, "TD37", 37, 61, 2, 4},
        {149, "TD38", 38, 61, 2, 4},
        {150, "TD39", 39, 61, 2, 4},
        {151, "TCP0", 0, 77, 4, 8},
        {152, "TCP1", 1, 77, 4, 8},
        {153, "TCP2", 2, 77, 4, 8},
        {154, "TCP3", 3, 77, 4, 8},
        {155, "TCP4", 4, 77, 4, 8},
        {156, "TCP5", 5, 77, 4, 8},
        {157, "TCP6", 6, 77, 4, 8},
        {158, "TCP7", 7, 77, 4, 8},
        {159, "TCP8", 8, 77, 4, 8},
        {160, "TCP9", 9, 77, 4, 8},
        {161, "TCP10", 10, 77, 4, 8},
        {162, "TCP11", 11, 77, 4, 8},
        {163, "TCP12", 12, 77, 4, 8},
        {164, "TCP13", 13, 77, 4, 8},
        {165, "TCP14", 14, 77, 4, 8},
        {166, "TCP15", 15, 77, 4, 8},
        {167, "TCP16", 16, 77, 4, 8},
        {168, "TCP17", 17, 77, 4, 8},
        {169, "TCP18", 18, 77, 4, 8},
        {170, "TCP19", 19, 77, 4, 8},
        {171, "TCP20", 20, 77, 4, 8},
        {172, "TCP21", 21, 77, 4, 8},
        {173, "TCP22", 22, 77, 4, 8},
        {174, "TCP23", 23, 77, 4, 8},
        {175, "TCP24", 24, 77, 4, 8},
        {176, "TCP25", 25, 77, 4, 8},
        {177, "TCP26", 26, 77, 4, 8},
        {178, "TCP27", 27, 77, 4, 8},
        {179, "TCP28", 28, 77, 4, 8},
        {180, "TCP29", 29, 77, 4, 8},
        {181, "TCP30", 30, 77, 4, 8},
        {182, "TCP31", 31, 77, 4, 8},
        {183, "TCP32", 32, 77, 4, 8},
        {184, "TCP33", 33, 77, 4, 8},
        {185, "TCP34", 34, 77, 4, 8},
        {186, "TCP35", 35, 77, 4, 8},
        {187, "TCP36", 36, 77, 4, 8},
        {188, "TCP37", 37, 77, 4, 8},
        {189, "TCP38", 38, 77, 4, 8},
        {190, "TCP39", 39, 77, 4, 8},
        {191, "GDS", 0, 123, 4, 4},
        {192, "CPG", 0, 82, 2, 4},
        {193, "CPC", 0, 47, 2, 4},
        {194, "MCVML2", 0, 21, 8, 0},
        {195, "ATC", 0, 24, 4, 0},
        {196, "ATCL2", 0, 12, 2, 4},
        {197, "RPB", 0, 63, 4, 0},
        {198, "GCEA0", 0, 89, 2, 4},
        {199, "GCEA1", 1, 89, 2, 4},
        {200, "GCEA2", 2, 89, 2, 4},
        {201, "GCEA3", 3, 89, 2, 4},
        {202, "GCEA4", 4, 89, 2, 4},
        {203, "GCEA5", 5, 89, 2, 4},
        {204, "GCEA6", 6, 89, 2, 4},
        {205, "GCEA7", 7, 89, 2, 4},
        {206, "GCEA8", 8, 89, 2, 4},
        {207, "GCEA9", 9, 89, 2, 4},
        {208, "GCEA10", 10, 89, 2, 4},
        {209, "GCEA11", 11, 89, 2, 4},
        {210, "GCEA12", 12, 89, 2, 4},
        {211, "GCEA13", 13, 89, 2, 4},
        {212, "GCEA14", 14, 89, 2, 4},
        {213, "GCEA15", 15, 89, 2, 4},
        {214, "RMI0", 0, 258, 4, 4},
        {215, "RMI1", 1, 258, 4, 4},
        {216, "RMI2", 2, 258, 4, 4},
        {217, "RMI3", 3, 258, 4, 4},
        {218, "RMI4", 4, 258, 4, 4},
        {219, "RMI5", 5, 258, 4, 4},
        {220, "RMI6", 6, 258, 4, 4},
        {221, "RMI7", 7, 258, 4, 4},
        {222, "RMI8", 8, 258, 4, 4},
        {223, "RMI9", 9, 258, 4, 4},
        {224, "RMI10", 10, 258, 4, 4},
        {225, "RMI11", 11, 258, 4, 4},
        {226, "RMI12", 12, 258, 4, 4},
        {227, "RMI13", 13, 258, 4, 4},
        {228, "RMI14", 14, 258, 4, 4},
        {229, "RMI15", 15, 258, 4, 4},
        {230, "CHA", 0, 45, 4, 4},
        {231, "CHC0", 0, 35, 4, 4},
        {232, "CHC1", 1, 35, 4, 4},
        {233, "CHC2", 2, 35, 4, 4},
        {234, "CHC3", 3, 35, 4, 4},
        {235, "CHCG", 0, 35, 4, 4},
        {236, "GCR", 0, 94, 2, 4},
        {237, "GE", 0, 315, 12, 16},
        {238, "GL1A0", 0, 36, 4, 4},
        {239, "GL1A1", 1, 36, 4, 4},
        {240, "GL1A2", 2, 36, 4, 4},
        {241, "GL1A3", 3, 36, 4, 4},
        {242, "GL1A4", 4, 36, 4, 4},
        {243, "GL1A5", 5, 36, 4, 4},
        {244, "GL1A6", 6, 36, 4, 4},
        {245, "GL1A7", 7, 36, 4, 4},
        {246, "GL1C0", 0, 64, 4, 4},
        {247, "GL1C1", 1, 64, 4, 4},
        {248, "GL1C2", 2, 64, 4, 4},
        {249, "GL1C3", 3, 64, 4, 4},
        {250, "GL1C4", 4, 64, 4, 4},
        {251, "GL1C5", 5, 64, 4, 4},
        {252, "GL1C6", 6, 64, 4, 4},
        {253, "GL1C7", 7, 64, 4, 4},
        {254, "GL1C8", 8, 64, 4, 4},
        {255, "GL1C9", 9, 64, 4, 4},
        {256, "GL1C10", 10, 64, 4, 4},
        {257, "GL1C11", 11, 64, 4, 4},
        {258, "GL1C12", 12, 64, 4, 4},
        {259, "GL1C13", 13, 64, 4, 4},
        {260, "GL1C14", 14, 64, 4, 4},
        {261, "GL1C15", 15, 64, 4, 4},
        {262, "GL1CG0", 0, 38, 4, 0},
        {263, "GL1CG1", 1, 38, 4, 0},
        {264, "GL1CG2", 2, 38, 4, 0},
        {265, "GL1CG3", 3, 38, 4, 0},
        {266, "GL1CG4", 4, 38, 4, 0},
        {267, "GL1CG5", 5, 38, 4, 0},
        {268, "GL1CG6", 6, 38, 4, 0},
        {269, "GL1CG7", 7, 38, 4, 0},
        {270, "GL1CG8", 8, 38, 4, 0},
        {271, "GL1CG9", 9, 38, 4, 0},
        {272, "GL1CG10", 10, 38, 4, 0},
        {273, "GL1CG11", 11, 38, 4, 0},
        {274, "GL1CG12", 12, 38, 4, 0},
        {275, "GL1CG13", 13, 38, 4, 0},
        {276, "GL1CG14", 14, 38, 4, 0},
        {277, "GL1CG15", 15, 38, 4, 0},
        {278, "GL2A0", 0, 91, 4, 8},
        {279, "GL2A1", 1, 91, 4, 8},
        {280, "GL2A2", 2, 91, 4, 8},
        {281, "GL2A3", 3, 91, 4, 8},
        {282, "GL2C0", 0, 235, 4, 8},
        {283, "GL2C1", 1, 235, 4, 8},
        {284, "GL2C2", 2, 235, 4, 8},
        {285, "GL2C3", 3, 235, 4, 8},
        {286, "GL2C4", 4, 235, 4, 8},
        {287, "GL2C5", 5, 235, 4, 8},
        {288, "GL2C6", 6, 235, 4, 8},
        {289, "GL2C7", 7, 235, 4, 8},
        {290, "GL2C8", 8, 235, 4, 8},
        {291, "GL2C9", 9, 235, 4, 8},
        {292, "GL2C10", 10, 235, 4, 8},
        {293, "GL2C11", 11, 235, 4, 8},
        {294, "GL2C12", 12, 235, 4, 8},
        {295, "GL2C13", 13, 235, 4, 8},
        {296, "GL2C14", 14, 235, 4, 8},
        {297, "GL2C15", 15, 235, 4, 8},
        {298, "GL2C16", 16, 235, 4, 8},
        {299, "GL2C17", 17, 235, 4, 8},
        {300, "GL2C18", 18, 235, 4, 8},
        {301, "GL2C19", 19, 235, 4, 8},
        {302, "GL2C20", 20, 235, 4, 8},
        {303, "GL2C21", 21, 235, 4, 8},
        {304, "GL2C22", 22, 235, 4, 8},
        {305, "GL2C23", 23, 235, 4, 8},
        {306, "GUS", 0, 176, 2, 4},
        {307, "PA_PH", 0, 960, 8, 16},
        {308, "UTCL10", 0, 15, 2, 0},
        {309, "UTCL11", 1, 15, 2, 0},
        {310, "UTCL12", 2, 15, 2, 0},
        {311, "UTCL13", 3, 15, 2, 0},
        {312, "GPUTimeStamp", 0, 1, 1, 0},
        {313, "GPUTime", 0, 6, 3, 0},
    };

    GpaCounterGroupExposedCounterDesc kHwDx11ExposedCountersByGroupGfx10[] = {
        {0, 0},
        {1, 40},
        {2, 501},
        {3, 962},
        {4, 1423},
        {5, 1884},
        {6, 2345},
        {7, 2806},
        {8, 3267},
        {9, 3728},
        {10, 4189},
        {11, 4650},
        {12, 5111},
        {13, 5572},
        {14, 6033},
        {15, 6494},
        {16, 6955},
        {17, 7416},
        {18, 7786},
        {19, 8156},
        {20, 8526},
        {21, 8896},
        {22, 9266},
        {23, 9636},
        {24, 10006},
        {25, 10376},
        {26, 10746},
        {27, 11116},
        {28, 11486},
        {29, 11856},
        {30, 12226},
        {31, 12596},
        {32, 12966},
        {33, 13336},
        {37, 13428},
        {38, 13694},
        {39, 13960},
        {40, 14226},
        {41, 14492},
        {42, 15044},
        {43, 15596},
        {44, 16148},
        {45, 16700},
        {46, 17252},
        {47, 17804},
        {48, 18356},
        {49, 18908},
        {50, 19133},
        {51, 19358},
        {52, 19583},
        {53, 19808},
        {54, 20137},
        {55, 20466},
        {56, 20978},
        {57, 21490},
        {58, 22002},
        {59, 22514},
        {60, 23026},
        {61, 23538},
        {62, 24050},
        {63, 24562},
        {64, 25074},
        {65, 25586},
        {66, 26098},
        {67, 26610},
        {68, 27122},
        {69, 27634},
        {70, 28146},
        {71, 28658},
        {72, 28884},
        {73, 29110},
        {74, 29336},
        {75, 29562},
        {76, 29788},
        {77, 30014},
        {78, 30240},
        {79, 30466},
        {80, 30692},
        {81, 30918},
        {82, 31144},
        {83, 31370},
        {84, 31596},
        {85, 31822},
        {86, 32048},
        {87, 32274},
        {88, 32500},
        {89, 32726},
        {90, 32952},
        {91, 33178},
        {92, 33404},
        {93, 33630},
        {94, 33856},
        {95, 34082},
        {96, 34308},
        {97, 34534},
        {98, 34760},
        {99, 34986},
        {100, 35212},
        {101, 35438},
        {102, 35664},
        {103, 35890},
        {104, 36116},
        {105, 36342},
        {106, 36568},
        {107, 36794},
        {108, 37020},
        {109, 37246},
        {110, 37472},
        {151, 40138},
        {152, 40215},
        {153, 40292},
        {154, 40369},
        {155, 40446},
        {156, 40523},
        {157, 40600},
        {158, 40677},
        {159, 40754},
        {160, 40831},
        {161, 40908},
        {162, 40985},
        {163, 41062},
        {164, 41139},
        {165, 41216},
        {166, 41293},
        {167, 41370},
        {168, 41447},
        {169, 41524},
        {170, 41601},
        {171, 41678},
        {172, 41755},
        {173, 41832},
        {174, 41909},
        {175, 41986},
        {176, 42063},
        {177, 42140},
        {178, 42217},
        {179, 42294},
        {180, 42371},
        {181, 42448},
        {182, 42525},
        {183, 42602},
        {184, 42679},
        {185, 42756},
        {186, 42833},
        {187, 42910},
        {188, 42987},
        {189, 43064},
        {190, 43141},
        {198, 43590},
        {199, 43679},
        {200, 43768},
        {201, 43857},
        {202, 43946},
        {203, 44035},
        {204, 44124},
        {205, 44213},
        {206, 44302},
        {207, 44391},
        {208, 44480},
        {209, 44569},
        {210, 44658},
        {211, 44747},
        {212, 44836},
        {213, 44925},
        {237, 49456},
        {246, 50059},
        {247, 50123},
        {248, 50187},
        {249, 50251},
        {250, 50315},
        {251, 50379},
        {252, 50443},
        {253, 50507},
        {254, 50571},
        {255, 50635},
        {256, 50699},
        {257, 50763},
        {258, 50827},
        {259, 50891},
        {260, 50955},
        {261, 51019},
        {282, 52055},
        {283, 52290},
        {284, 52525},
        {285, 52760},
        {286, 52995},
        {287, 53230},
        {288, 53465},
        {289, 53700},
        {290, 53935},
        {291, 54170},
        {292, 54405},
        {293, 54640},
        {294, 54875},
        {295, 55110},
        {296, 55345},
        {297, 55580},
        {298, 55815},
        {299, 56050},
        {300, 56285},
        {301, 56520},
        {302, 56755},
        {303, 56990},
        {304, 57225},
        {305, 57460},
        {313, 58892},
    };

    GpaPaddedCounterDesc kDx11PaddedCounterByGroupGfx10[] = {
    {}
    };

    GpaSqCounterGroupDesc kHwDx11SqGroupsGfx10[] = {
        {55, 0, kSqAll},
        {56, 1, kSqAll},
        {57, 0, kSqEs},
        {58, 1, kSqEs},
        {59, 0, kSqGs},
        {60, 1, kSqGs},
        {61, 0, kSqVs},
        {62, 1, kSqVs},
        {63, 0, kSqPs},
        {64, 1, kSqPs},
        {65, 0, kSqLs},
        {66, 1, kSqLs},
        {67, 0, kSqHs},
        {68, 1, kSqHs},
        {69, 0, kSqCs},
        {70, 1, kSqCs},
    };


    unsigned int kHwDx11SqIsolatedGroupsGfx10[] = {
        71, // Ta
        72, // Ta
        73, // Ta
        74, // Ta
        75, // Ta
        76, // Ta
        77, // Ta
        78, // Ta
        79, // Ta
        80, // Ta
        81, // Ta
        82, // Ta
        83, // Ta
        84, // Ta
        85, // Ta
        86, // Ta
        87, // Ta
        88, // Ta
        89, // Ta
        90, // Ta
        91, // Ta
        92, // Ta
        93, // Ta
        94, // Ta
        95, // Ta
        96, // Ta
        97, // Ta
        98, // Ta
        99, // Ta
        100, // Ta
        101, // Ta
        102, // Ta
        103, // Ta
        104, // Ta
        105, // Ta
        106, // Ta
        107, // Ta
        108, // Ta
        109, // Ta
        110, // Ta
        111, // Td
        112, // Td
        113, // Td
        114, // Td
        115, // Td
        116, // Td
        117, // Td
        118, // Td
        119, // Td
        120, // Td
        121, // Td
        122, // Td
        123, // Td
        124, // Td
        125, // Td
        126, // Td
        127, // Td
        128, // Td
        129, // Td
        130, // Td
        131, // Td
        132, // Td
        133, // Td
        134, // Td
        135, // Td
        136, // Td
        137, // Td
        138, // Td
        139, // Td
        140, // Td
        141, // Td
        142, // Td
        143, // Td
        144, // Td
        145, // Td
        146, // Td
        147, // Td
        148, // Td
        149, // Td
        150, // Td
        151, // Tcp
        152, // Tcp
        153, // Tcp
        154, // Tcp
        155, // Tcp
        156, // Tcp
        157, // Tcp
        158, // Tcp
        159, // Tcp
        160, // Tcp
        161, // Tcp
        162, // Tcp
        163, // Tcp
        164, // Tcp
        165, // Tcp
        166, // Tcp
        167, // Tcp
        168, // Tcp
        169, // Tcp
        170, // Tcp
        171, // Tcp
        172, // Tcp
        173, // Tcp
        174, // Tcp
        175, // Tcp
        176, // Tcp
        177, // Tcp
        178, // Tcp
        179, // Tcp
        180, // Tcp
        181, // Tcp
        182, // Tcp
        183, // Tcp
        184, // Tcp
        185, // Tcp
        186, // Tcp
        187, // Tcp
        188, // Tcp
        189, // Tcp
        190, // Tcp
    };

    PE_BLOCK_ID kHwDx11DriverEnumGfx10[] = {
    PE_BLOCK_CPF,
    PE_BLOCK_CB,
    PE_BLOCK_CB,
    PE_BLOCK_CB,
    PE_BLOCK_CB,
    PE_BLOCK_CB,
    PE_BLOCK_CB,
    PE_BLOCK_CB,
    PE_BLOCK_CB,
    PE_BLOCK_CB,
    PE_BLOCK_CB,
    PE_BLOCK_CB,
    PE_BLOCK_CB,
    PE_BLOCK_CB,
    PE_BLOCK_CB,
    PE_BLOCK_CB,
    PE_BLOCK_CB,
    PE_BLOCK_DB,
    PE_BLOCK_DB,
    PE_BLOCK_DB,
    PE_BLOCK_DB,
    PE_BLOCK_DB,
    PE_BLOCK_DB,
    PE_BLOCK_DB,
    PE_BLOCK_DB,
    PE_BLOCK_DB,
    PE_BLOCK_DB,
    PE_BLOCK_DB,
    PE_BLOCK_DB,
    PE_BLOCK_DB,
    PE_BLOCK_DB,
    PE_BLOCK_DB,
    PE_BLOCK_DB,
    PE_BLOCK_GRBM,
    PE_BLOCK_GRBMSE,
    PE_BLOCK_GRBMSE,
    PE_BLOCK_RLC,
    PE_BLOCK_PA,
    PE_BLOCK_PA,
    PE_BLOCK_PA,
    PE_BLOCK_PA,
    PE_BLOCK_SC,
    PE_BLOCK_SC,
    PE_BLOCK_SC,
    PE_BLOCK_SC,
    PE_BLOCK_SC,
    PE_BLOCK_SC,
    PE_BLOCK_SC,
    PE_BLOCK_SC,
    PE_BLOCK_SX,
    PE_BLOCK_SX,
    PE_BLOCK_SX,
    PE_BLOCK_SX,
    PE_BLOCK_SPI,
    PE_BLOCK_SPI,
    PE_BLOCK_SQ,
    PE_BLOCK_SQ,
    PE_BLOCK_SQ,
    PE_BLOCK_SQ,
    PE_BLOCK_SQ,
    PE_BLOCK_SQ,
    PE_BLOCK_SQ,
    PE_BLOCK_SQ,
    PE_BLOCK_SQ,
    PE_BLOCK_SQ,
    PE_BLOCK_SQ,
    PE_BLOCK_SQ,
    PE_BLOCK_SQ,
    PE_BLOCK_SQ,
    PE_BLOCK_SQ,
    PE_BLOCK_SQ,
    PE_BLOCK_TA,
    PE_BLOCK_TA,
    PE_BLOCK_TA,
    PE_BLOCK_TA,
    PE_BLOCK_TA,
    PE_BLOCK_TA,
    PE_BLOCK_TA,
    PE_BLOCK_TA,
    PE_BLOCK_TA,
    PE_BLOCK_TA,
    PE_BLOCK_TA,
    PE_BLOCK_TA,
    PE_BLOCK_TA,
    PE_BLOCK_TA,
    PE_BLOCK_TA,
    PE_BLOCK_TA,
    PE_BLOCK_TA,
    PE_BLOCK_TA,
    PE_BLOCK_TA,
    PE_BLOCK_TA,
    PE_BLOCK_TA,
    PE_BLOCK_TA,
    PE_BLOCK_TA,
    PE_BLOCK_TA,
    PE_BLOCK_TA,
    PE_BLOCK_TA,
    PE_BLOCK_TA,
    PE_BLOCK_TA,
    PE_BLOCK_TA,
    PE_BLOCK_TA,
    PE_BLOCK_TA,
    PE_BLOCK_TA,
    PE_BLOCK_TA,
    PE_BLOCK_TA,
    PE_BLOCK_TA,
    PE_BLOCK_TA,
    PE_BLOCK_TA,
    PE_BLOCK_TA,
    PE_BLOCK_TA,
    PE_BLOCK_TA,
    PE_BLOCK_TD,
    PE_BLOCK_TD,
    PE_BLOCK_TD,
    PE_BLOCK_TD,
    PE_BLOCK_TD,
    PE_BLOCK_TD,
    PE_BLOCK_TD,
    PE_BLOCK_TD,
    PE_BLOCK_TD,
    PE_BLOCK_TD,
    PE_BLOCK_TD,
    PE_BLOCK_TD,
    PE_BLOCK_TD,
    PE_BLOCK_TD,
    PE_BLOCK_TD,
    PE_BLOCK_TD,
    PE_BLOCK_TD,
    PE_BLOCK_TD,
    PE_BLOCK_TD,
    PE_BLOCK_TD,
    PE_BLOCK_TD,
    PE_BLOCK_TD,
    PE_BLOCK_TD,
    PE_BLOCK_TD,
    PE_BLOCK_TD,
    PE_BLOCK_TD,
    PE_BLOCK_TD,
    PE_BLOCK_TD,
    PE_BLOCK_TD,
    PE_BLOCK_TD,
    PE_BLOCK_TD,
    PE_BLOCK_TD,
    PE_BLOCK_TD,
    PE_BLOCK_TD,
    PE_BLOCK_TD,
    PE_BLOCK_TD,
    PE_BLOCK_TD,
    PE_BLOCK_TD,
    PE_BLOCK_TD,
    PE_BLOCK_TD,
    PE_BLOCK_TCP,
    PE_BLOCK_TCP,
    PE_BLOCK_TCP,
    PE_BLOCK_TCP,
    PE_BLOCK_TCP,
    PE_BLOCK_TCP,
    PE_BLOCK_TCP,
    PE_BLOCK_TCP,
    PE_BLOCK_TCP,
    PE_BLOCK_TCP,
    PE_BLOCK_TCP,
    PE_BLOCK_TCP,
    PE_BLOCK_TCP,
    PE_BLOCK_TCP,
    PE_BLOCK_TCP,
    PE_BLOCK_TCP,
    PE_BLOCK_TCP,
    PE_BLOCK_TCP,
    PE_BLOCK_TCP,
    PE_BLOCK_TCP,
    PE_BLOCK_TCP,
    PE_BLOCK_TCP,
    PE_BLOCK_TCP,
    PE_BLOCK_TCP,
    PE_BLOCK_TCP,
    PE_BLOCK_TCP,
    PE_BLOCK_TCP,
    PE_BLOCK_TCP,
    PE_BLOCK_TCP,
    PE_BLOCK_TCP,
    PE_BLOCK_TCP,
    PE_BLOCK_TCP,
    PE_BLOCK_TCP,
    PE_BLOCK_TCP,
    PE_BLOCK_TCP,
    PE_BLOCK_TCP,
    PE_BLOCK_TCP,
    PE_BLOCK_TCP,
    PE_BLOCK_TCP,
    PE_BLOCK_TCP,
    PE_BLOCK_GDS,
    PE_BLOCK_CPG,
    PE_BLOCK_CPC,
    PE_BLOCK_MCVML2,
    PE_BLOCK_ATC,
    PE_BLOCK_ATCL2,
    PE_BLOCK_RPB,
    PE_BLOCK_EA,
    PE_BLOCK_EA,
    PE_BLOCK_EA,
    PE_BLOCK_EA,
    PE_BLOCK_EA,
    PE_BLOCK_EA,
    PE_BLOCK_EA,
    PE_BLOCK_EA,
    PE_BLOCK_EA,
    PE_BLOCK_EA,
    PE_BLOCK_EA,
    PE_BLOCK_EA,
    PE_BLOCK_EA,
    PE_BLOCK_EA,
    PE_BLOCK_EA,
    PE_BLOCK_EA,
    PE_BLOCK_RMI,
    PE_BLOCK_RMI,
    PE_BLOCK_RMI,
    PE_BLOCK_RMI,
    PE_BLOCK_RMI,
    PE_BLOCK_RMI,
    PE_BLOCK_RMI,
    PE_BLOCK_RMI,
    PE_BLOCK_RMI,
    PE_BLOCK_RMI,
    PE_BLOCK_RMI,
    PE_BLOCK_RMI,
    PE_BLOCK_RMI,
    PE_BLOCK_RMI,
    PE_BLOCK_RMI,
    PE_BLOCK_RMI,
    PE_BLOCK_CHA,
    PE_BLOCK_CHC,
    PE_BLOCK_CHC,
    PE_BLOCK_CHC,
    PE_BLOCK_CHC,
    PE_BLOCK_CHCG,
    PE_BLOCK_GCR,
    PE_BLOCK_GE,
    PE_BLOCK_GL1A,
    PE_BLOCK_GL1A,
    PE_BLOCK_GL1A,
    PE_BLOCK_GL1A,
    PE_BLOCK_GL1A,
    PE_BLOCK_GL1A,
    PE_BLOCK_GL1A,
    PE_BLOCK_GL1A,
    PE_BLOCK_GL1C,
    PE_BLOCK_GL1C,
    PE_BLOCK_GL1C,
    PE_BLOCK_GL1C,
    PE_BLOCK_GL1C,
    PE_BLOCK_GL1C,
    PE_BLOCK_GL1C,
    PE_BLOCK_GL1C,
    PE_BLOCK_GL1C,
    PE_BLOCK_GL1C,
    PE_BLOCK_GL1C,
    PE_BLOCK_GL1C,
    PE_BLOCK_GL1C,
    PE_BLOCK_GL1C,
    PE_BLOCK_GL1C,
    PE_BLOCK_GL1C,
    PE_BLOCK_GL1CG,
    PE_BLOCK_GL1CG,
    PE_BLOCK_GL1CG,
    PE_BLOCK_GL1CG,
    PE_BLOCK_GL1CG,
    PE_BLOCK_GL1CG,
    PE_BLOCK_GL1CG,
    PE_BLOCK_GL1CG,
    PE_BLOCK_GL1CG,
    PE_BLOCK_GL1CG,
    PE_BLOCK_GL1CG,
    PE_BLOCK_GL1CG,
    PE_BLOCK_GL1CG,
    PE_BLOCK_GL1CG,
    PE_BLOCK_GL1CG,
    PE_BLOCK_GL1CG,
    PE_BLOCK_GL2A,
    PE_BLOCK_GL2A,
    PE_BLOCK_GL2A,
    PE_BLOCK_GL2A,
    PE_BLOCK_GL2C,
    PE_BLOCK_GL2C,
    PE_BLOCK_GL2C,
    PE_BLOCK_GL2C,
    PE_BLOCK_GL2C,
    PE_BLOCK_GL2C,
    PE_BLOCK_GL2C,
    PE_BLOCK_GL2C,
    PE_BLOCK_GL2C,
    PE_BLOCK_GL2C,
    PE_BLOCK_GL2C,
    PE_BLOCK_GL2C,
    PE_BLOCK_GL2C,
    PE_BLOCK_GL2C,
    PE_BLOCK_GL2C,
    PE_BLOCK_GL2C,
    PE_BLOCK_GL2C,
    PE_BLOCK_GL2C,
    PE_BLOCK_GL2C,
    PE_BLOCK_GL2C,
    PE_BLOCK_GL2C,
    PE_BLOCK_GL2C,
    PE_BLOCK_GL2C,
    PE_BLOCK_GL2C,
    PE_BLOCK_GUS,
    PE_BLOCK_PH,
    PE_BLOCK_UTCL1,
    PE_BLOCK_UTCL1,
    PE_BLOCK_UTCL1,
    PE_BLOCK_UTCL1,
    PE_BLOCK_UNKNOWN,
    PE_BLOCK_UNKNOWN,
    };

    // DX11: Only supports GPU time duration counters. Unavailable counters indices are assigned -1.
    const unsigned int kHwDx11GpuTimeBottomToBottomDurationIndexGfx10 = 58892; ///< Index of delta between the previous command reaching bottom of pipe and the current command reaching bottom of pipe, will not include latency of first data to travel through pipeline, best for large data sets. for Dx11 for Gfx10 family
    const unsigned int kHwDx11GpuTimeBottomToBottomStartIndexGfx10 = static_cast<unsigned int>(-1); ///< Index of time of the previous command reaching bottom of pipe for Dx11 for Gfx10 family
    const unsigned int kHwDx11GpuTimeBottomToBottomEndIndexGfx10 = static_cast<unsigned int>(-1); ///< Index of time of the current command reaching bottom of pipe for Dx11 for Gfx10 family
    const unsigned int kHwDx11GpuTimeTopToBottomDurationIndexGfx10 = 58895; ///< Index of execution duration of the current command from top of pipe to bottom of pipe, may include overhead of time in queue for Dx11 for Gfx10 family
    const unsigned int kHwDx11GpuTimeTopToBottomStartIndexGfx10 = static_cast<unsigned int>(-1); ///< Index of time that the current command reaches the top of pipe for Dx11 for Gfx10 family
    const unsigned int kHwDx11GpuTimeTopToBottomEndIndexGfx10 = static_cast<unsigned int>(-1); ///< Index of time that the current command reaches the bottom of pipe for Dx11 for Gfx10 family
    const std::set<unsigned int> kHwDx11TimestampBlockIdsGfx10 =       {313, 312}; ///< Timestamp block id's for DX11 for gfx10 family
    const std::set<unsigned int> kHwDx11TimeCounterIndicesGfx10 =      {58892, 58893, 58894, 58895, 58896, 58897, 58891}; ///< Timestamp counter indices for DX11 for gfx10 family
    const unsigned int           kHwDx11GroupCountGfx10                = static_cast<unsigned int>(kHwDx11GroupsGfx10.size());
    const unsigned int           kDx11PaddedCounterGroupCountGfx10 = 0;
    const unsigned int           kHwDx11SqGroupCountGfx10              = sizeof(kHwDx11SqGroupsGfx10) / sizeof(GpaSqCounterGroupDesc);
    const unsigned int           kHwDx11SqIsolatedGroupCountGfx10      = sizeof(kHwDx11SqIsolatedGroupsGfx10) / sizeof(unsigned int);
} //  namespace counter_dx11_gfx10

// clang-format on
