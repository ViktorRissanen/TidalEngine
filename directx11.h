#pragma once

namespace directx11 {

	bool initialize();
	void cleanup();
	void Render();
	
	struct Graphics {
		const bool successful;

		Graphics() : successful{ initialize() } {}
		~Graphics() { cleanup(); }
	};	
}