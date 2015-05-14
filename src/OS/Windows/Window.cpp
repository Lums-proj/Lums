/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Windows/Window.cpp                             oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include <windows.h>
#include <LumsInclude/Graphics/Window.hpp>

using namespace lm;

static Window* currentWin;

static const PIXELFORMATDESCRIPTOR pfd =
{
    sizeof(PIXELFORMATDESCRIPTOR),
    1,
    PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
    PFD_TYPE_RGBA,
    32,
    0, 0, 0, 0, 0, 0,
    0,
    0,
    0,
    0, 0, 0, 0,
    32,
    8,
    0,
    PFD_MAIN_PLANE,
    0,
    0, 0, 0
};

static LRESULT CALLBACK
LMWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    Event event;

    switch(msg)
    {
        case WM_KEYDOWN:
            event.type = Event::Type::KeyDown;
            event.key = static_cast<Key>(wParam);
            currentWin->pushEvent(event);
            break;
        case WM_KEYUP:
            event.type = Event::Type::KeyUp;
            event.key = static_cast<Key>(wParam);
            currentWin->pushEvent(event);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

Window::Window(int w, int h, const char* name)
{
    HINSTANCE hInstance = GetModuleHandle(NULL);
    static bool launched = false;

    if (!launched)
    {
        WNDCLASSEX wc;

        wc.cbSize        = sizeof(WNDCLASSEX);
        wc.style         = CS_NOCLOSE | CS_OWNDC;
        wc.lpfnWndProc   = LMWindowProc;
        wc.cbClsExtra    = 0;
        wc.cbWndExtra    = 0;
        wc.hInstance     = hInstance;
        wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
        wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
        wc.lpszMenuName  = NULL;
        wc.lpszClassName = "LMWindow";
        wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);
        RegisterClassEx(&wc);
        launched = true;
    }

    HWND hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        "LMWindow",
        name,
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT, w, h,
        NULL, NULL, hInstance, NULL);
    _windowHandle = hwnd;

    HDC dc = GetWindowDC(hwnd);
    int pf = ChoosePixelFormat(dc, &pfd);

    SetPixelFormat(dc, pf, &pfd);

    HGLRC gl = wglCreateContext(dc);
    wglMakeCurrent(dc, gl);
    
    _openGlHandle = gl;

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
    ReleaseDC(hwnd, dc);
}

void   
Window::pumpEvent()
{
    currentWin = this;
    MSG msg;

    while (PeekMessage(&msg, static_cast<HWND>(_windowHandle), 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void   
Window::swap()
{
    HWND hwnd = static_cast<HWND>(_windowHandle);
    HDC dc = GetWindowDC(hwnd);
    SwapBuffers(dc);
    UpdateWindow(hwnd);
    ReleaseDC(hwnd, dc);
}

Window::~Window()
{
    DestroyWindow(static_cast<HWND>(_windowHandle));
}
