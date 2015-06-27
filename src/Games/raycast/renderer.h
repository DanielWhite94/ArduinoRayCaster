#ifndef RAYCAST_RENDERER_H
#define RAYCAST_RENDERER_H

#include <Esplora.h>
#include "viewpoint.h"

namespace RayCast {

	class Renderer {
	public:
		Renderer();
		~Renderer();

		void render(const ViewPoint &vPoint);

#ifdef EXTRA
		void renderTopDown(const ViewPoint &vPoint);
#endif

	private:
	};
};

#endif
