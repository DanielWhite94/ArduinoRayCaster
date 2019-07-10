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

#define MAPW 16
#define MAPH 16
#define _ 0
#define W 1
#define R 2
#define B 3
const int map[MAPW][MAPH]={
	{ W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,_ },
	{ W,_,_,_,_,_,_,_,_,_,_,_,_,_,_,W },
	{ W,_,_,_,_,_,_,_,_,_,_,_,_,_,_,W },
	{ W,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_ },
	{ W,_,_,R,R,R,R,_,_,_,_,R,_,_,_,_ },
	{ W,_,_,R,_,_,_,_,_,_,_,R,_,_,_,W },
	{ _,_,_,R,_,R,R,_,_,_,_,R,_,_,_,W },
	{ _,_,_,_,_,R,_,_,_,_,_,R,_,_,_,W },
	{ W,_,_,R,_,R,_,_,_,_,_,R,_,_,_,W },
	{ W,_,_,_,_,_,_,_,_,_,_,_,_,_,_,W },
	{ W,_,_,_,_,_,_,_,_,_,_,_,_,_,_,W },
	{ W,_,_,_,B,B,_,B,B,B,_,_,_,_,_,W },
	{ W,_,_,_,_,_,_,_,_,_,_,_,_,_,_,W },
	{ W,_,_,_,_,_,_,_,_,_,_,_,_,_,_,W },
	{ W,_,_,_,_,_,_,_,_,_,_,_,_,_,_,W },
	{ W,W,W,W,_,_,_,_,_,W,W,W,W,W,W,W }};
Level::Block staticBlock;
const Level::Block *Level::getBlock(int8_t x, int8_t y) const {
	if (x<0 || y<0 || x>=MAPW || y>=MAPH)
		return NULL;

	staticBlock.textureIndex=map[x][y];
	staticBlock.height=48+map[x][y]*16;
	return &staticBlock;

	/*
	uint8_t regionId=this->getRegionId(x, y);
	if (regionId==RegionIdInvalid)
		return NULL;
	return this->regions[regionId].getBlock(x, y);
	*/
}

uint8_t Level::getRegionId(int8_t x, int8_t y) const {
	uint8_t id;
	const Region *region;
	for(id=0,region=&regions[0];id<regionCount;++id,++region)
		if (x>=region->x && x<region->x+region->w && y>=region->y && y<region->y+region->h)
			return id;
	return RegionIdInvalid;
}

Level::Texture staticTexture;
const Level::Texture *Level::getTexture(uint8_t id) const {
	staticTexture.type=Level::TextureType::Colour;
	switch(id) {
		case 0: return NULL; break;
		case 1:
			staticTexture.data.colour.r=160;
			staticTexture.data.colour.g=160;
			staticTexture.data.colour.b=160;
			return &staticTexture;
		break;
		case 2:
			staticTexture.data.colour.r=255;
			staticTexture.data.colour.g=0;
			staticTexture.data.colour.b=0;
			return &staticTexture;
		break;
		case 3:
			staticTexture.data.colour.r=255;
			staticTexture.data.colour.g=255;
			staticTexture.data.colour.b=0;
			return &staticTexture;
		break;
		default: return NULL; break;
	}
	// TODO: this
	return NULL;
}