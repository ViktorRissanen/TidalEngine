#include "pch.h"
#include "console.h"

bool console::create() {
	bool successful = AllocConsole();
	if (successful) {
		HWND handle = GetConsoleWindow();
		SetWindowLong(handle, GWL_STYLE, GetWindowLong(handle, GWL_STYLE) & ~WS_SYSMENU); 
		SetConsoleTitle(L"TidalEngine Console");
	}
	return successful;
}

void console::destroy() {
	FreeConsole();
}

void console::set_visible(bool visible) {
	ShowWindow(GetConsoleWindow(), visible ? SW_SHOW : SW_HIDE);
}

bool console::is_visible() {
	return IsWindowVisible(GetConsoleWindow());
}

void console::write(const std::string &text) {
	WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), text.c_str(), (DWORD)text.size(), nullptr, nullptr);
}

std::string console::read() {
	CHAR buffer[MAX_PATH];
	DWORD chars_read = 0;
	ReadConsoleA(GetStdHandle(STD_INPUT_HANDLE), buffer, MAX_PATH, &chars_read, nullptr);
	return std::string(buffer, chars_read);
}
