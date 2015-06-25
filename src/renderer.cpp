#include <cmath>

#include "renderer.h"

namespace RayCast {

	Renderer::Renderer() {
	}

	Renderer::~Renderer() {
	}

	void Renderer::render(const ViewPoint &vPoint) {
		int screenW=EsploraTFT.width();
		int screenH=EsploraTFT.height();

		// Clear surface.
		EsploraTFT.background(255, 0, 255); // Clear screen (to pink, to help identify any undrawn regions).

		// Draw sky and ground.
		EsploraTFT.noStroke();

		EsploraTFT.fill(0,0,255);
		EsploraTFT.rect(0, 0, screenW, screenH/2);

		EsploraTFT.fill(0,255,0);
		EsploraTFT.rect(0, screenH/2, screenW, screenH/2);

		// Draw blocks.
		// TODO: this

		// Draw objects.
		// TODO: this
	}

};
