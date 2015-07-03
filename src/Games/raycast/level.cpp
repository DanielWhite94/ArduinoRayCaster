#include <cassert>

#include "level.h"

uint8_t Level::Block::getTextureIndex(void) const {
	return textureIndex;
}

Fixed Level::Block::getHeight(void) const {
	return height;
}

Level::Level() {
	regionCount=0;
	regions=NULL;

	textureCount=0;
	textures=NULL;
}

Level::~Level() {
	// TODO: this
}

const Level::Block *Level::Region::getBlock(int8_t x, int8_t y) const {
	assert(x>=this->x && x<this->x+this->w);
	assert(y>=this->y && y<this->y+this->h);

	// TODO: this
	return NULL;
}

const Level::Block *Level::getBlock(int8_t x, int8_t y) const {
	uint8_t regionId=this->getRegionId(x, y);
	if (regionId==RegionIdInvalid)
		return NULL;
	return this->regions[regionId].getBlock(x, y);
}

uint8_t Level::getRegionId(int8_t x, int8_t y) const {
	uint8_t id;
	const Region *region;
	for(id=0,region=&regions[0];id<regionCount;++id,++region)
		if (x>=region->x && x<region->x+region->w && y>=region->y && y<region->y+region->h)
			return id;
	return RegionIdInvalid;
}

const Level::Texture *Level::getTexture(uint8_t id) const {
	// TODO: this
	return NULL;
}