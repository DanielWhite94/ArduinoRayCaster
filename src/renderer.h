#ifndef RAYCAST_RENDERER_H
#define RAYCAST_RENDERER_H

#include "graphics.h"
#include "viewpoint.h"

namespace RayCast {

	class Renderer {
	public:
		Renderer(Graphics *g);
		~Renderer();

		void render(const ViewPoint &vPoint);

	private:
		Graphics *graphics;
	};
};

#endif
