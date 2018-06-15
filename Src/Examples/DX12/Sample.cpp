//==============================================================================
// Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Sample implementation
//==============================================================================

#include <Windows.h>
#include <string>

extern unsigned int g_windowWidth;
extern unsigned int g_windowHeight;
extern std::wstring g_windowClassName;
extern HWND g_windowHandle;

extern LRESULT CALLBACK SampleWindowProc(
    _In_ HWND   hwnd,
    _In_ UINT   uMsg,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam
);

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE prevInstance, LPSTR pCmdLine, int cmdShow)
{
    UNREFERENCED_PARAMETER(pCmdLine);
    UNREFERENCED_PARAMETER(prevInstance);
    // Create app local window class and register it to system
    WNDCLASSEX cubeAppWindowClass =
    {
        sizeof(WNDCLASSEX),
        CS_HREDRAW | CS_VREDRAW,
        SampleWindowProc,
        0,
        0,
        hinstance,
        NULL, // default icon
        LoadCursor(nullptr, IDC_IBEAM),
        NULL, // no brush
        NULL, // no menu
        g_windowClassName.c_str(),
        NULL
    };

    ATOM windowRegisterSuccess = RegisterClassEx(&cubeAppWindowClass);

    if (windowRegisterSuccess == 0)
    {
        // Failed to register window
        return -1;
    }

    g_windowHandle = CreateWindow(
                         g_windowClassName.c_str(),
                         g_windowClassName.c_str(),
                         WS_OVERLAPPED | WS_SYSMENU,
                         CW_USEDEFAULT,
                         CW_USEDEFAULT,
                         g_windowWidth,
                         g_windowHeight,
                         nullptr,
                         nullptr,
                         hinstance,
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
    UnregisterClass(g_windowClassName.c_str(), hinstance);
    return 0;
}
