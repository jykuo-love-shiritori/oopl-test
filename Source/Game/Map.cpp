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

std::set<unsigned int> Map::kTilesAvailableForRocks = {
	//FIXME: cant catch 140 235 and some others as tiles available
	1,2,3,17,18,19,33,34,35,137,
	138,139,140,149,150,151,152,153,154,155,
	165,166,167,168,169,170,171,172,181,182,
	183,184,185,186,187,188,198,199,200,201,
	202,203,217,218,219,233,234,235,240,241,
	242,256,257,258,272,273,274
};

std::vector<Unity::Vector2i> Map::kStartPosition = {
	// TODO: there is only 16 levels
	{10,4},{4,5},{9,31},{18,4},{12,6},
	{6,38},{27,24},{20,5},{19,9},{6,6},
	{4,5},{8,4},{17,4},{27,21},{12,9},
	{23,4}
};

std::map<int,Vector2i> Map::presetExitLevels = {
	{10,Vector2i(15,11)},{12,Vector2i(75,9)}
};

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

	m_mapSize={w,h};
	m_backTile.clear();
	m_buildingTile.clear();
	m_frontTile.clear();

	int wCounter = 0;
	int hCounter = 0;
	int vectorCounter = 0;
	while (fread(&i, NUMBER_SIZE, 1, fp)) {
		if (vectorCounter == 0) {
			m_backTile.push_back(i);
		}
		else if (vectorCounter == 1) {
			m_buildingTile.push_back(i);
		}
		else {
			m_frontTile.push_back(i);
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
	for(int y=0;y < m_mapSize.y ;y++){
		for (int x=0;x < m_mapSize.x ;x++){
			int i = m_buildingTile[y*m_mapSize.x + x];
			if(i == 173+1)
				continue; // exit
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
	for(int y=0;y < m_mapSize.y ;y++){
		for (int x=0;x < m_mapSize.x ;x++){
			int i = tile[y* m_mapSize.x + x];
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
	drawTiles(m_backTile);
}

void Map::drawBuilding()
{
	drawTiles(m_buildingTile);
}

void Map::drawFront()
{
	drawTiles(m_frontTile);
}

Unity::Vector2i Map::getMapSize() const {
	return m_mapSize;
}

bool Map::isPlaceable(Vector2i pos) const {
	if (
		(pos.x < 0 || pos.x >= m_mapSize.x) ||
		(pos.y < 0 || pos.y >= m_mapSize.y)
	) return false; // TODO: whether to throw when position out of range

	unsigned int i = m_mapSize.x*pos.y + pos.x;

	if (
		m_backTile[i]==0 ||
		m_buildingTile[i]!=0 ||
		m_frontTile[i]!=0
	) return false;

	if (pos == kStartPosition[m_mapIndex-1]) return false;

	return kTilesAvailableForRocks.count(m_backTile[i]) != 0;
}

std::vector<Vector2i> Map::getPlaceablePositions() const {
	vector<Vector2i> result;
	for(int y=0;y < m_mapSize.y ;y++){
		for (int x=0;x < m_mapSize.x ;x++){
			if(isPlaceable({x,y})) {
				result.push_back({ x,y });
			}
		}
	}
	return result;
}

Map::Info Map::getInfo() const {
	Info info;
	info.startPosition = kStartPosition[m_mapIndex-1];
	if(presetExitLevels.count(m_mapIndex)){
		info.hasPresetExit=true;
		info.presetExitPosition=presetExitLevels[m_mapIndex];
	}
	else{
		info.hasPresetExit=false;
	}
	return info;
}

unsigned int Map::getLevel() const {
	return m_mapIndex;
}

void Map::setLevel(unsigned int index) {
	// TODO: better exception handle
	m_mapIndex = index;
	loadFile("resources/MapData/" + std::to_string(m_mapIndex) + ".ttt");
}

bool Map::nextLevel() {
	auto next_map_index = (m_mapIndex+1) % kStartPosition.size();
	setLevel(next_map_index);
	return true;

	// TODO: better exception handle
	// file is start at 1 but vector start at 0 :(
	if(!(m_mapIndex-1+1 < kStartPosition.size())) return false;
	// set to next level
	setLevel(m_mapIndex+1);
	return true;
}


