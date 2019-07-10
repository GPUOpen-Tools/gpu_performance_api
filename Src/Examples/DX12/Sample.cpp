//==============================================================================
// Copyright (c) 2018-2019 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Sample implementation
//==============================================================================

#include <Windows.h>
#include <string>
#include <sstream>

#include "Sample.h"

extern unsigned int g_windowWidth;
extern unsigned int g_windowHeight;
extern std::wstring g_windowClassName;
extern HWND         g_windowHandle;

extern LRESULT CALLBACK SampleWindowProc(_In_ HWND hwnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam);

extern bool g_anyGPAErrorsLogged;  ///< flag indicating if any GPA errors have been logged

CommandLineArgs args;

/// Parse Command line arguments
bool ParseCommandLine(const int argc, const char* argv[])
{
    bool success = true;

    for (int i = 1; i < argc; i++)
    {
        std::string thisArg(argv[i]);

        if (0 == thisArg.compare("--numberofframes"))
        {
            i++;

            if (i < argc)
            {
                std::istringstream iss(argv[i]);

                iss >> args.m_numberOfFrames;

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
        else if (0 == thisArg.compare("--profilebundles"))
        {
            args.m_profileBundles = true;
        }
        else if (0 == thisArg.compare("--verify"))
        {
            args.m_verifyCounters = true;
        }
        else if (0 == thisArg.compare("--nogpa"))
        {
            args.m_useGPA = false;
        }
        else if (0 == thisArg.compare("--includehwcounters"))
        {
            args.m_includeHwCounters = true;
        }
        else
        {
            success = false;
        }
    }

    return success;
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE prevInstance, _In_ LPSTR pCmdLine, _In_ int cmdShow)
{
    UNREFERENCED_PARAMETER(pCmdLine);
    UNREFERENCED_PARAMETER(prevInstance);

    if (!ParseCommandLine(__argc, const_cast<const char**>(__argv)))
    {
        return -1;
    }

    // Create app local window class and register it to system
    WNDCLASSEX cubeAppWindowClass = {sizeof(WNDCLASSEX),
                                     CS_HREDRAW | CS_VREDRAW,
                                     SampleWindowProc,
                                     0,
                                     0,
                                     hInstance,
                                     NULL,  // default icon
                                     LoadCursor(nullptr, IDC_IBEAM),
                                     NULL,  // no brush
                                     NULL,  // no menu
                                     g_windowClassName.c_str(),
                                     NULL};

    ATOM windowRegisterSuccess = RegisterClassEx(&cubeAppWindowClass);

    if (windowRegisterSuccess == 0)
    {
        // Failed to register window
        return -1;
    }

    g_windowHandle = CreateWindow(g_windowClassName.c_str(),
                                  g_windowClassName.c_str(),
                                  WS_OVERLAPPED | WS_SYSMENU,
                                  CW_USEDEFAULT,
                                  CW_USEDEFAULT,
                                  g_windowWidth,
                                  g_windowHeight,
                                  nullptr,
                                  nullptr,
                                  hInstance,
                                  nullptr);

    if (g_windowHandle == nullptr)
    {
        // Failed to create window
        return -1;
    }

    ShowWindow(g_windowHandle, cmdShow);


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

    DestroyWindow(g_windowHandle);
    UnregisterClass(g_windowClassName.c_str(), hInstance);

    return g_anyGPAErrorsLogged ? -1 : 0;
}
