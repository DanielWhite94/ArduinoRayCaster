#include "viewpoint.h"

namespace RayCast {

	ViewPoint::ViewPoint(float X, float Y, float Angle, float Fov, float MaxDist) {
		x=X;
		y=Y;
		angle=Angle;
		fov=Fov;
		maxDist=MaxDist;
	}

	float ViewPoint::getX(void) const {
		return x;
	}

	float ViewPoint::getY(void) const {
		return y;
	}

	float ViewPoint::getAngle(void) const {
		return angle;
	}

	float ViewPoint::getFov(void) const {
		return fov;
	}

	float ViewPoint::getMaxDist(void) const {
		return maxDist;
	}

	void ViewPoint::setAngle(float newAngle) {
		angle=newAngle;
	}
};