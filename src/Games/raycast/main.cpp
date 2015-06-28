#include <cstdlib>
#include <unistd.h>

#include <Esplora.h>
#include "renderer.h"
#include "viewpoint.h"

using namespace RayCast;

Renderer *renderer=NULL;


int main(int argc, char **argv) {
	EsploraTFT.begin();
	renderer=new Renderer();

	const Fixed moveSpeed=0.2;
	const Fixed turnSpeed=Fixed(M_PI/18.0);

	ViewPoint vPoint(Fixed(13.4), Fixed(8.0), Fixed(M_PI));

	while(1) {
		// Check events.
		if (Esplora.readButton(SWITCH_LEFT)==HIGH)
			vPoint.turn(-turnSpeed);
		if (Esplora.readButton(SWITCH_RIGHT)==HIGH)
			vPoint.turn(turnSpeed);
		if (Esplora.readButton(SWITCH_UP)==HIGH)
			vPoint.move(moveSpeed);
		if (Esplora.readButton(SWITCH_DOWN)==HIGH)
			vPoint.move(-moveSpeed);

		// Redraw.
		renderer->render(vPoint);
#if SDL_MAJOR_VERSION == 2
		EsploraTFT.tick();
#endif

		// Delay.
		delay(100);
	}

	delete renderer;

	return EXIT_SUCCESS;
}
