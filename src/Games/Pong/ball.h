#ifndef BALL_H
#define BALL_H

#include "arduinoinc.h"

namespace Pong {
	class Ball {
	public:
		Ball(unsigned _x, unsigned _y, unsigned rad, TFT _tft)
		: x(_x), y(_y), radius(rad), tft(_tft) {
			xVel = 1;
			yVel = 2;

			w = tft.width();
			h = tft.height();
		}

		// Draw the ball to the screen
		void draw(void);

		// A call to clear before the next tick() will clear
		// the previously drawn circle
		void clear(void);

		// Returns:
		// 0 if not touching,
		// 1 if touching horizontal edges (top and bottom)
		// 2 if touching vertical edges (left and right)
		int isTouchingWall(void) const;

		// update the balls position
		void tick(void);

		void flipXVel(void);
		void flipYVel(void);

		int getX(void) {
			return x;
		}

		int getY(void) {
			return y;
		}

		int getRadius(void) {
			return radius;
		}

	private:
		int x, y;
		int xVel, yVel;
		int radius;
		int w, h;

		TFT tft;
	};
}

#endif