//==============================================================================
// Copyright (c) 2018-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Sample implementation.
//==============================================================================

#include "examples/dx12/sample.h"

#include <Windows.h>

#include <iostream>
#include <sstream>
#include <string>

extern const unsigned int kWindowWidth;
extern const unsigned int kWindowHeight;
extern const std::wstring kWindowClassName;

extern HWND window_handle;

extern LRESULT CALLBACK SampleWindowProc(_In_ HWND hwnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam);

extern bool         any_errors_logged;       ///< Flag indicating if any GPA errors have been logged.
extern unsigned int validation_error_count;  ///< Number of counter validation errors that have been encountered.

gpa_example::Dx12SampleApp::Dx12SampleApp(const std::string app_name, CmdlineParser& cmdline_parser)
    : GpaSampleApp(app_name, cmdline_parser)
    , nogpa_(false)
    , profile_bundle_(false)
{
    cmdline_parser_.AddArg("--nogpa", &nogpa_, ArgType::kArgTypeBool, "Do not use GPUPerfAPI to collect performance counters");
    cmdline_parser_.AddArg("--profilebundle", &profile_bundle_, ArgType::kArgTypeBool, "Include the bundled samples in the profile (experimental)");
}

bool gpa_example::Dx12SampleApp::NoGpa()
{
    return nogpa_;
}

bool gpa_example::Dx12SampleApp::ProfileBundle()
{
    return profile_bundle_;
}

/// @brief The main function of this sample application.
///
/// @param instance [in] The application instance.
/// @param prev_instance [in] Unused.
/// @param cmd_line [in] Command line arguments as unicode string.
/// @param cmd_show [in] Flag that indicates whether the window will be minimized, maximized, or shown normally.
///
/// @return If the application ran successfully but there were counter validation errors, then the number of validation errors will be the return code.
/// @retval -1 If there were errors executing the application.
/// @retval 0 On success: the application ran successfully and all counters were validated to be correct.
int WINAPI WinMain(_In_ HINSTANCE instance, _In_opt_ HINSTANCE prev_instance, _In_ LPSTR cmd_line, _In_ int cmd_show)
{
    UNREFERENCED_PARAMETER(cmd_line);
    UNREFERENCED_PARAMETER(prev_instance);

    gpa_example::CmdlineParser parser(__argc, __argv);

    gpa_example::Dx12SampleApp app(AMDT_PROJECT_NAME, parser);

    if (!app.Initialize())
    {
        return -1;
    }

    // Create app local window class and register it to system.
    WNDCLASSEX cube_app_window_class = {sizeof(WNDCLASSEX),
                                        CS_HREDRAW | CS_VREDRAW,
                                        SampleWindowProc,
                                        0,
                                        0,
                                        instance,
                                        NULL,  // Default icon.
                                        LoadCursor(nullptr, IDC_IBEAM),
                                        NULL,  // No brush.
                                        NULL,  // No menu.
                                        kWindowClassName.c_str(),
                                        NULL};

    ATOM windowRegisterSuccess = RegisterClassEx(&cube_app_window_class);

    if (windowRegisterSuccess == 0)
    {
        // Failed to register window.
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

    if (window_handle == nullptr)
    {
        // Failed to create window.
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

    // If errors were logged and there were validation errors, then use the number of validation errors as the return code.
    // If errors were logged and there were not validation errors, then return -1.
    // On success return 0.
    return any_errors_logged ? ((validation_error_count > 0) ? validation_error_count : -1) : 0;
}
