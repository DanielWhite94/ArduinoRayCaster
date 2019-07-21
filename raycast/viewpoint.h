#ifndef RAYCAST_VIEWPOINT_H
#define RAYCAST_VIEWPOINT_H

#include <cmath>

#include "fixed.h"

namespace RayCast {

	class ViewPoint {
	public:
		ViewPoint(Fixed X, Fixed Y, Fixed Angle, Fixed Fov=Fixed(M_PI/3.0), Fixed MaxDist=Fixed(64.0));

		Fixed getX(void) const ;
		Fixed getY(void) const ;
		Fixed getAngle(void) const ;
		Fixed getFov(void) const ;
		Fixed getMaxDist(void) const ;

		void setX(Fixed newX);
		void setY(Fixed newY);
		void setAngle(Fixed newAngle);

		void move(Fixed delta); // Move in current direction (or backwards if delta is negative).
		void turn(Fixed delta);
	private:
		Fixed x, y;
		Fixed angle;
		Fixed fov; // Field-of-view, radians.
		Fixed maxDist; // Maximum viewing distance.
	};

};

#endif
