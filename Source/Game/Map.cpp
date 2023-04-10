#include "stdafx.h"
#include "Map.h"

#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <iostream>
#include <set>

#include "../Config/scaler.h"

#define HEADER_OFFSET 3
#define NUMBER_SIZE 2

using namespace temp_name;

void Map::loadFile(std::string file)
{
	FILE *fp;

	fp = fopen(file.c_str(), "rb");

	fseek(fp, HEADER_OFFSET, SEEK_SET);

	unsigned short i = 0;

	int w, h;
	fread(&i, NUMBER_SIZE, 1, fp);
	w = i;
	fread(&i, NUMBER_SIZE, 1, fp);
	h = i;

	this->mapSize={w,h};
	this->backTile.clear();
	this->buildingTile.clear();
	this->frontTile.clear();

	int wCounter = 0;
	int hCounter = 0;
	int vectorCounter = 0;
	while (fread(&i, NUMBER_SIZE, 1, fp)) {
		if (vectorCounter == 0) {
			this->backTile.push_back(i);
		}
		else if (vectorCounter == 1) {
			this->buildingTile.push_back(i);
		}
		else {
			this->frontTile.push_back(i);
		}

		if (++wCounter >= w) {
			wCounter = 0;
			hCounter++;
		}
		if (hCounter >= h) {
			vectorCounter++;
			hCounter = 0;
		}
	}

	fclose(fp);

	this->loadHitbox();
}

void Map::loadHitbox()
{
	auto magicSize = Vector2i(1,1) * TILE_SIZE * SCALE_SIZE;
	hp = HitboxPool();
	for(int y=0;y < mapSize.y ;y++){
		for (int x=0;x < mapSize.x ;x++){
			int i = buildingTile[y*mapSize.x + x];
			if(i != 0) {
				auto magicPos = Vector2i(x, y) * TILE_SIZE * SCALE_SIZE;
				hp.AddHitbox(Rect::FromTopLeft(magicPos, magicSize));
			}
		}
	}
}

void Map::loadBMPs(std::string datapath)
{
	bmps = game_framework::Bittermap();
	std::vector<std::string> bmpList;
	for(int i=0;i<288;i++){ // FIXME: hardcode texture size
		bmpList.push_back(datapath+"/"+std::to_string(i)+".bmp");
	}
	bmps.LoadBitmapByString(bmpList, RGB(0, 0, 0));
}

void Map::drawTiles(std::vector<unsigned short> tile)
{
	for(int y=0;y < mapSize.y ;y++){
		for (int x=0;x < mapSize.x ;x++){
			int i = tile[y*mapSize.x + x];
			if(i==0) continue;
			bmps.SetFrameIndexOfBitmap(i-1);
			bmps.position = { x * TILE_SIZE, y * TILE_SIZE };
			bmps.position = bmps.position * bmps.GetScale();
			bmps.Draw();
		}
	}
}

void Map::drawBack()
{
	drawTiles(backTile);
}

void Map::drawBuilding()
{
	drawTiles(buildingTile);
}

void Map::drawFront()
{
	drawTiles(frontTile);
}

std::vector<Unity::Vector2i> Map::startPosition={
	{10,4},{4,5},{9,31},{18,4},{12,6},
	{6,38},{27,24},{20,5},{19,9},{6,6},
	{4,5},{8,4},{17,4},{27,21},{12,9},
	{23,4}
};

Unity::Vector2i Map::getMapSize() const {
	return mapSize;
}

bool Map::isPlaceable(Vector2i pos) const {
	if (
		(pos.x < 0 || pos.x >= this->mapSize.x) ||
		(pos.y < 0 || pos.y >= this->mapSize.y)
	) return false; // TODO: whether to throw when position out of range

	unsigned int i = this->mapSize.x*pos.y + pos.x;

	if (
		this->backTile[i]==0 ||
		this->buildingTile[i]!=0 ||
		this->frontTile[i]!=0
	) return false;

	return _tilesAvailableForRocks.count(this->backTile[i]) != 0;
}

std::vector<Vector2i> Map::getPlaceablePositions() const {
	vector<Vector2i> result;
	for(int y=0;y < mapSize.y ;y++){
		for (int x=0;x < mapSize.x ;x++){
			if(isPlaceable({x,y})) {
				result.push_back({ x,y });
			}
		}
	}
	return result;
}