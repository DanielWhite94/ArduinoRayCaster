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

};
