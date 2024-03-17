#include "pch.h"
#include "window.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

namespace window {
    extern HWND handle = nullptr;
}

bool window::initialize() {
    WNDCLASSEXW wcex = {};
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wcex.lpfnWndProc = WndProc;
    wcex.hInstance = GetModuleHandle(NULL);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW);
    wcex.lpszClassName = L"TidalEngine";
    RegisterClassExW(&wcex);

    const int WIDTH = 1280;
    const int HEIGHT = 720;
    handle = CreateWindow(wcex.lpszClassName, wcex.lpszClassName,
                             WS_OVERLAPPEDWINDOW,
                             CW_USEDEFAULT, CW_USEDEFAULT, WIDTH, HEIGHT, NULL, NULL, GetModuleHandle(NULL), NULL);
    if (!handle) return false;

    ShowWindow(handle, 1);
    UpdateWindow(handle);

	return true;
}

void window::cleanup() {
    if(!handle) return;

    DestroyWindow(handle);
    handle = nullptr;
}

bool window::resize(int width, int height) {
    if(!handle) return false;
    //TODO: Handle fullscreen case differently if necessary

    //Adjust the window size to fit the client area
    RECT rect = { 0, 0, width, height };
    AdjustWindowRect(&rect, GetWindowLong(handle, GWL_STYLE), FALSE); //GetWindowLong returns the current window style

    //Calculate the position of the window so that it remains centered
    int x = (native_width - (rect.right - rect.left)) / 2;
    int y = (native_height - (rect.bottom - rect.top)) / 2;

    //Resize the window
    SetWindowPos(handle, NULL, x, y, rect.right - rect.left, rect.bottom - rect.top, SWP_NOMOVE | SWP_NOZORDER);
    return true;
}

bool window::is_exclusive_fullscreen() {
	if (!handle) return false;

    //Check if the window is currently borderless
	DWORD style = GetWindowLong(handle, GWL_STYLE);
	if(!(style & WS_POPUP)) return false;

    //Check if window covers the entire screen
    RECT rect;
    GetWindowRect(handle, &rect);
    if(rect.left != 0 || rect.top != 0 || rect.right != native_width || rect.bottom != native_height) return false;

    return true;
}

void window::lock_cursor(bool lock) {
    if (!handle) return;

    if (lock) {
        RECT rect;
        GetClientRect(handle, &rect);
        MapWindowPoints(handle, NULL, (LPPOINT)&rect, 2);
        ClipCursor(&rect);
    } else {
        ClipCursor(NULL);
    }
}

void window::set_borderless(bool borderless) {
    if (!handle) return;

    RECT rect;
    GetWindowRect(handle, &rect);
    if (borderless) {
		SetWindowLongPtr(handle, GWL_STYLE, WS_POPUP);
		SetWindowPos(handle, NULL, 0, 0, rect.right - rect.left, rect.bottom - rect.top, SWP_FRAMECHANGED | SWP_SHOWWINDOW);
    } else {
		SetWindowLongPtr(handle, GWL_STYLE, WS_OVERLAPPEDWINDOW);
		SetWindowPos(handle, NULL, 0, 0, rect.right - rect.left, rect.bottom - rect.top, SWP_FRAMECHANGED | SWP_SHOWWINDOW);
	}
}

void window::set_exclusive_fullscreen() {
    if (!handle) return;

    SetWindowLongPtr(handle, GWL_STYLE, WS_POPUP);
    SetWindowPos(handle, NULL, 0, 0, native_width, native_height, SWP_FRAMECHANGED | SWP_SHOWWINDOW);

    DEVMODE dm_screen_settings = {};
    dm_screen_settings.dmSize = sizeof(dm_screen_settings);
    dm_screen_settings.dmPelsWidth = native_width;
    dm_screen_settings.dmPelsHeight = native_height;
    dm_screen_settings.dmBitsPerPel = 32;
    dm_screen_settings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
    ChangeDisplaySettings(&dm_screen_settings, CDS_FULLSCREEN);
    lock_cursor(true);
}
