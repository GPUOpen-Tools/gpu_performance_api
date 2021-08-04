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

CommandLineArgs args;

/// @brief Print command line usage information.
void Usage()
{
    std::cout << "D3D11Triangle [--nogpa] [--numberofframes #] [--verify] [--confirmsuccess] [--counterfile <file>]" << std::endl << std::endl;
    std::cout << "  --nogpa: Do not use GPUPerfAPI to collect performance counters" << std::endl;
    std::cout << "  --numberofframes #: Renders the specified number of frames before exiting; if used with --verify then # must be a multiple of the number of passes needed" << std::endl;
    std::cout << "  --verify: Application will verify a few counter values (experimental)" << std::endl;
    std::cout << "  --confirmsuccess: Implies --verify and confirms successful counter values in addition to errors" << std::endl;
    std::cout << "  --includehwcounters: Public hardware counters will be enabled in non-internal builds" << std::endl;
    std::cout << "  --counterfile <file>: File containing the list of counters to profile" << std::endl;
}

/// @brief Parse Command line arguments.
bool ParseCommandLine(const int argc, const char* argv[])
{
    bool success = true;

    for (int i = 1; i < argc; i++)
    {
        std::string this_arg(argv[i]);

        if (0 == this_arg.compare("--numberofframes"))
        {
            i++;

            if (i < argc)
            {
                std::istringstream iss(argv[i]);

                iss >> args.num_frames;

                if (iss.fail())
                {
                    success = false;
                }
            }
            else
            {
                success = false;
            }
        }
        else if (0 == this_arg.compare("--verify"))
        {
            args.verify_counters = true;
        }
        else if (0 == this_arg.compare("--confirmsuccess"))
        {
            args.confirm_success = true;
        }
        else if (0 == this_arg.compare("--nogpa"))
        {
            args.use_gpa = false;
        }
        else if (0 == this_arg.compare("--includehwcounters"))
        {
            args.include_hardware_counters = true;
        }
        else if (0 == this_arg.compare("--counterfile"))
        {
            i++;

            if (i < argc)
            {
                std::istringstream iss(argv[i]);

                iss >> args.counter_file_name;

                if (iss.fail())
                {
                    success = false;
                }
                else
                {
                    args.counter_provided = true;
                }
            }
            else
            {
                success = false;
            }
        }
        else
        {
            success = false;
        }
    }

    return success;
}

int WINAPI WinMain(_In_ HINSTANCE instance, _In_opt_ HINSTANCE prev_instance, _In_ LPSTR cmd_line, _In_ int cmd_show)
{
    UNREFERENCED_PARAMETER(cmd_line);
    UNREFERENCED_PARAMETER(prev_instance);

    if (!ParseCommandLine(__argc, const_cast<const char**>(__argv)))
    {
        Usage();
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

    return any_errors_logged ? -1 : 0;
}