#include "pch.h"
#include "console.h"
#include "window.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ LPWSTR, _In_ int nCmdShow) {
    console::Console _console{};
    if (_console.successful) {
        console::set_visible(true);
        console::write("Did you pray today?\n");
    }

    window::Window _window{};
    if (!_window.successful) return EXIT_FAILURE;

    //window::resize(1920, 1080);

    MSG msg = {};
    bool should_run = true;
    while (should_run) {
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            if (msg.message == WM_QUIT) {
                should_run = false;
            }
        }
    }
    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return EXIT_SUCCESS;
}