#include <cmath>

#include "renderer.h"

namespace RayCast {

	Renderer::Renderer() {
	}

	Renderer::~Renderer() {
	}

	void Renderer::render(const ViewPoint &vPoint) {
		int screenW=EsploraTFT.width();
		int screenH=EsploraTFT.height();

		// Clear surface.
		EsploraTFT.background(255, 0, 255); // Clear screen (to pink, to help identify any undrawn regions).

		// Draw sky and ground.
		EsploraTFT.noStroke();

		EsploraTFT.fill(0,0,255);
		EsploraTFT.rect(0, 0, screenW, screenH/2);

		EsploraTFT.fill(0,255,0);
		EsploraTFT.rect(0, screenH/2, screenW, screenH/2);

		// Draw blocks.
		// TODO: this

		// Draw objects.
		// TODO: this
	}

#ifdef EXTRA
	void Renderer::renderTopDown(const ViewPoint &vPoint) {
		#define SX(X) ((screenW/2+cellW*(vPoint.getX()-(X))).getInt())
		#define SY(Y) ((screenH/2+cellH*(vPoint.getY()-(Y))).getInt())

		const int cellW=16;
		const int cellH=16;

		int screenW=EsploraTFT.width();
		int screenH=EsploraTFT.height();

		// Clear screen.
		EsploraTFT.background(0, 0, 0);

		// Debugging grid.
		int cellsWide=screenW/cellW+2;
		int cellsHigh=screenH/cellH+2;
		int minMapX=vPoint.getX().floor()-cellsWide/2;
		int minMapY=vPoint.getY().floor()-cellsHigh/2;
		int maxMapX=minMapX+cellsWide;
		int maxMapY=minMapY+cellsHigh;
		int mapX, mapY;
		EsploraTFT.stroke(196, 196, 196);
		int x, y;
		for(x=minMapX;x<=maxMapX;++x)
			EsploraTFT.line(SX(x), 0, SX(x), screenH);
		for(y=minMapY;y<=maxMapY;++y)
			EsploraTFT.line(0, SY(y), screenW, SY(y));

		// Trace ray.
		Ray ray(vPoint.getX(), vPoint.getY(), vPoint.getAngle());
		int i;
		for(i=0;i<10;++i) {
			// Draw highlighted cell.
			EsploraTFT.stroke(255, 0, 0);
			EsploraTFT.fill(255, 0, 0);
			EsploraTFT.rect(SX(ray.getX())+1, SY(ray.getY())+1, cellW-2, cellH-2);

			// Advance ray.
			ray.next();
		}

		// Viewpoint cross-hair.
		int k=2;
		EsploraTFT.stroke(0, 0, 255);
		EsploraTFT.line(SX(vPoint.getX())-k, SY(vPoint.getY())-k, SX(vPoint.getX())+k, SY(vPoint.getY())+k);
		EsploraTFT.line(SX(vPoint.getX())-k, SY(vPoint.getY())+k, SX(vPoint.getX())+k, SY(vPoint.getY())-k);

		// Line of sight.
		EsploraTFT.stroke(0, 255, 0);
		Fixed len=Fixed(16.0);
		EsploraTFT.line(SX(vPoint.getX()), SY(vPoint.getY()), SX(vPoint.getX()+Fixed::cos(vPoint.getAngle())*len), SY(vPoint.getY()+Fixed::sin(vPoint.getAngle())*len));

		#undef SX
		#undef SY
	}
#endif

};
