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
#include <vector>

// Process the next main command.
void process_android_cmd(android_app* vkColorCube, int32_t cmd)
{
    AMDVulkanDemo* app = reinterpret_cast<AMDVulkanDemo*>(vkColorCube->userData);
    __android_log_print(ANDROID_LOG_INFO, "GPA VkColorCube", "Testing");
    switch (cmd)
    {
    case APP_CMD_INIT_WINDOW:
        app->SetWindow(vkColorCube->window);
        app->SetNativeActivity(vkColorCube->activity);
        app->InitializeVulkan();
        break;
    case APP_CMD_TERM_WINDOW:
        delete app;
        break;
    case APP_CMD_WINDOW_REDRAW_NEEDED:
        app->DrawScene();
        break;
    default:
        break;
        //__android_log_print(ANDROID_LOG_INFO, "Vulkan AMD color cube", "event not handled: %d", cmd);
    }
}

/// Native-App must implement the android_main
void android_main(struct android_app* vkColorCube)
{
    // Android native apps don't utilize command line arguments, so we emulate them here.
    std::vector<const char*>   argv_mock{"VkColorCube"};
    gpa_example::CmdlineParser parser(argv_mock.size(), const_cast<char**>(argv_mock.data()));

    AMDVulkanDemo* app    = new AMDVulkanDemo("VkColorCube", parser);
    vkColorCube->userData = app;

    // Set the callback to process system events
    vkColorCube->onAppCmd = process_android_cmd;

    // Used to poll the events in the main loop
    int events;
    android_poll_source* source;

    // Main loop
    do
    {
        if (ALooper_pollAll(app->Initialized() ? 1 : 0, nullptr, &events, (void**)&source) >= 0)
        {
            if (nullptr != source)
            {
                source->process(vkColorCube, source);
            }
        }

        // render if vulkan is ready
        if (app->Initialized())
        {
            app->DrawScene();
        }
    } while (vkColorCube->destroyRequested == 0);
}
