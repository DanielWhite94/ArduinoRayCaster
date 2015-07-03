#include "inc.h"
#include "renderer.h"

using namespace RayCast;

// Defining pins for TFT screen usage
const int TFTCS = 10;
const int TFTDC = 8;
const int TFTReset = 9;

TFT tft = TFT(TFTCS, TFTDC, TFTReset);

char conv[10];
Renderer *renderer;

const Fixed moveSpeed=0.2;
const Fixed turnSpeed=Fixed(M_PI/18.0);

ViewPoint vPoint(Fixed(13.4), Fixed(8.0), Fixed(M_PI));


extern "C" void setup() {
	tft.begin();

	tft.background(255, 0, 0);

	renderer = new Renderer();
}

extern "C" void loop() {
	renderer->render(vPoint);
}