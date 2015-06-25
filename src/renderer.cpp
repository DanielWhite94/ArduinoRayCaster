#include <cmath>

#include "renderer.h"

namespace RayCast {

	Renderer::Renderer(Graphics *g) {
		graphics=g;
	}

	Renderer::~Renderer() {
	}

	void Renderer::render(const ViewPoint &vPoint) {
		int screenW=graphics->getWidth();
		int screenH=graphics->getHeight();

		// Clear surface.
		graphics->clear(Colour(255, 0, 255)); // Clear screen (to pink, to help identify any undrawn regions).

		// Draw sky and ground.
		graphics->noStroke();

		graphics->fill(Colour(0,0,255));
		graphics->rect(0, 0, screenW, screenH/2);

		graphics->fill(Colour(0,255,0));
		graphics->rect(0, screenH/2, screenW, screenH/2);

		// Draw blocks.
		// TODO: this

		// Draw objects.
		// TODO: this

		// Refresh screen.
		graphics->refresh();
	}

};
