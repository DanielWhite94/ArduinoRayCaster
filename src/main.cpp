#include <cstdlib>

#include <Esplora.h>
#include "renderer.h"
#include "viewpoint.h"

using namespace RayCast;

Renderer *renderer=NULL;

#include <unistd.h>

int main(int argc, char **argv) {
	EsploraTFT.begin();
	renderer=new Renderer();

	while(1) {
		ViewPoint vPoint(0, 0, 0);
		renderer->render(vPoint);
		sleep(1);
	}

	delete renderer;

	return EXIT_SUCCESS;
}
