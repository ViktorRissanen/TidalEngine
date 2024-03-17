#pragma once

namespace window {

	bool create();
	void destroy();

	extern HWND handle;

	const int native_width = GetSystemMetrics(SM_CXSCREEN);
	const int native_height = GetSystemMetrics(SM_CYSCREEN);

	struct Window {
		const bool successful;
		

		Window() : successful{ create() } {}
		~Window() { destroy(); }
	};
	bool resize(int width, int height);
	bool is_exclusive_fullscreen();
	void lock_cursor(bool lock);
	void set_borderless(bool borderless);
	// Locked fullscreen, ignores other applications unless the window is minimized or closed
	void set_exclusive_fullscreen();
}