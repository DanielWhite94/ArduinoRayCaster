#ifndef RAYCAST_RAYCAST_GRAPHICS_H
#define RAYCAST_RAYCAST_GRAPHICS_H

#define RAYCAST_GRAPHICS_MODE_TFT 1
#define RAYCAST_GRAPHICS_MODE_SDL 2

#include <cstdint>

#if RAYCAST_GRAPHICS_MODE == RAYCAST_GRAPHICS_MODE_SDL
#	include <SDL2/SDL.h>
#endif

namespace RayCast {

	struct Colour {
		uint8_t r,g,b;

		Colour(uint8_t R=0, uint8_t G=0, uint8_t B=0) {
			r=R; b=B; g=G;
		}
	};

	class Graphics {
	public:
		Graphics();
		~Graphics();

		unsigned int getWidth(void);
		unsigned int getHeight(void);

		void refresh(void);

		void clear(const Colour &colour);

		void stroke(const Colour &colour); // Set colour of lines and borders around shapes.
		void noStroke(void);

		void fill(const Colour &colour); // Set fill colour of shapes and text.
		void noFill(void);

		void point(unsigned x, unsigned y);
		void line(unsigned x1, unsigned y1, unsigned x2, unsigned y2);
		void rect(unsigned x, unsigned y, unsigned w, unsigned h);
	private:
#		if RAYCAST_GRAPHICS_MODE == RAYCAST_GRAPHICS_MODE_SDL
			bool strokeDo, fillDo;
			Colour strokeColour, fillColour;

			SDL_Window *window;
			SDL_Renderer *renderer;
#		endif
	};

};

#endif
