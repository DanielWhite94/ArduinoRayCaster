#include <cassert>
#include <cstdio>
#include <cstdlib>

#include "graphics.h"

namespace RayCast {

	Graphics::Graphics() {
#		if RAYCAST_GRAPHICS_MODE == RAYCAST_GRAPHICS_MODE_SDL
			strokeDo=false;
			fillDo=false;

			// TODO: Throw exceptions instead?
			if(SDL_Init(SDL_INIT_VIDEO)<0) {
				printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
				exit(EXIT_FAILURE);
			}
			if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
				printf("Warning: Linear texture filtering not enabled!");
				exit(EXIT_FAILURE);
			}
			window=SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
			if(window==NULL) {
				printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
				exit(EXIT_FAILURE);
			}
			renderer=SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if(renderer==NULL) {
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				exit(EXIT_FAILURE);
			}
#		else
			assert(false);
#		endif
	}

	Graphics::~Graphics() {
#		if RAYCAST_GRAPHICS_MODE == RAYCAST_GRAPHICS_MODE_SDL
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
			window=NULL;
			renderer=NULL;

			SDL_Quit();
#		else
			assert(false);
#		endif
	}

	unsigned int Graphics::getWidth(void) {
#		if RAYCAST_GRAPHICS_MODE == RAYCAST_GRAPHICS_MODE_SDL
			int w=0, h=0;
			SDL_GetRendererOutputSize(renderer, &w, &h);
			return w;
#		else
			assert(false);
#		endif

		return 0;
	}

	unsigned int Graphics::getHeight(void) {
#		if RAYCAST_GRAPHICS_MODE == RAYCAST_GRAPHICS_MODE_SDL
			int w=0, h=0;
			SDL_GetRendererOutputSize(renderer, &w, &h);
			return h;
#		else
			assert(false);
#		endif

		return 0;
	}

	void Graphics::refresh(void) {
#		if RAYCAST_GRAPHICS_MODE == RAYCAST_GRAPHICS_MODE_SDL
			SDL_RenderPresent(renderer);
#		else
			assert(false);
#		endif
	}

	void Graphics::clear(const Colour &colour) {
#		if RAYCAST_GRAPHICS_MODE == RAYCAST_GRAPHICS_MODE_SDL
			bool oldstrokeDo=strokeDo;
			Colour oldstrokeColour=strokeColour;

			SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, 0xFF);
			SDL_RenderClear(renderer);

			strokeDo=oldstrokeDo;
			strokeColour=oldstrokeColour;
#		else
			assert(false);
#		endif
	}

	void Graphics::stroke(const Colour &colour) {
#		if RAYCAST_GRAPHICS_MODE == RAYCAST_GRAPHICS_MODE_SDL
			strokeDo=true;
			strokeColour=colour;
			SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, 0xFF);
#		else
			assert(false);
#		endif
	}

	void Graphics::noStroke(void) {
#		if RAYCAST_GRAPHICS_MODE == RAYCAST_GRAPHICS_MODE_SDL
			strokeDo=false;
#		else
			assert(false);
#		endif
	}

	void Graphics::fill(const Colour &colour) {
#		if RAYCAST_GRAPHICS_MODE == RAYCAST_GRAPHICS_MODE_SDL
			fillDo=true;
			fillColour=colour;
			// TODO: this
#		else
			assert(false);
#		endif
	}

	void Graphics::noFill(void) {
#		if RAYCAST_GRAPHICS_MODE == RAYCAST_GRAPHICS_MODE_SDL
			fillDo=false;
#		else
			assert(false);
#		endif
	}

	void Graphics::point(unsigned x, unsigned y) {
#		if RAYCAST_GRAPHICS_MODE == RAYCAST_GRAPHICS_MODE_SDL
			SDL_RenderDrawPoint(renderer, (int)x, (int)y);
#		else
			assert(false);
#		endif
	}

	void Graphics::line(unsigned x1, unsigned y1, unsigned x2, unsigned y2) {
#		if RAYCAST_GRAPHICS_MODE == RAYCAST_GRAPHICS_MODE_SDL
			SDL_RenderDrawLine(renderer, (int)x1, (int)y1, (int)x2, (int)y2);
#		else
			assert(false);
#		endif
	}

	void Graphics::rect(unsigned x, unsigned y, unsigned w, unsigned h) {
#		if RAYCAST_GRAPHICS_MODE == RAYCAST_GRAPHICS_MODE_SDL
		// Draw rectangle.
		if (fillDo) {
			SDL_SetRenderDrawColor(renderer, fillColour.r, fillColour.g, fillColour.b, 0xFF);
			SDL_Rect rect={(int)x, (int)y, (int)w, (int)h};
			SDL_RenderFillRect(renderer, &rect);
			SDL_SetRenderDrawColor(renderer, strokeColour.r, strokeColour.g, strokeColour.b, 0xFF); // Reset colour.
		}

		// Draw outline:
		if (strokeDo) {
			this->line(x, y, x+w, y); // Top,
			this->line(x+w-1, y, x+w-1, y+h); // right,
			this->line(x, y+h-1, x+w, y+h-1); // bottom and
			this->line(x, y, x, y+h); // left.
		}
#		else
			assert(false);
#		endif
	}

};
