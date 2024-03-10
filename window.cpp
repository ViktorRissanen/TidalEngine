#include "pch.h"
#include "window.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

namespace window {
    extern HWND handle = nullptr;
}

bool window::create() {
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
                             WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
                             CW_USEDEFAULT, CW_USEDEFAULT, WIDTH, HEIGHT, NULL, NULL, GetModuleHandle(NULL), NULL);
    if (!handle) return false;

    ShowWindow(handle, 1);
    UpdateWindow(handle);

	return true;
}

void window::destroy() {
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
    int x = (GetSystemMetrics(SM_CXSCREEN) - (rect.right - rect.left)) / 2;
    int y = (GetSystemMetrics(SM_CYSCREEN) - (rect.bottom - rect.top)) / 2;

    //Resize the window
    SetWindowPos(handle, NULL, x, y, rect.right - rect.left, rect.bottom - rect.top, SWP_NOMOVE | SWP_NOZORDER);
    return true;
}

void window::set_borderless(bool borderless) {
}

void window::set_fullscreen(bool fullscreen) {

}
