#include <cmath>

#include "ray.h"
#include "renderer.h"

namespace RayCast {

	Renderer::Renderer() {
	}

	Renderer::~Renderer() {
	}

	void Renderer::render(const Level &level, const ViewPoint &vPoint) {
		// Calculate various useful values.
		int screenW=EsploraTFT.width();
		int screenH=EsploraTFT.height();
		Fixed screenDist=screenW/(2*Fixed::tan(vPoint.getFov()/2));

		// Clear surface.
		EsploraTFT.background(255, 0, 255); // Clear screen (to pink, to help identify any undrawn regions).

		// Draw sky and ground.
		EsploraTFT.noStroke();
		EsploraTFT.fill(0,0,255);
		EsploraTFT.rect(0, 0, screenW, screenH/2);
		EsploraTFT.fill(0,255,0);
		EsploraTFT.rect(0, screenH/2, screenW, screenH/2);

		// Draw blocks.
		// Loop over each vertical slice of the screen.
		int x;
		for(x=0;x<screenW;++x) {
			// Trace ray from view point at this angle.
			Fixed deltaAngle=Fixed::atan((x-screenW/2)/screenDist);
			Fixed angle=vPoint.getAngle()+deltaAngle;
			Ray ray(vPoint.getX(), vPoint.getY(), angle);

			for(Fixed stepCount=0;stepCount<vPoint.getMaxDist();++stepCount) { // FIXME: This is just a hack (the distance is limited but not correctly).
				// Advance ray to next (or first) intersection point.
				ray.next();

				// Get block at current ray position.
				int mapX=ray.getMapX();
				int mapY=ray.getMapY();
				const Level::Block *block=level.getBlock(mapX, mapY);
				if (block==NULL)
					continue;

				// Calculate 'true distance' and display height.
				Fixed distance=ray.getTrueDistance();
				int height=this->computeDisplayHeight(block->getHeight(), distance).getInt();
				if (height>screenH) height=screenH;

				// Find texture.
				const Level::Texture *texture=level.getTexture(block->getTextureIndex());
				if (texture==NULL)
					continue;

				// Draw texture (based on type).
				switch(texture->type) {
					case Level::TextureType::Colour: {
						// Solid colour.
						class::Colour colour=texture->data.colour;

						// Adjust colour based on intersection side (horizontal or vertical).
						// This makes edges between adjacent walls clearer.
						int side=ray.getSide();
						if (side) colour.mul(0.7);

						// Draw vertical line.
						EsploraTFT.stroke(colour.r, colour.g, colour.b);
						EsploraTFT.line(x, (screenH-height)/2, x, (screenH+height)/2);
					} break;
				}

				// Move onto next ray.
				break;
			}
		}

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

	Fixed Renderer::computeDisplayHeight(const Fixed &blockHeight, const Fixed &distance) {
		return (distance>0 ? blockHeight/distance : Fixed::max());
	}

};
