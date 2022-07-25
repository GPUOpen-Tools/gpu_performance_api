//==============================================================================
// Copyright (c) 2019-2022 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief GL triangle.
//==============================================================================

#include <iostream>

#define GLUT_NO_LIB_PRAGMA

#ifdef _WIN32
#pragma warning(disable : 4505)
#include <windows.h>
#include <GL/GL.h>
#include <GL/GLext.h>
#include <GL/wglext.h>
#endif

#ifdef _LINUX
#include <GL/glx.h>
#include <dlfcn.h>
#include <X11/Xutil.h>
#endif

#ifdef _WIN32
typedef HMODULE LibHandle;
#define LOAD_SYMBOL GetProcAddress
#define GET_PROC_ADDRESS_TYPE wglGetProcAddress
#define GET_PROC_ADDRESS_FUNC _wglGetProcAddress
#endif

#ifdef _LINUX
typedef void* LibHandle;
#define LOAD_SYMBOL dlsym
#define GET_PROC_ADDRESS_TYPE glXGetProcAddressARB
#define GET_PROC_ADDRESS_FUNC _glXGetProcAddressARB
#endif

#include "examples/opengl/gl_triangle/gpa_helper.h"

const unsigned int kWindowWidth     = 800;
const unsigned int kWindowHeight    = 800;
const std::wstring kWindowClassName = L"OpenGL Triangle Sample App";

/// Handle to the OpenGL library.
LibHandle gl_lib_handle = nullptr;

#ifdef _LINUX
Display* kDisplay;
Window   kAppWindow;
Colormap kWindowColorMap;
#else
HWND window_handle;
#endif

GlContext gl_context = nullptr;

decltype(glBegin)*      ogl_begin       = nullptr;
decltype(glEnd)*        ogl_end         = nullptr;
decltype(glFinish)*     ogl_finish      = nullptr;
decltype(glColor3f)*    ogl_color_3f    = nullptr;
decltype(glVertex3fv)*  ogl_vertex_3fv  = nullptr;
decltype(glViewport)*   ogl_viewport    = nullptr;
decltype(glGetError)*   ogl_get_error   = nullptr;
decltype(glFlush)*      ogl_flush       = nullptr;
decltype(glClearColor)* ogl_clear_color = nullptr;
decltype(glClear)*      ogl_clear       = nullptr;

#define MAKE_STRING(X) #X

#define LOG_ERROR(error_type, error_message) GpaLogger(static_cast<GpaLoggingType>(error_type), error_message)

#define GL_FUNC(X, error_message, line)                                     \
    {                                                                       \
        X;                                                                  \
        GLenum gl_error = ogl_get_error();                                  \
        if (GL_NO_ERROR != gl_error)                                        \
        {                                                                   \
            std::stringstream error_string;                                 \
            error_string << "error code - " << std::hex << gl_error << " "; \
            error_string << error_message << " at line " MAKE_STRING(line); \
            LOG_ERROR(kGlError, error_string.str().c_str());                \
        }                                                                   \
    }

#define LOAD_LIBRARY_SYMBOL(varName, type)                                                \
    if (nullptr == (varName))                                                             \
    {                                                                                     \
        (varName) = reinterpret_cast<decltype(type)*>(LOAD_SYMBOL(gl_lib_handle, #type)); \
    }

#define CHECK_LOAD_LIBRARY_SYMBOL(varName, type)                                          \
    if (nullptr == (varName))                                                             \
    {                                                                                     \
        (varName) = reinterpret_cast<decltype(type)*>(LOAD_SYMBOL(gl_lib_handle, #type)); \
        if (nullptr == (varName))                                                         \
        {                                                                                 \
            LOG_ERROR(kGlError, "Unable to obtain " #type " function pointer.");          \
            return false;                                                                 \
        }                                                                                 \
    }

#define RETURN_IF_FAILED(X) \
    if (!X)                 \
        return -1;

bool CreateSessionAndEnableCounters()
{
    const gpa_example::GpaSampleApp& app = *(GpaHelper::Instance()->App());

    if (!GpaHelper::Instance()->CreateGpaSession())
    {
        return false;
    }

    if (!app.Counterfile().empty())
    {
        std::fstream counter_file_stream;
        counter_file_stream.open(app.Counterfile().c_str(), std::ios_base::in);
        std::vector<std::string> counter_list;
        char                     temp_counter[256];
        if (counter_file_stream.is_open())
        {
            while (counter_file_stream.getline(temp_counter, 256))
            {
                counter_list.push_back(std::string(temp_counter));
            }

            counter_file_stream.close();

            for (std::vector<std::string>::const_iterator it = counter_list.cbegin(); it != counter_list.cend(); ++it)
            {
                if (!GpaHelper::Instance()->EnableCounterByName(it->c_str()))
                {
                    std::stringstream error;
                    error << "Failed to enable counter '" << it->c_str() << "'.";
                    GpaLogger(static_cast<GpaLoggingType>(kGeneralError), error.str().c_str());
                    return false;
                }
            }
        }
        else
        {
            std::stringstream error;
            error << "Unable to open Counter file " << app.Counterfile().c_str() << ". Not enabling any counters.";
            LOG_ERROR(kGeneralError, error.str().c_str());
            return false;
        }
    }
    else
    {
#ifndef AMDT_INTERNAL
        if (!GpaHelper::Instance()->EnableAllCounters())
        {
            return false;
        }
#else
        if (!GpaHelper::Instance()->EnableCounterByName("GPUTime"))
        {
            return false;
        }
#endif
    }

    return true;
}

void DrawClear()
{
    ogl_clear_color(0.0f, 0.0f, 0.0f, 1.0f);
    ogl_clear(GL_COLOR_BUFFER_BIT);
}

void DrawTriangle()
{
    GL_FUNC(ogl_viewport(0, 0, kWindowWidth, kWindowHeight), "glViewPort failed", __LINE__);

    ogl_begin(GL_TRIANGLES);
    GLfloat v1[] = {0.0f, 0.75f, 1.0f};
    GLfloat v2[] = {-0.75f, -0.75f, 0.0f};
    GLfloat v3[] = {0.75f, -0.75f, 0.0f};
    ogl_color_3f(0.0f, 0.0f, 1.0f);  // Blue color.
    ogl_vertex_3fv(v1);
    ogl_color_3f(1.0f, 0.0f, 0.0f);  // Red color.
    ogl_vertex_3fv(v2);
    ogl_color_3f(0.0f, 1.0f, 0.0f);  // Green color.
    ogl_vertex_3fv(v3);
    ogl_end();
}

bool LoadOpenGL()
{
    if (nullptr == gl_lib_handle)
    {
#ifdef _WIN32
        gl_lib_handle = LoadLibraryA("opengl32.dll");
        if (gl_lib_handle == nullptr)
        {
            LOG_ERROR(kGlError, "Failed to load opengl32.dll");
        }
#endif
#ifdef _LINUX
        gl_lib_handle = dlopen("libGL.so", RTLD_LAZY);
        if (gl_lib_handle == nullptr)
        {
            LOG_ERROR(kGlError, "Failed to load libGL.so");
        }
#endif
    }

    return nullptr != gl_lib_handle;
}

bool InitializeOpenGLFunctionPointers()
{
    if (!LoadOpenGL())
    {
        return false;
    }

    CHECK_LOAD_LIBRARY_SYMBOL(ogl_flush, glFlush);
    CHECK_LOAD_LIBRARY_SYMBOL(ogl_get_error, glGetError);
    CHECK_LOAD_LIBRARY_SYMBOL(ogl_clear_color, glClearColor);
    CHECK_LOAD_LIBRARY_SYMBOL(ogl_clear, glClear);
    CHECK_LOAD_LIBRARY_SYMBOL(ogl_begin, glBegin);
    CHECK_LOAD_LIBRARY_SYMBOL(ogl_end, glEnd);
    CHECK_LOAD_LIBRARY_SYMBOL(ogl_finish, glFinish);
    CHECK_LOAD_LIBRARY_SYMBOL(ogl_color_3f, glColor3f);
    CHECK_LOAD_LIBRARY_SYMBOL(ogl_vertex_3fv, glVertex3fv);
    CHECK_LOAD_LIBRARY_SYMBOL(ogl_viewport, glViewport);

    return true;
}

#ifdef _LINUX

int XGLTriangleErrorHandler(Display* display, XErrorEvent* error_event)
{
    char error_code_text[GPA_MAX_PATH];
    XGetErrorText(display, error_event->error_code, error_code_text, GPA_MAX_PATH);
    std::stringstream ss;
    ss << error_code_text;
    LOG_ERROR(kXServerError, ss.str().c_str());
    return -1;
}

bool CreateWindowAndContext()
{
    kDisplay = XOpenDisplay(nullptr);

    GLint gl_attributes[] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None};

    if (nullptr != kDisplay)
    {
        XSetErrorHandler(&XGLTriangleErrorHandler);
        Window root_window    = DefaultRootWindow(kDisplay);
        int    default_screen = DefaultScreen(kDisplay);

        decltype(glXChooseVisual)* glx_choose_visual = nullptr;
        CHECK_LOAD_LIBRARY_SYMBOL(glx_choose_visual, glXChooseVisual);
        XVisualInfo* visual_info = glx_choose_visual(kDisplay, default_screen, gl_attributes);

        // Create color map for the window.
        kWindowColorMap                       = XCreateColormap(kDisplay, root_window, visual_info->visual, AllocNone);
        XSetWindowAttributes windowAttributes = {};
        windowAttributes.colormap             = kWindowColorMap;
        windowAttributes.event_mask           = ExposureMask | StructureNotifyMask;
        windowAttributes.backing_store        = NotUseful;

        kAppWindow = XCreateWindow(
            kDisplay, root_window, 0, 0, kWindowWidth, kWindowHeight, 0, 24, InputOutput, visual_info->visual, CWColormap | CWEventMask, &windowAttributes);

        XMapWindow(kDisplay, kAppWindow);

        decltype(glXCreateContext)* glx_create_context = nullptr;
        CHECK_LOAD_LIBRARY_SYMBOL(glx_create_context, glXCreateContext);
        gl_context = glx_create_context(kDisplay, visual_info, nullptr, GL_TRUE);

        decltype(glXMakeCurrent)* glx_make_current = nullptr;
        CHECK_LOAD_LIBRARY_SYMBOL(glx_make_current, glXMakeCurrent);
        glx_make_current(kDisplay, kAppWindow, gl_context);
    }

    return true;
}

int main(int argc, char* argv[])
{
    if (!GpaHelper::Instance()->ParseCommandLine(argc, argv))
    {
        GpaHelper::DeleteInstance();
        return -1;
    }

    if (!InitializeOpenGLFunctionPointers())
    {
        GpaHelper::DeleteInstance();
        return -1;
    }

    ogl_viewport(0, 0, kWindowWidth, kWindowHeight);

    if (!CreateWindowAndContext())
    {
        GpaHelper::DeleteInstance();
        return -1;
    }

    Atom window_deletion = XInternAtom(kDisplay, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(kDisplay, kAppWindow, &window_deletion, 1);

    XEvent event;

    if (!GpaHelper::Instance()->SetupGpa())
    {
        GpaHelper::DeleteInstance();
        return -1;
    }

    const gpa_example::GpaSampleApp& app = *(GpaHelper::Instance()->App());

    if (!GpaHelper::Instance()->OpenContext(gl_context, app.IncludeHwCounters()))
    {
        GpaHelper::DeleteInstance();
        return -1;
    }

    decltype(glXSwapBuffers)* glx_swap_buffers = nullptr;
    LOAD_LIBRARY_SYMBOL(glx_swap_buffers, glXSwapBuffers);
    if (nullptr == glx_swap_buffers)
    {
        LOG_ERROR(kGlError, "Unable to acquire glXSwapBuffers function pointer.\n");
        GpaHelper::DeleteInstance();
        return -1;
    }

    while (1)
    {
        XNextEvent(kDisplay, &event);

        if (event.type == Expose)
        {
            if (!CreateSessionAndEnableCounters())
            {
                GpaHelper::Instance()->CloseContext();
                GpaHelper::DeleteInstance();
                return -1;
            }

            ogl_viewport(0, 0, kWindowWidth, kWindowHeight);

            GpaHelper::Instance()->OnGpaSessionStart();

            for (unsigned int pass_iter = 0; pass_iter < GpaHelper::Instance()->GetPassRequired(); ++pass_iter)
            {
                GpaHelper::Instance()->OnPassStart();

                DrawClear();

                GpaHelper::Instance()->BeginSample();
                DrawTriangle();
                GpaHelper::Instance()->EndSample();

                GpaHelper::Instance()->OnPassEnd();

                glx_swap_buffers(kDisplay, kAppWindow);
            }

            GpaHelper::Instance()->OnGpaSessionEnd();

            static unsigned int profile_set = GpaHelper::Instance()->GetCurrentFrameCount();
            GpaHelper::Instance()->PrintGpaSampleResults(profile_set, app.Verify());

            GpaHelper::Instance()->DestroyGpaSession();

            GpaHelper::Instance()->IncrementFrameCounter();

            // Exit if this is the number of frames expected.
            if (app.NumberOfFrames() > 0 && GpaHelper::Instance()->GetCurrentFrameCount() == app.NumberOfFrames())
            {
                // All profiling is done, the app can be exited.
                GpaHelper::Instance()->CloseContext();
                GpaHelper::DeleteInstance();
                return 0;
            }

            int event_queue_length = XQLength(kDisplay);
            if (event_queue_length == 0)
            {
                XPutBackEvent(kDisplay, &event);
            }
        }
        else if (event.type == ClientMessage)
        {
            XClientMessageEvent client_message = event.xclient;
            if (*client_message.data.l == static_cast<long>(window_deletion))
            {
                RETURN_IF_FAILED(GpaHelper::Instance()->CloseContext());
                XFreeColormap(kDisplay, kWindowColorMap);
                XUnmapWindow(kDisplay, kAppWindow);
                XDestroyWindow(kDisplay, kAppWindow);
                XCloseDisplay(kDisplay);
                kDisplay = nullptr;
                GpaHelper::DeleteInstance();
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
        HDC device_context = GetDC(window_handle);
        if (nullptr == device_context && ERROR_SUCCESS != GetLastError())
        {
            LOG_ERROR(kWinError, "GetDC failed.");
            PostQuitMessage(-1);
            return -1;
        }

        const gpa_example::GpaSampleApp& app = *(GpaHelper::Instance()->App());

        if (nullptr == gl_context)
        {
            if (!GpaHelper::Instance()->SetupGpa())
            {
                PostQuitMessage(-1);
                return -1;
            }

            decltype(wglCreateContext)* wgl_create_context = nullptr;
            LOAD_LIBRARY_SYMBOL(wgl_create_context, wglCreateContext);
            if (nullptr == wgl_create_context)
            {
                LOG_ERROR(kGlError, "Unable to acquire wglCreateContext function pointer.");
                PostQuitMessage(-1);
                return -1;
            }

            gl_context = wgl_create_context(device_context);
            if (nullptr == gl_context && ERROR_SUCCESS != GetLastError())
            {
                LOG_ERROR(kWinError, "Unable to create context.");
                PostQuitMessage(-1);
                return -1;
            }

            decltype(wglMakeCurrent)* wgl_make_current = nullptr;
            LOAD_LIBRARY_SYMBOL(wgl_make_current, wglMakeCurrent);
            if (nullptr == wgl_make_current)
            {
                LOG_ERROR(kGlError, "Unable to acquire wglMakeCurrent function pointer.");
                PostQuitMessage(-1);
                return -1;
            }

            if (FAILED(wgl_make_current(device_context, gl_context)) && ERROR_SUCCESS != GetLastError())
            {
                LOG_ERROR(kWinError, "Unable to make context current.");
                PostQuitMessage(-1);
                return -1;
            }

            if (!GpaHelper::Instance()->OpenContext(gl_context, app.IncludeHwCounters()))
            {
                PostQuitMessage(-1);
                return -1;
            }
        }

        if (!CreateSessionAndEnableCounters())
        {
            GpaHelper::Instance()->CloseContext();
            PostQuitMessage(-1);
            return -1;
        }

        GpaHelper::Instance()->OnGpaSessionStart();

        for (unsigned int pass_iter = 0; pass_iter < GpaHelper::Instance()->GetPassRequired(); ++pass_iter)
        {
            GpaHelper::Instance()->OnPassStart();

            DrawClear();

            GpaHelper::Instance()->BeginSample();
            DrawTriangle();
            GpaHelper::Instance()->EndSample();

            GpaHelper::Instance()->OnPassEnd();

            SwapBuffers(device_context);
        }

        GpaHelper::Instance()->OnGpaSessionEnd();

        static unsigned int profile_set = GpaHelper::Instance()->GetCurrentFrameCount();
        GpaHelper::Instance()->PrintGpaSampleResults(profile_set, app.Verify());

        GpaHelper::Instance()->DestroyGpaSession();

        GpaHelper::Instance()->IncrementFrameCounter();

        // Exit if this is the number of frames expected.
        if (app.NumberOfFrames() > 0 && GpaHelper::Instance()->GetCurrentFrameCount() == app.NumberOfFrames())
        {
            // All profiling is done, the app can be exited.
            GpaHelper::Instance()->CloseContext();
            PostQuitMessage(0);
        }

        return 0;
    }

    case WM_DESTROY:
        // Destroy app here.
        RETURN_IF_FAILED(GpaHelper::Instance()->CloseContext());
        PostQuitMessage(0);
        return 0;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

int WINAPI WinMain(HINSTANCE instance_handle, HINSTANCE previous_instance, LPSTR cmd_line, int cmd_show)
{
    UNREFERENCED_PARAMETER(cmd_line);
    UNREFERENCED_PARAMETER(previous_instance);

    if (!GpaHelper::Instance()->ParseCommandLine(__argc, __argv))
    {
        GpaHelper::DeleteInstance();
        return -1;
    }

    if (!InitializeOpenGLFunctionPointers())
    {
        GpaHelper::DeleteInstance();
        return -1;
    }

    // Create app local window class and register it to system.
    WNDCLASSEX app_window_class = {sizeof(WNDCLASSEX),
                                   CS_HREDRAW | CS_VREDRAW,
                                   SampleWindowProc,
                                   0,
                                   0,
                                   instance_handle,
                                   NULL,  // Default icon.
                                   LoadCursor(nullptr, IDC_IBEAM),
                                   NULL,  // No brush.
                                   NULL,  // No menu.
                                   kWindowClassName.c_str(),
                                   NULL};

    ATOM window_register_success = RegisterClassEx(&app_window_class);

    DWORD win_error_code = ERROR_SUCCESS;
    if (NULL == window_register_success)
    {
        win_error_code = GetLastError();
        if (ERROR_SUCCESS != win_error_code)
        {
            LOG_ERROR(kWinError, "Unable to register windows class.");
        }

        // Failed to register window.
        GpaHelper::DeleteInstance();
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
                                 instance_handle,
                                 nullptr);

    if (nullptr == window_handle)
    {
        win_error_code = GetLastError();
        if (ERROR_SUCCESS != win_error_code)
        {
            LOG_ERROR(kWinError, "Unable to create window.");
        }

        // Failed to create window.
        GpaHelper::DeleteInstance();
        return -1;
    }

    //SetWindowLongPtr(window_handle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(GpaHelper));

    PIXELFORMATDESCRIPTOR pixel_format_desc = {sizeof(PIXELFORMATDESCRIPTOR),
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

    HDC device_context = GetDC(window_handle);
    if (nullptr == device_context)
    {
        win_error_code = GetLastError();
        if (ERROR_SUCCESS != win_error_code)
        {
            LOG_ERROR(kWinError, "Unable to get device context from windows.");
        }
        GpaHelper::DeleteInstance();
        return -1;
    }

    int pixel_format_index = ChoosePixelFormat(device_context, &pixel_format_desc);
    if (0 == pixel_format_index)
    {
        win_error_code = GetLastError();
        if (ERROR_SUCCESS != win_error_code)
        {
            LOG_ERROR(kWinError, "Unable to choose pixel format.");
        }
        GpaHelper::DeleteInstance();
        return -1;
    }

    if (FAILED(SetPixelFormat(device_context, pixel_format_index, &pixel_format_desc)))
    {
        win_error_code = GetLastError();
        if (ERROR_SUCCESS != win_error_code)
        {
            LOG_ERROR(kWinError, "Unable to set pixel format.");
        }
        GpaHelper::DeleteInstance();
        return -1;
    }

    if (FAILED(ShowWindow(window_handle, cmd_show)))
    {
        win_error_code = GetLastError();
        if (ERROR_SUCCESS != win_error_code)
        {
            LOG_ERROR(kWinError, "Unable to show window.");
        }
        GpaHelper::DeleteInstance();
        return -1;
    }

    // Main sample loop.
    MSG message = {};

    while (message.message != WM_QUIT)
    {
        // Process any messages in the queue.
        if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
    }

    if (FAILED(UnregisterClass(kWindowClassName.c_str(), instance_handle)))
    {
        win_error_code = GetLastError();
        if (ERROR_SUCCESS != win_error_code)
        {
            LOG_ERROR(kWinError, "Unable to unregister windows class.");
        }
        GpaHelper::DeleteInstance();
        return -1;
    }

    int return_code = GpaHelper::Instance()->has_error_occurred_ ? GpaHelper::Instance()->num_errors_occurred_ : 0;
    GpaHelper::DeleteInstance();
    return return_code;
}
#endif
