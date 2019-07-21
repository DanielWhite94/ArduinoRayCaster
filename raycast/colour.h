#ifndef COLOUR_H
#define COLOUR_H

#include <cstdint>

#include "fixed.h"

class Colour {
public:
	uint8_t r, g, b;

	void mul(Fixed factor);
};

#endif