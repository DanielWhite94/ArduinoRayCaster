#ifndef RAYCAST_LEVEL_H
#define RAYCAST_LEVEL_H

#include <cstdint>

#include "colour.h"
#include "fixed.h"

struct Level {
public:
	const uint8_t RegionIdInvalid=255;

	// Internal data structures
	enum TextureType {
		Colour,
	};

	struct Texture {
		TextureType type;
		union {
			class::Colour colour;
		} data ;
	};

	struct Block {
	public:
		uint8_t getTextureIndex(void) const ;
		Fixed getHeight(void) const ;

	//private:
		uint8_t textureIndex;
		uint8_t height;
	};

	struct Region {
		int8_t x, y, w, h;
		Block *blocks;
		uint8_t neighbourCount;
		uint8_t neighbours;

		const Block *getBlock(int8_t x, int8_t y) const ; // Get a block at global coordinates (x, y) within this region.
	};

	Level();
	~Level();

	const Block *getBlock(int8_t x, int8_t y) const ; // Get a block at global coordinates (x, y).

	uint8_t getRegionId(int8_t x, int8_t y) const ; // Returns id of region associated with (x,y), or RegionIdInvalid if none.

	const Texture *getTexture(uint8_t id) const ;

private:
	uint8_t regionCount;
	Region *regions;

	uint8_t textureCount;
	Texture *textures;
};

#endif
