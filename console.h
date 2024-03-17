#pragma once

namespace console {

	bool initialize();
	void cleanup();

	struct Console {
		const bool successful;

		Console() : successful{ initialize() } {}
		~Console() { cleanup(); }
	};

	void set_visible(bool visible);
	bool is_visible();
	void write(const std::string &text);
	std::string read();
}