#include <cassert>
#include <cstdio>
#include <cstdlib>

#include "Esplora.h"

esploraTft EsploraTFT;
esplora Esplora;

void delay(unsigned long ms) {
	SDL_Delay(ms);
}

unsigned long millis(void) {
	return SDL_GetTicks();
}

esploraTft::esploraTft() {
	strokeDo=false;
	fillDo=false;

	// TODO: Make getter/setter
	LedR = 255;
	LedG = 0;
	LedB = 0;

	// TODO: Throw exceptions instead?
	if(SDL_Init(SDL_INIT_VIDEO)<0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		printf("Warning: Linear texture filtering not enabled!");
		exit(EXIT_FAILURE);
	}
	window=SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
		WINDOWWIDTH, WINDOWHEIGHT, SDL_WINDOW_SHOWN);
	if(window==NULL) {
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	renderer=SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(renderer==NULL) {
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	
	// Create another texture for the TFT library to write onto
	// TODO: Check for NULL
	tftTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_TARGET,
		TFTWIDTH, TFTHEIGHT);
	SDL_SetRenderTarget(renderer, tftTexture);

}

esploraTft::~esploraTft() {
    SDL_DestroyTexture(tftTexture);
	tftTexture=NULL;
	SDL_DestroyRenderer(renderer);
	renderer=NULL;
	SDL_DestroyWindow(window);
	window=NULL;

	SDL_Quit();
}

void esploraTft::begin(void) {
	tick();
}

void esploraTft::tick(void) {
	// Check for events.
	checkEvents();

	// Draw and update screen.
	redraw();
}

void esploraTft::background(int r, int g, int b) {
	assert(r>=0 && r<256);
	assert(r>=0 && r<256);
	assert(r>=0 && r<256);

	SDL_SetRenderDrawColor(renderer, r, g, b, 0xFF);
	SDL_Rect rect={0, 0, this->width(), this->height()};
	SDL_RenderFillRect(renderer, &rect);
}

void esploraTft::stroke(int r, int g, int b) {
	assert(r>=0 && r<256);
	assert(r>=0 && r<256);
	assert(r>=0 && r<256);

	strokeDo=true;
	strokeR=r;
	strokeG=g;
	strokeB=b;
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

	SDL_SetRenderDrawColor(renderer, strokeR, strokeG, strokeB, 0xFF);
	SDL_RenderDrawPoint(renderer, x, y);
}

void esploraTft::line(int x1, int y1, int x2, int y2) {
	if (!strokeDo)
		return;

	SDL_SetRenderDrawColor(renderer, strokeR, strokeG, strokeB, 0xFF);
	SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void esploraTft::rect(int x, int y, int w, int h) {
	// Draw rectangle.
	if (fillDo) {
		SDL_SetRenderDrawColor(renderer, fillR, fillG, fillB, 0xFF);
		SDL_Rect rect={x, y, w, h};
		SDL_RenderFillRect(renderer, &rect);
	}

	// Draw outline:
	if (strokeDo) {
		SDL_SetRenderDrawColor(renderer, strokeR, strokeG, strokeB, 0xFF);
		this->line(x, y, x+w, y); // Top,
		this->line(x+w-1, y, x+w-1, y+h); // right,
		this->line(x, y+h-1, x+w, y+h-1); // bottom and
		this->line(x, y, x, y+h); // left.
	}
}

void esploraTft::circle(int x, int y, int radius) {
	// TODO: this
}

int esploraTft::width(void) {
	return TFTWIDTH;
}

int esploraTft::height(void) {
	return TFTHEIGHT;
}

void esploraTft::text(const char *str, int x, int y) {
	// TODO: this
}

void esploraTft::setTextSize(int size) {
	// TODO: this
}

void esploraTft::checkEvents(void) {
	// Check events.
	SDL_Event event;
	while (SDL_PollEvent(&event))
		switch(event.type) {
			case SDL_QUIT:
				exit(EXIT_SUCCESS);
			break;
		}
}

void esploraTft::redraw(void) {
	// Reset rendering back to the screen
	SDL_SetRenderTarget(renderer, NULL);

	// Copy TFT texture.
	SDL_Rect r = {
		TFTPOSX, TFTPOSY, 
		(int)(ZOOM*TFTWIDTH), 
		(int)(ZOOM*TFTHEIGHT)
	};
	SDL_RenderCopy(renderer, tftTexture, NULL, &r);

	// Draw the Led.
	this->drawLed();

	// Update the screen.
	SDL_RenderPresent(renderer);

	// Set rendering to tft texture once again.
	SDL_SetRenderTarget(renderer, tftTexture);
}

void esploraTft::drawLed(void) {
	filledCircleRGBA(renderer, LEDX, LEDY, LEDRADIUS, LedR, LedG, LedB, 255);
}


int esplora::readSlider(){
	//TODO
	return 0;
}
int esplora::readLightSensor(){
	//TODO
	return 0;
}
int esplora::readTemperature(TemperatureScale scale){
	//TODO
	return 0;
}
int esplora::readMicrophone(){
	//TODO
	return 0;
}
int esplora::readJoystickSwitch(){
	//TODO
	return 0;
}
int esplora::readAccelerometer(Axis axis){
	//TODO
	return 0;
}
DigitalOutput esplora::readButton(Button b){
	const Uint8 *keys = getKeyboardState();

	switch(b) {
		case SWITCH_1:
		case SWITCH_DOWN:
			if(keys[SDL_SCANCODE_DOWN])
				return HIGH;
			else
				return LOW;
		break;	
		case SWITCH_LEFT:
		case SWITCH_2:
			if(keys[SDL_SCANCODE_LEFT])
				return HIGH;
			else
				return LOW;
		break;
		case SWITCH_UP:
		case SWITCH_3:
			if(keys[SDL_SCANCODE_UP])
				return HIGH;
			else
				return LOW;
		break;
		case SWITCH_RIGHT:
		case SWITCH_4:
			if(keys[SDL_SCANCODE_RIGHT])
				return HIGH;
			else
				return LOW;
		break;

		default:
			return LOW;
		break;
	}
}
int esplora::readJoystickX(){
	//TODO
	return 0;
}
int esplora::readJoystickY(){
	//TODO
	return 0;
}
void esplora::writeRGB(int red, int green, int blue){
	//TODO
}
void esplora::writeRed(int brightness){
	//TODO
}
void esplora::writeGreen(int brightness){
	//TODO
}
void esplora::writeBlue(int brightness){
	//TODO
}
int esplora::readRed(){
	//TODO
	return 0;
}
int esplora::readGreen(){
	//TODO
	return 0;
}
int esplora::readBlue(){
	//TODO
	return 0;
}
void esplora::tone(int pin, unsigned int frequency, unsigned long duration){
	//TODO
}
// A call to tone without a duration keeps the buzzer
// going until noTone is called
void esplora::tone(int pin, unsigned int frequency){
	//TODO
}
void esplora::noTone(int pin){
	//TODO
}

const Uint8 *esplora::getKeyboardState(){
	// Refresh SDL internals
	SDL_PumpEvents();
	return SDL_GetKeyboardState(NULL);
}
