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
#include <Lums/Window.hpp>

using namespace lm;

static Window* currentWin;

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
    	wc.style         = CS_NOCLOSE;
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
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, w, h,
        NULL, NULL, hInstance, NULL);
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
    _windowHandle = hwnd;
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
	UpdateWindow(static_cast<HWND>(_windowHandle));
}

Window::~Window()
{
    DestroyWindow(static_cast<HWND>(_windowHandle));
}
