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

	int x;
	for(x=0;x<3;++x) {
		ViewPoint vPoint(0, 0, 0);
		renderer->render(vPoint);
		sleep(1);
	}

	delete renderer;

	return EXIT_SUCCESS;
}
