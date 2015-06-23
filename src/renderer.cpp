#include <cmath>

#include "renderer.h"

namespace RayCast {

	Renderer::Renderer(Graphics *g) {
		graphics=g;
	}

	Renderer::~Renderer() {
	}

	void Renderer::render(const ViewPoint &vPoint) {
		// Clear surface.
		graphics->clear(Colour(255, 0, 255)); // Clear screen (to pink, to help identify any undrawn regions).

		// Draw skybox.
		// TODO: this

		// Draw ground.
		// TODO: this

		// Draw blocks.
		// TODO: this

		// Draw objects.
		// TODO: this

		// Refresh screen.
		graphics->refresh();
	}

};
