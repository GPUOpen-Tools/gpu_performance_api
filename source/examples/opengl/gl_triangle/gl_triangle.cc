//==============================================================================
// Copyright (c) 2019-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief GL triangle.
//==============================================================================

#include <iostream>

#define GLUT_NO_LIB_PRAGMA

#ifdef _WIN32
#pragma warning(disable : 4505)
#include <windows.h>
#include <GL/gL.h>
#include <GL/gLext.h>
#include <GL/wglext.h>
#else
#include <GL/glx.h>
#include <X11/Xutil.h>
#endif

#include "gpu_perf_api_counter_generator/gl_entry_points.h"

#include "gpu_perf_api_common/gpa_common_defs.h"

#include "examples/opengl/gl_triangle/gpa_helper.h"

using namespace ogl_utils;

/// @brief Struct to hold values of command line arguments.
struct CommandLineArgs
{
    /// Number of frames to execute -- zero indicates that the app should run until the user closes it.
    unsigned int num_frames = 0;

    /// Flag indicating if some counter values should be verified (experimental).
    bool verify_counters = false;

    /// Flag indicating whether the application should verify some counter values and confirm successful results.
    bool confirm_success = false;

    /// Flag indicating whether or not to include hardware counters in non-internal builds.
    bool include_hw_counters = false;

    /// Flag indicating whether the counter file is given or not.
    bool counter_provided = false;

    /// Counter file name.
    std::string counter_file_name;
};

CommandLineArgs command_line_args;

const unsigned int kWindowWidth     = 800;
const unsigned int kWindowHeight    = 800;
const std::wstring kWindowClassName = L"OpenGL Triangle Sample App";

#ifdef _LINUX
Display* kDisplay;
Window   kAppWindow;
Colormap kWindowColorMap;
#else
HWND window_handle;
#endif

GlContext gl_context = nullptr;

decltype(glBegin)*     ogl_begin      = nullptr;
decltype(glEnd)*       ogl_end        = nullptr;
decltype(glFinish)*    ogl_finish     = nullptr;
decltype(glColor3f)*   ogl_color_3f   = nullptr;
decltype(glVertex3fv)* ogl_vertex_3fv = nullptr;
decltype(glViewport)*  ogl_viewport   = nullptr;

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

#define RETURN_IF_FAILED(X) \
    if (!X)                 \
        return -1;

int DrawTriangle()
{
    if (command_line_args.num_frames > 0 && GpaHelper::Instance()->GetCurrentFrameCount() == command_line_args.num_frames)
    {
        GpaHelper::Instance()->CloseContext();
        if (GpaHelper::Instance()->gpa_has_error_occured_)
        {
            exit(1);
        }

        exit(0);
    }

    RETURN_IF_FAILED(GpaHelper::Instance()->CreateGpaSession());

    if (command_line_args.counter_provided)
    {
        std::fstream counter_file_stream;
        counter_file_stream.open(command_line_args.counter_file_name.c_str(), std::ios_base::in);
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
                RETURN_IF_FAILED(GpaHelper::Instance()->EnableCounterByName(it->c_str()));
            }
        }
        else
        {
            std::stringstream error;
            error << "Unable to open Counter file " << command_line_args.counter_file_name.c_str() << " . Not enabling any counters";
            LOG_ERROR(kGeneralError, error.str().c_str());
        }
    }
    else
    {
#ifndef AMDT_INTERNAL
        RETURN_IF_FAILED(GpaHelper::Instance()->EnableAllCounters());
#else
        RETURN_IF_FAILED(GpaHelper::Instance()->EnableCounterByName("GPUTime"));
#endif
    }
    RETURN_IF_FAILED(GpaHelper::Instance()->OnGpaSessionStart());

    GL_FUNC(ogl_flush(), "glFlush failed", __LINE__);
    GL_FUNC(ogl_finish(), "glFinish failed", __LINE__);

    unsigned int pass_iter = 0u;

    do
    {
        RETURN_IF_FAILED(GpaHelper::Instance()->OnPassStart());
        RETURN_IF_FAILED(GpaHelper::Instance()->BeginSample());
        GL_FUNC(ogl_flush(), "glFlush failed", __LINE__);
        GL_FUNC(ogl_finish(), "glFinish failed", __LINE__);
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
        GL_FUNC(ogl_flush(), "glFlush failed", __LINE__);
        GL_FUNC(ogl_finish(), "glFinish failed", __LINE__);
        RETURN_IF_FAILED(GpaHelper::Instance()->EndSample());
        RETURN_IF_FAILED(GpaHelper::Instance()->OnPassEnd());
        pass_iter++;
    } while (pass_iter < GpaHelper::Instance()->GetPassRequired());

    GL_FUNC(ogl_flush(), "glFlush failed", __LINE__);
    GL_FUNC(ogl_finish(), "glFinish failed", __LINE__);

    RETURN_IF_FAILED(GpaHelper::Instance()->OnGpaSessionEnd());

    unsigned int profile_set = GpaHelper::Instance()->GetCurrentFrameCount();
    RETURN_IF_FAILED(GpaHelper::Instance()->PrintGpaSampleResults(profile_set, command_line_args.verify_counters || command_line_args.confirm_success));
    RETURN_IF_FAILED(GpaHelper::Instance()->DestroyGpaSession());

    GpaHelper::Instance()->IncrementFrameCounter();
    return 0;
}

/// @brief Print command line usage information.
void Usage()
{
    std::cout << "GLTriangle [--numberofframes #] [--verify] [--confirmsuccess] [--counterfile <file>] [--includehwcounters]" << std::endl << std::endl;
    std::cout << "  --numberofframes #: Renders the specified number of frames before exiting; if used with --verify then # must be a multiple of the number "
                 "of passes needed"
              << std::endl;
    std::cout << "  --verify: Application will verify a few counter values (experimental)" << std::endl;
    std::cout << "  --confirmsuccess: Implies --verify and confirms successful counter values in addition to errors" << std::endl;
    std::cout << "  --counterfile <file>: File containing the list of counters to profile" << std::endl;
    std::cout << "  --includehwcounters: Public hardware counters will be enabled in non-internal builds" << std::endl;
}

/// @brief Parse Command line arguments.
///
/// @param [in] argc The number of arguments.
/// @param [in] argv The array of arguments.
///
/// @retval true If the arguments could be parsed.
/// @retval false On error.
bool ParseCommandLine(int argc, char* argv[])
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

                iss >> command_line_args.num_frames;

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
            command_line_args.verify_counters = true;
        }
        else if (0 == this_arg.compare("--confirmsuccess"))
        {
            command_line_args.confirm_success = true;
        }
        else if (0 == this_arg.compare("--includehwcounters"))
        {
            command_line_args.include_hw_counters = true;
        }
        else if (0 == this_arg.compare("--counterfile"))
        {
            i++;

            if (i < argc)
            {
                std::istringstream iss(argv[i]);

                iss >> command_line_args.counter_file_name;

                if (iss.fail())
                {
                    success = false;
                }
                else
                {
                    command_line_args.counter_provided = true;
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

bool InitializeOpenGLFunctionPointers()
{
    if (!InitializeGlCoreFunctions())
    {
        LOG_ERROR(kGlError, "Unable to initialize OpenGL function core functions.");
        return false;
    }

    LOAD_LIBRARY_SYMBOL(ogl_begin, glBegin);
    if (nullptr == ogl_begin)
    {
        LOG_ERROR(kGlError, "Unable to obtain glBegin function pointer.");
        return false;
    }

    LOAD_LIBRARY_SYMBOL(ogl_end, glEnd);
    if (nullptr == ogl_end)
    {
        LOG_ERROR(kGlError, "Unable to obtain glEnd function pointer.");
        return false;
    }

    LOAD_LIBRARY_SYMBOL(ogl_finish, glFinish);
    if (nullptr == ogl_finish)
    {
        LOG_ERROR(kGlError, "Unable to obtain glFinish function pointer.");
        return false;
    }

    LOAD_LIBRARY_SYMBOL(ogl_color_3f, glColor3f);
    if (nullptr == ogl_color_3f)
    {
        LOG_ERROR(kGlError, "Unable to obtain glColor3f function pointer.");
        return false;
    }

    LOAD_LIBRARY_SYMBOL(ogl_vertex_3fv, glVertex3fv);
    if (nullptr == ogl_vertex_3fv)
    {
        LOG_ERROR(kGlError, "Unable to obtain glVertex3fv function pointer.");
        return false;
    }

    LOAD_LIBRARY_SYMBOL(ogl_viewport, glViewport);
    if (nullptr == ogl_viewport)
    {
        LOG_ERROR(kGlError, "Unable to obtain glViewport function pointer.");
        return false;
    }

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

void CreateWindowAndContext()
{
    kDisplay = XOpenDisplay(nullptr);

    GLint gl_attributes[] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None};

    if (nullptr != kDisplay)
    {
        XSetErrorHandler(&XGLTriangleErrorHandler);
        Window root_window    = DefaultRootWindow(kDisplay);
        int    default_screen = DefaultScreen(kDisplay);

        decltype(glXChooseVisual)* glx_choose_visual = nullptr;
        LOAD_LIBRARY_SYMBOL(glx_choose_visual, glXChooseVisual);
        if (nullptr == glx_choose_visual)
        {
            LOG_ERROR(kGlError, "Unable to acquire glXChooseVisual function pointer.\n");
            return;
        }
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
        LOAD_LIBRARY_SYMBOL(glx_create_context, glXCreateContext);
        if (nullptr == glx_create_context)
        {
            LOG_ERROR(kGlError, "Unable to acquire glXCreateContext function pointer.\n");
            return;
        }
        gl_context = glx_create_context(kDisplay, visual_info, nullptr, GL_TRUE);

        decltype(glXMakeCurrent)* glx_make_current = nullptr;
        LOAD_LIBRARY_SYMBOL(glx_make_current, glXMakeCurrent);
        if (nullptr == glx_make_current)
        {
            LOG_ERROR(kGlError, "Unable to acquire glXMakeCurrent function pointer.\n");
            return;
        }
        glx_make_current(kDisplay, kAppWindow, gl_context);
    }
}

int main(int argc, char* argv[])
{
    if (!ParseCommandLine(argc, argv))
    {
        Usage();
        return -1;
    }

    if (!InitializeOpenGLFunctionPointers())
    {
        LOG_ERROR(kGlError, "Failed to initialize OpenGL function pointers.");
        return -1;
    }

    int width  = 500;
    int height = 250;
    ogl_viewport(0, 0, width, height);

    CreateWindowAndContext();

    Atom window_deletion = XInternAtom(kDisplay, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(kDisplay, kAppWindow, &window_deletion, 1);

    XEvent event;
    RETURN_IF_FAILED(GpaHelper::Instance()->SetupGpa());
    RETURN_IF_FAILED(GpaHelper::Instance()->OpenContext(gl_context, command_line_args.include_hw_counters));

    decltype(glXSwapBuffers)* glx_swap_buffers = nullptr;
    LOAD_LIBRARY_SYMBOL(glx_swap_buffers, glXSwapBuffers);
    if (nullptr == glx_swap_buffers)
    {
        LOG_ERROR(kGlError, "Unable to acquire glXSwapBuffers function pointer.\n");
        return -1;
    }

    while (1)
    {
        XNextEvent(kDisplay, &event);

        if (event.type == Expose)
        {
            ogl_viewport(0, 0, 500, 500);
            DrawTriangle();
            glx_swap_buffers(kDisplay, kAppWindow);
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
        }

        if (nullptr == gl_context)
        {
            RETURN_IF_FAILED(GpaHelper::Instance()->SetupGpa());

            decltype(wglCreateContext)* wgl_create_context = nullptr;
            LOAD_LIBRARY_SYMBOL(wgl_create_context, wglCreateContext);
            if (nullptr == wgl_create_context)
            {
                LOG_ERROR(kGlError, "Unable to acquire wglCreateContext function pointer.");
                return false;
            }

            gl_context = wgl_create_context(device_context);
            if (nullptr == gl_context && ERROR_SUCCESS != GetLastError())
            {
                LOG_ERROR(kWinError, "Unable to create context.");
            }

            decltype(wglMakeCurrent)* wgl_make_current = nullptr;
            LOAD_LIBRARY_SYMBOL(wgl_make_current, wglMakeCurrent);
            if (nullptr == wgl_make_current)
            {
                LOG_ERROR(kGlError, "Unable to acquire wglMakeCurrent function pointer.");
                return false;
            }

            if (FAILED(wgl_make_current(device_context, gl_context)) && ERROR_SUCCESS != GetLastError())
            {
                LOG_ERROR(kWinError, "Unable to make context current.");
            }

            RETURN_IF_FAILED(GpaHelper::Instance()->OpenContext(gl_context, command_line_args.include_hw_counters));
        }

        if (DrawTriangle() == -1)
        {
            return -1;
        }

        SwapBuffers(device_context);
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

    if (!ParseCommandLine(__argc, __argv))
    {
        Usage();
        return -1;
    }

    if (!InitializeOpenGLFunctionPointers())
    {
        LOG_ERROR(kGlError, "Failed to initialize OpenGL function pointers.");
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
        return -1;
    }

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
        return -1;
    }

    if (FAILED(SetPixelFormat(device_context, pixel_format_index, &pixel_format_desc)))
    {
        win_error_code = GetLastError();
        if (ERROR_SUCCESS != win_error_code)
        {
            LOG_ERROR(kWinError, "Unable to set pixel format.");
        }
        return -1;
    }

    if (FAILED(ShowWindow(window_handle, cmd_show)))
    {
        win_error_code = GetLastError();
        if (ERROR_SUCCESS != win_error_code)
        {
            LOG_ERROR(kWinError, "Unable to show window.");
        }
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
        return -1;
    }

    return GpaHelper::Instance()->gpa_has_error_occured_ ? -1 : 0;
}
#endif