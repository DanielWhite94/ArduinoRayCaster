#ifndef RAYCAST_VIEWPOINT_H
#define RAYCAST_VIEWPOINT_H

#include <cmath>

namespace RayCast {

	class ViewPoint {
	public:
		ViewPoint(float X, float Y, float Angle, float Fov=M_PI/3.0, float MaxDist=64.0);

		float getX(void) const ;
		float getY(void) const ;
		float getAngle(void) const ;
		float getFov(void) const ;
		float getMaxDist(void) const ;

		void setAngle(float newAngle);
	private:
		float x, y;
		float angle;
		float fov; // Field-of-view, radians.
		float maxDist; // Maximum viewing distance.
	};

};

#endif
