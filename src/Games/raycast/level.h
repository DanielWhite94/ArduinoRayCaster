#ifndef RAYCAST_LEVEL_H
#define RAYCAST_LEVEL_H

#include <cstdint>

class Level {
public:

	// Internal data structures
	struct Block {
		uint8_t colourIndex;
	};

	struct Region {
		uint8_t x, y, w, h;
		Block *blocks;
		uint8_t neighbourCount;
		uint8_t neighbours;


		// Get a block at global coordinates (x, y)
		Block getBlock(uint8_t x, uint8_t y);
	};

	uint8_t regionCount;
	Region *regions;

	
};

#endif