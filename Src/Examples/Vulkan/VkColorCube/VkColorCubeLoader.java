//==============================================================================
// Copyright (c) 2019 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Vulkan Color Cube Sample Java Loader
//==============================================================================

package com.amd.gpa.vkcolorcube;
import android.os.Build;
import android.app.Activity;
import android.view.WindowManager;

public class VkColorCubeLoader extends android.app.NativeActivity
{
    static {
        System.loadLibrary("VkColorCube@APK_SUFFIX@");
    }

    @Override
    protected void onCreate(android.os.Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
    }
}
