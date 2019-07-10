//==============================================================================
// Copyright (c) 2019 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  GL Sample
//==============================================================================

#include "GPAHelper.h"

#ifdef _WIN32
#pragma warning(disable : 4505)
#include <Windows.h>
#include <GL/GL.h>
#else
#include <GL/glx.h>
#include <X11/Xutil.h>
#endif

/// Struct to hold values of command line arguments.
struct CommandLineArgs
{
    ///< Number of frames to execute -- zero indicates that the app should run until the user closes it
    unsigned int m_numberOfFrames = 0;

    ///< Flag indicating if some counter values should be verified (experimental)
    bool m_verifyCounters = false;

    /// Flag indicating whether or not to include hardware counters in non-internal builds
    bool m_includeHwCounters = false;
};

CommandLineArgs g_args;
unsigned int    g_windowWidth     = 500;
unsigned int    g_windowHeight    = 500;
std::wstring    g_windowClassName = L"OpenGL Triangle Sample App";

#ifdef _LINUX
Display* g_pDisplay;
Window   g_appWindow;
Colormap g_windowColorMap;
#else
HWND g_windowHandle;
#endif

GLContext g_glContext = nullptr;

#define MAKE_STRING(X) #X

#define LOG_ERROR(errorType, errorMessage)  \
    GPALogger(static_cast<GPA_Logging_Type>(errorType), errorMessage)

#define GL_FUNC(X, errorMessage, line)                                              \
    {                                                                               \
        X;                                                                          \
        GLenum glError = glGetError();                                              \
        if (GL_NO_ERROR != glError)                                                 \
        {                                                                           \
            std::stringstream errorString;                                          \
            errorString << "error code - " << std::hex << glError << " ";           \
            errorString << errorMessage << " at line " MAKE_STRING(line);           \
            LOG_ERROR(GL_ERROR, errorString.str().c_str());                         \
        }                                                                           \
    }

#define RETURN_IF_FAILED(X) if (!X) return -1;

int DrawTriangle()
{
    if (g_args.m_numberOfFrames > 0 && GPAHelper::Instance()->GetCurrentFrameCount() == g_args.m_numberOfFrames)
    {
        GPAHelper::Instance()->CloseContext();
        if (GPAHelper::Instance()->m_anyGpaError)
        {
            exit(1);
        }

        exit(0);
    }

    RETURN_IF_FAILED(GPAHelper::Instance()->CreateGpaSession());
#ifndef AMDT_INTERNAL
    RETURN_IF_FAILED(GPAHelper::Instance()->EnableAllCounters());
#else
    RETURN_IF_FAILED(GPAHelper::Instance()->EnableCounterByName("GPUTime"));
#endif
    RETURN_IF_FAILED(GPAHelper::Instance()->OnGpaSessionStart());

    GL_FUNC(glFlush(), "glFlush failed", __LINE__);
    GL_FUNC(glFinish(), "glFinish failed", __LINE__);

    unsigned int passIter = 0u;

    do
    {
        RETURN_IF_FAILED(GPAHelper::Instance()->OnPassStart());
        RETURN_IF_FAILED(GPAHelper::Instance()->BeginSample());
        GL_FUNC(glFlush(), "glFlush failed", __LINE__);
        GL_FUNC(glFinish(), "glFinish failed", __LINE__);
        GL_FUNC(glViewport(0, 0, 500, 500), "glViewPort failed", __LINE__);
        glBegin(GL_TRIANGLES);
        GLfloat v1[] = {0.0f, 0.75f, 1.0f};
        GLfloat v2[] = {-0.75f, -0.75f, 0.0f};
        GLfloat v3[] = {0.75f, -0.75f, 0.0f};
        glColor3f(0.0f, 0.0f, 1.0f);  //blue color
        glVertex3fv(v1);
        glColor3f(1.0f, 0.0f, 0.0f);  //red color
        glVertex3fv(v2);
        glColor3f(0.0f, 1.0f, 0.0f);  //green color
        glVertex3fv(v3);
        glEnd();
        GL_FUNC(glFlush(), "glFlush failed", __LINE__);
        GL_FUNC(glFinish(), "glFinish failed", __LINE__);
        RETURN_IF_FAILED(GPAHelper::Instance()->EndSample());
        RETURN_IF_FAILED(GPAHelper::Instance()->OnPassEnd());
        passIter++;
    } while (passIter < GPAHelper::Instance()->GetPassRequired());

    GL_FUNC(glFlush(), "glFlush failed", __LINE__);
    GL_FUNC(glFinish(), "glFinish failed", __LINE__);

    RETURN_IF_FAILED(GPAHelper::Instance()->OnGpaSessionEnd());
    RETURN_IF_FAILED(GPAHelper::Instance()->PrintGPASampleResults(g_args.m_verifyCounters));
    RETURN_IF_FAILED(GPAHelper::Instance()->DestroyGpaSession());

    GPAHelper::Instance()->IncrementFrameCounter();
    return 0;
}

// Parse Command line arguments
bool ParseCommandLine(int argc, char* argv[])
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

                iss >> g_args.m_numberOfFrames;

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
        else if (0 == thisArg.compare("--verify"))
        {
            g_args.m_verifyCounters = true;
        }
        else if (0 == thisArg.compare("--includehwcounters"))
        {
            g_args.m_includeHwCounters = true;
        }
        else
        {
            success = false;
        }
    }

    return success;
}

#ifdef _LINUX

int XGLTriangleErrorHandler(Display* pDisplay, XErrorEvent* pErrorEvent)
{
    char errorCodeText[GPA_MAX_PATH];
    XGetErrorText(pDisplay, pErrorEvent->error_code, errorCodeText, GPA_MAX_PATH);
    std::stringstream ss;
    ss  << errorCodeText;
    LOG_ERROR(X_SERVER_ERROR, ss.str().c_str());
    return -1;
}

void CreateWindowAndContext()
{
    g_pDisplay = XOpenDisplay(nullptr);

    GLint glAttributes[] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None};

    if (nullptr != g_pDisplay)
    {
        XSetErrorHandler(&XGLTriangleErrorHandler);
        Window       rootWindow    = DefaultRootWindow(g_pDisplay);
        int          defaultScreen = DefaultScreen(g_pDisplay);
        XVisualInfo* visualInfo    = glXChooseVisual(g_pDisplay, defaultScreen, glAttributes);

        // Create color map for the window
        g_windowColorMap                      = XCreateColormap(g_pDisplay, rootWindow, visualInfo->visual, AllocNone);
        XSetWindowAttributes windowAttributes = {};
        windowAttributes.colormap             = g_windowColorMap;
        windowAttributes.event_mask           = ExposureMask | StructureNotifyMask;
        windowAttributes.backing_store = NotUseful;

        g_appWindow = XCreateWindow(
            g_pDisplay, rootWindow, 0, 0, g_windowWidth, g_windowHeight, 0, 24, InputOutput, visualInfo->visual, CWColormap | CWEventMask, &windowAttributes);

        XMapWindow(g_pDisplay, g_appWindow);
        g_glContext = glXCreateContext(g_pDisplay, visualInfo, nullptr, GL_TRUE);
        glXMakeCurrent(g_pDisplay, g_appWindow, g_glContext);
    }
}

int main(int argc, char* argv[])
{
    if (!ParseCommandLine(argc, argv))
    {
        return -1;
    }

    int width  = 500;
    int height = 250;
    glViewport(0, 0, width, height);

    CreateWindowAndContext();

    Atom windowDeletion = XInternAtom(g_pDisplay, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(g_pDisplay, g_appWindow, &windowDeletion, 1);

    XEvent event;
    RETURN_IF_FAILED(GPAHelper::Instance()->SetUpGPA());
    RETURN_IF_FAILED(GPAHelper::Instance()->OpenContext(g_glContext, g_args.m_includeHwCounters));

    while (1)
    {
        XNextEvent(g_pDisplay, &event);

        if (event.type == Expose)
        {
            glViewport(0, 0, 500, 500);
            DrawTriangle();
            glXSwapBuffers(g_pDisplay, g_appWindow);
            int eventQueueLength = XQLength(g_pDisplay);
            if(eventQueueLength == 0)
            {
                XPutBackEvent(g_pDisplay, &event);
            }
        }
        else if( event.type == ClientMessage)
        {
            XClientMessageEvent clientMessage = event.xclient;
            if (*clientMessage.data.l == static_cast<long>(windowDeletion))
            {
                RETURN_IF_FAILED(GPAHelper::Instance()->CloseContext());
                XFreeColormap(g_pDisplay, g_windowColorMap);
                XUnmapWindow(g_pDisplay, g_appWindow);
                XDestroyWindow(g_pDisplay, g_appWindow);
                XCloseDisplay(g_pDisplay);
                g_pDisplay = nullptr;
                exit(0);
            }
        }
    };
}
#else

LRESULT CALLBACK SampleWindowProc(_In_ HWND hwnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_PAINT:
    {
        HDC deviceContext = GetDC(g_windowHandle);

        if(nullptr == deviceContext &&
           ERROR_SUCCESS != GetLastError())
        {
            LOG_ERROR(WIN_ERROR, "GetDC failed.");
        }

        if (nullptr == g_glContext)
        {
            RETURN_IF_FAILED(GPAHelper::Instance()->SetUpGPA());
            g_glContext    = wglCreateContext(deviceContext);
            if (nullptr == g_glContext &&
                ERROR_SUCCESS != GetLastError())
            {
                LOG_ERROR(WIN_ERROR, "Unable to create context.");
            }

            if (FAILED(wglMakeCurrent(deviceContext, g_glContext)) &&
                ERROR_SUCCESS != GetLastError())
            {
                LOG_ERROR(WIN_ERROR, "Unable to make context current.");
            }
            RETURN_IF_FAILED(GPAHelper::Instance()->OpenContext(g_glContext, g_args.m_includeHwCounters));
        }

        if(DrawTriangle() == -1)
        {
            return -1;
        }

        SwapBuffers(deviceContext);
        return 0;
    }

    case WM_DESTROY:
        // Destroy app here
        RETURN_IF_FAILED(GPAHelper::Instance()->CloseContext());
        PostQuitMessage(0);
        return 0;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE prevInstance, LPSTR pCmdLine, int cmdShow)
{
    UNREFERENCED_PARAMETER(pCmdLine);
    UNREFERENCED_PARAMETER(prevInstance);

    if (!ParseCommandLine(__argc, __argv))
    {
        return -1;
    }

    // Create app local window class and register it to system
    WNDCLASSEX appWindowClass = {sizeof(WNDCLASSEX),
                                 CS_HREDRAW | CS_VREDRAW,
                                 SampleWindowProc,
                                 0,
                                 0,
                                 hinstance,
                                 NULL,  // default icon
                                 LoadCursor(nullptr, IDC_IBEAM),
                                 NULL,  // no brush
                                 NULL,  // no menu
                                 g_windowClassName.c_str(),
                                 NULL};

    ATOM windowRegisterSuccess = RegisterClassEx(&appWindowClass);

    DWORD winErrorCode = ERROR_SUCCESS;
    if (NULL == windowRegisterSuccess)
    {
        winErrorCode = GetLastError();
        if (ERROR_SUCCESS != winErrorCode)
        {
            LOG_ERROR(WIN_ERROR, "Unable to register windows class.");
        }

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
                                  hinstance,
                                  nullptr);

    if(nullptr == g_windowHandle)
    {
        winErrorCode = GetLastError();
        if (ERROR_SUCCESS != winErrorCode)
        {
            LOG_ERROR(WIN_ERROR, "Unable to create window.");
        }

        // Failed to create window
        return -1;
    }

    PIXELFORMATDESCRIPTOR pfd = {sizeof(PIXELFORMATDESCRIPTOR),
                                 1,
                                 PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
                                 PFD_TYPE_RGBA,
                                 32,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 24,
                                 8,
                                 0,
                                 PFD_MAIN_PLANE,
                                 0,
                                 0,
                                 0,
                                 0};

    HDC deviceContext    = GetDC(g_windowHandle);

    if (nullptr == deviceContext)
    {
        winErrorCode = GetLastError();
        if (ERROR_SUCCESS != winErrorCode)
        {
            LOG_ERROR(WIN_ERROR, "Unable to get device context from windows.");
        }
        return -1;
    }

    int pixelFormatIndex = ChoosePixelFormat(deviceContext, &pfd);

    if (0 == pixelFormatIndex)
    {
        winErrorCode = GetLastError();
        if (ERROR_SUCCESS != winErrorCode)
        {
            LOG_ERROR(WIN_ERROR, "Unable to choose pixel format.");
        }
        return -1;
    }

    if(FAILED(SetPixelFormat(deviceContext, pixelFormatIndex, &pfd)))
    {
        winErrorCode = GetLastError();
        if (ERROR_SUCCESS != winErrorCode)
        {
            LOG_ERROR(WIN_ERROR, "Unable to set pixel format.");
        }
        return -1;
    }

    if(FAILED(ShowWindow(g_windowHandle, cmdShow)))
    {
        winErrorCode = GetLastError();
        if (ERROR_SUCCESS != winErrorCode)
        {
            LOG_ERROR(WIN_ERROR, "Unable to show window.");
        }
        return -1;
    }

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

    if(FAILED(UnregisterClass(g_windowClassName.c_str(), hinstance)))
    {
        winErrorCode = GetLastError();
        if (ERROR_SUCCESS != winErrorCode)
        {
            LOG_ERROR(WIN_ERROR, "Unable to unregister windows class.");
        }
        return -1;
    }

    return GPAHelper::Instance()->m_anyGpaError ? -1 : 0;
}
#endif
