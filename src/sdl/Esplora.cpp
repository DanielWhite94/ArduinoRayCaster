#include <cassert>
#include <cstdio>
#include <cstdlib>

#include "Esplora.h"

esploraTft EsploraTFT;

esploraTft::esploraTft() {
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
}

esploraTft::~esploraTft() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window=NULL;
	renderer=NULL;

	SDL_Quit();
}

void esploraTft::begin(void) {
}

void esploraTft::background(int r, int g, int b) {
	assert(r>=0 && r<256);
	assert(r>=0 && r<256);
	assert(r>=0 && r<256);

	SDL_SetRenderDrawColor(renderer, r, g, b, 0xFF);
	SDL_Rect rect={0, 0, this->width(), this->height()};
	SDL_RenderFillRect(renderer, &rect);
	SDL_SetRenderDrawColor(renderer, strokeR, strokeG, strokeB, 0xFF); // Reset colour.

	this->refresh();
}

void esploraTft::stroke(int r, int g, int b) {
	assert(r>=0 && r<256);
	assert(r>=0 && r<256);
	assert(r>=0 && r<256);

	strokeDo=true;
	strokeR=r;
	strokeG=g;
	strokeB=b;
	SDL_SetRenderDrawColor(renderer, strokeR, strokeG, strokeB, 0xFF);
}

void esploraTft::noStroke(void) {
	strokeDo=false;
}

void esploraTft::fill(int r, int g, int b) {
	assert(r>=0 && r<256);
	assert(r>=0 && r<256);
	assert(r>=0 && r<256);

	fillDo=true;
	fillR=r;
	fillG=g;
	fillB=b;
}

void esploraTft::noFill(void) {
	fillDo=false;
}

void esploraTft::point(int x, int y) {
	if (!strokeDo)
		return;

	SDL_RenderDrawPoint(renderer, x, y);

	this->refresh();
}

void esploraTft::line(int x1, int y1, int x2, int y2) {
	if (!strokeDo)
		return;

	SDL_RenderDrawLine(renderer, x1, y1, x2, y2);

	this->refresh();
}

void esploraTft::rect(int x, int y, int w, int h) {
	// Draw rectangle.
	if (fillDo) {
		SDL_SetRenderDrawColor(renderer, fillR, fillG, fillB, 0xFF);
		SDL_Rect rect={x, y, w, h};
		SDL_RenderFillRect(renderer, &rect);
		SDL_SetRenderDrawColor(renderer, strokeR, strokeG, strokeB, 0xFF); // Reset colour.
	}

	// Draw outline:
	if (strokeDo) {
		this->line(x, y, x+w, y); // Top,
		this->line(x+w-1, y, x+w-1, y+h); // right,
		this->line(x, y+h-1, x+w, y+h-1); // bottom and
		this->line(x, y, x, y+h); // left.
	}

	if (fillDo || strokeDo)
		this->refresh();
}

void esploraTft::circle(int x, int y, int radius) {
	// TODO: this
}

int esploraTft::width(void) {
	int w=0, h=0;
	SDL_GetRendererOutputSize(renderer, &w, &h);
	return w;
}

int esploraTft::height(void) {
	int w=0, h=0;
	SDL_GetRendererOutputSize(renderer, &w, &h);
	return h;
}

void esploraTft::text(const char *str, int x, int y) {
	// TODO: this
}

void esploraTft::setTextSize(int size) {
	// TODO: this
}

void esploraTft::refresh(void) {
	SDL_RenderPresent(renderer);
}
