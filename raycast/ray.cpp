#include "ray.h"

namespace RayCast {

	Ray::Ray(Fixed x, Fixed y, Fixed angle) {
		startX=x;
		startY=y;

		mapX=startX.floor();
		mapY=startY.floor();

		rayDirX=Fixed::cos(angle);
		rayDirY=Fixed::sin(angle);

		// TODO: Use trig versions instead.
		Fixed rayDirX2=rayDirX*rayDirX;
		Fixed rayDirY2=rayDirY*rayDirY;
		deltaDistX=(rayDirX2>0 ? Fixed::sqrt(1+rayDirY2/rayDirX2) : Fixed::max());
		deltaDistY=(rayDirY2>0 ? Fixed::sqrt(1+rayDirX2/rayDirY2) : Fixed::max());

		if (rayDirX<0) {
			stepX=-1;
			sideDistX=(startX-mapX)*deltaDistX;
		} else {
			stepX=1;
			sideDistX=(mapX+1-startX)*deltaDistX;
		}
		if (rayDirY<0) {
			stepY=-1;
			sideDistY=(startY-mapY)*deltaDistY;
		} else {
			stepY=1;
			sideDistY=(mapY+1-startY)*deltaDistY;
		}
	}

	Ray::~Ray() {
	}

	void Ray::next(void) {
		if (sideDistX<sideDistY) {
			sideDistX+=deltaDistX;
			mapX+=stepX;
			side=0;
		} else {
			sideDistY+=deltaDistY;
			mapY+=stepY;
			side=1;
		}
	}

	int Ray::getMapX(void) const {
		return mapX+1;
	}

	int Ray::getMapY(void) const {
		return mapY+1;
	}

	Fixed Ray::getTrueDistance(void) const {
		Fixed distance;
		if (side==0)
			distance=(rayDirX!=0 ? Fixed::abs((mapX-startX+(1-stepX)/2)/rayDirX) : Fixed::max());
		else
			distance=(rayDirY!=0 ? Fixed::abs((mapY-startY+(1-stepY)/2)/rayDirY) : Fixed::max());
		return distance;
	}

	int Ray::getSide(void) const {
		return side;
	}

};