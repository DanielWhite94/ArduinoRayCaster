#ifndef RAYCAST_RENDERER_H
#define RAYCAST_RENDERER_H

#include <Esplora.h>

#include "level.h"
#include "viewpoint.h"

namespace RayCast {

	class Renderer {
	public:
		Renderer();
		~Renderer();

		void render(const Level &level, const ViewPoint &vPoint);

#ifdef EXTRA
		void renderTopDown(const ViewPoint &vPoint);
#endif

	private:
		static Fixed computeDisplayHeight(const Fixed &blockHeight, const Fixed &distance);
	};
};

#endif
