#include "ball.h"

namespace Pong {
	void Ball::draw() {
		tft.fill(255, 0, 0);
		tft.stroke(255, 0, 0);
		tft.circle(x, y, radius);
	}

	void Ball::tick(void) {
		x += xVel;
		y += yVel;
		
		int wall = isTouchingWall();
		if(wall) {
			switch(wall) {
				case 1:
					flipXVel();
				break;
				case 2:
					flipYVel();
				break;
			}
		}
	}

	int Ball::isTouchingWall(void) const {
		if((x+radius/2) >= w || (x-radius/2) <= 0) return 1;
		if((y+radius/2) >= h || (y-radius/2) <= 0) return 2;
		
		return 0;
	}

	void Ball::flipYVel(void) {
		yVel = -yVel;
	}

	void Ball::flipXVel(void) {
		xVel = -xVel;
	}

	void Ball::clear(void) {
		// TODO: MAke the background colour a variable
		tft.fill(255, 255, 255);
		tft.stroke(255, 255, 255);
		tft.circle(x, y, radius);
	}
}