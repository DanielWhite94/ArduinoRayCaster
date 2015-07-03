#include "arduinoinc.h"

#include "ball.h"

#ifndef TFTCS
#	define TFTCS 10
#endif
#ifndef TFTDC
#	define TFTDC 8
#endif
#ifndef TFTReset
#	define TFTReset 9
#endif

TFT tft(TFTCS, TFTDC, TFTReset);
Pong::Ball *b;

void setup() {
	SPI.setClockDivider(SPI_CLOCK_DIV2);
	tft.begin();

	// Display a splash screen
	tft.background(255, 255, 255);
	tft.setTextSize(4);
	tft.text("Pong!", tft.width()/6, tft.height()/3);
	delay(700);

	b = new Pong::Ball(40, 40, 20, tft);
}

void loop() {
	/*b->draw();
	delay(10);
	b->clear();
	b->tick();*/
	//tft.background(255, 255, 255);
	//tft.fillScreen(0xFFFF);
	tft.stroke(0xffff);
	tft.fill(0xFFFF);
	tft.rect(b->getX() - b->getRadius()-2, b->getY() - b->getRadius()-2,
		2*b->getRadius()+2, 2*b->getRadius()+5);
	b->draw();
	b->tick();

	//delay(50);
}