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

	while(1) {
		ViewPoint vPoint(0, 0, 0);
		renderer->render(vPoint);
		delay(100);
	}

	delete renderer;

	return EXIT_SUCCESS;
}
