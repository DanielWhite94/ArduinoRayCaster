#include "viewpoint.h"

namespace RayCast {

	ViewPoint::ViewPoint(Fixed X, Fixed Y, Fixed Angle, Fixed Fov, Fixed MaxDist) {
		x=X;
		y=Y;
		angle=Angle;
		fov=Fov;
		maxDist=MaxDist;
	}

	Fixed ViewPoint::getX(void) const {
		return x;
	}

	Fixed ViewPoint::getY(void) const {
		return y;
	}

	Fixed ViewPoint::getAngle(void) const {
		return angle;
	}

	Fixed ViewPoint::getFov(void) const {
		return fov;
	}

	Fixed ViewPoint::getMaxDist(void) const {
		return maxDist;
	}

	void ViewPoint::setAngle(Fixed newAngle) {
		angle=newAngle;
	}
};
