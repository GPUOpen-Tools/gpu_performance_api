//==============================================================================
// Copyright (c) 2019-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief Vk Color cube Android Main class
//==============================================================================

#include <android_native_app_glue.h>
#include <android/log.h>
#include "vk_color_cube.h"

#ifndef JNIEXPORT
    #define JNIEXPORT  __attribute__ ((visibility ("default")))
#endif

extern "C"
{
    #include <android_native_app_glue.c>
}

#include <dlfcn.h>
#include <iostream>

// Process the next main command.
void process_android_cmd(android_app* vkColorCube, int32_t cmd)
{
    __android_log_print(ANDROID_LOG_INFO, "GPA VkColorCube", "Testing");
    switch (cmd)
    {
        case APP_CMD_INIT_WINDOW:
        AMDVulkanDemo::Instance()->SetWindow(vkColorCube->window);
        AMDVulkanDemo::Instance()->SetNativeActivity(vkColorCube->activity);
        AMDVulkanDemo::Instance()->InitializeVulkan();
            break;
        case APP_CMD_TERM_WINDOW:
            AMDVulkanDemo::Instance()->Destroy();
            break;
        case APP_CMD_WINDOW_REDRAW_NEEDED:
            AMDVulkanDemo::Instance()->DrawScene();
            break;
        default:
            break;
            //__android_log_print(ANDROID_LOG_INFO, "Vulkan AMD color cube", "event not handled: %d", cmd);
    }
}

/// Native-App must implement the android_main
void android_main(struct android_app* vkColorCube)
{
    // Set the callback to process system events
    vkColorCube->onAppCmd = process_android_cmd;

    // Used to poll the events in the main loop
    int events;
    android_poll_source* source;

    // Main loop
    do
    {
        if (ALooper_pollAll(AMDVulkanDemo::Instance()->Initialized() ? 1 : 0, nullptr, &events, (void**)&source) >= 0)
        {
            if (nullptr != source)
            {
                source->process(vkColorCube, source);
            }
        }

        // render if vulkan is ready
        if (AMDVulkanDemo::Instance()->Initialized())
        {
            AMDVulkanDemo::Instance()->DrawScene();
        }
    } while (vkColorCube->destroyRequested == 0);
}