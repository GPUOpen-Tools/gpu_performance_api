//==============================================================================
// Copyright (c) 2019-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Sample implementation.
//==============================================================================

#include "examples/dx11/sample.h"

#include <Windows.h>

#include <iostream>
#include <sstream>
#include <string>

extern const unsigned int kWindowWidth;
extern const unsigned int kWindowHeight;
extern const std::wstring kWindowClassName;

extern HWND window_handle;

extern LRESULT CALLBACK SampleWindowProc(_In_ HWND hwnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam);

extern bool any_errors_logged;  ///< Flag indicating if any GPA errors have been logged.
extern int  num_errors_logged;  ///< Indicates the number of GPA errors that have been logged.

gpa_example::Dx11SampleApp::Dx11SampleApp(const std::string app_name, CmdlineParser& cmdline_parser)
    : GpaSampleApp(app_name, cmdline_parser)
    , nogpa_(false)
{
    cmdline_parser_.AddArg("--nogpa", &nogpa_, ArgType::ARG_TYPE_BOOL, "Do not use GPUPerfAPI to collect performance counters");
}

bool gpa_example::Dx11SampleApp::NoGpa()
{
    return nogpa_;
}

int WINAPI WinMain(_In_ HINSTANCE instance, _In_opt_ HINSTANCE prev_instance, _In_ LPSTR cmd_line, _In_ int cmd_show)
{
    UNREFERENCED_PARAMETER(cmd_line);
    UNREFERENCED_PARAMETER(prev_instance);

    gpa_example::CmdlineParser parser(__argc, __argv);

    gpa_example::Dx11SampleApp app(AMDT_PROJECT_NAME, parser);

    if (!app.Initialize())
    {
        return -1;
    }

    // Create app local window class and register it to system
    WNDCLASSEX cube_application_window_class = {sizeof(WNDCLASSEX),
                                                CS_HREDRAW | CS_VREDRAW,
                                                SampleWindowProc,
                                                0,
                                                0,
                                                instance,
                                                NULL,  // default icon
                                                LoadCursor(nullptr, IDC_IBEAM),
                                                NULL,  // no brush
                                                NULL,  // no menu
                                                kWindowClassName.c_str(),
                                                NULL};

    ATOM window_registration_success = RegisterClassEx(&cube_application_window_class);

    if (window_registration_success == 0)
    {
        // Failed to register window
        return -1;
    }

    window_handle = CreateWindow(kWindowClassName.c_str(),
                                 kWindowClassName.c_str(),
                                 WS_OVERLAPPED | WS_SYSMENU,
                                 CW_USEDEFAULT,
                                 CW_USEDEFAULT,
                                 kWindowWidth,
                                 kWindowHeight,
                                 nullptr,
                                 nullptr,
                                 instance,
                                 nullptr);

    if (nullptr == window_handle)
    {
        // Failed to create window
        return -1;
    }

    SetWindowLongPtr(window_handle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(&app));

    ShowWindow(window_handle, cmd_show);

    // Main sample loop.
    MSG msg = {};

    while (msg.message != WM_QUIT)
    {
        // Process any messages in the queue.
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    DestroyWindow(window_handle);
    UnregisterClass(kWindowClassName.c_str(), instance);

    return any_errors_logged ? num_errors_logged : 0;
}
