#pragma once

namespace console {

	bool create();
	void destroy();

	struct Console {
		const bool successful;

		Console() : successful{ create() } {}
		~Console() { destroy(); }
	};

	void set_visible(bool visible);
	bool is_visible();
	void write(const std::string &text);
	std::string read();
}