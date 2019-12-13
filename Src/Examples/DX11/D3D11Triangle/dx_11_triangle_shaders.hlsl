//==============================================================================
// Copyright (c) 2019 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  HLSL Shader
//==============================================================================

struct PS
{
float4 position : SV_POSITION;
float4 color : COLOR;
};


PS VSMain(float4 vertex : SCREEN_POSITION, float4 color : VERTEX_COLOR)
{
    PS retPS;
    retPS.position = vertex;
    retPS.color = color;
    return retPS;
}


float4 PSMain(PS psInput) : SV_TARGET
{
    float4 outColor = psInput.color;
    return outColor;
}