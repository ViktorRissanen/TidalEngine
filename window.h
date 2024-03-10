#pragma once

namespace window {

	bool create();
	void destroy();

	extern HWND handle;

	struct Window {
		const bool successful;

		Window() : successful{ create() } {}
		~Window() { destroy(); }
	};

	bool resize(int width, int height);
	void set_borderless(bool borderless);
	void set_fullscreen(bool fullscreen);
}