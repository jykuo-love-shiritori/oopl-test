#include "stdafx.h"
#include "Map.h"

#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <iostream>


#define HEADER_OFFSET 3
#define NUMBER_SIZE 2

using namespace temp_name;

Map Map::loadFile(std::string file)
{
	Map newmap;
	FILE *fp;

	fp = fopen(file.c_str(), "rb");

	fseek(fp, HEADER_OFFSET, SEEK_SET);

	unsigned short i = 0;

	int w, h;
	fread(&i, NUMBER_SIZE, 1, fp);
	w = i;
	fread(&i, NUMBER_SIZE, 1, fp);
	h = i;

	newmap.mapSize={w,h};

	int wCounter = 0;
	int hCounter = 0;
	int vectorCounter = 0;
	while (fread(&i, NUMBER_SIZE, 1, fp)) {
		if (vectorCounter == 0) {
			newmap.backTile.push_back(i);
		}
		else if (vectorCounter == 1) {
			newmap.buildingTile.push_back(i);
		}
		else {
			newmap.frontTile.push_back(i);
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

	return newmap;
}

void Map::loadBMPs(std::string datapath)
{
	std::vector<std::string> bmpList;
	for(int i=0;i<288;i++){
		bmpList.push_back(datapath+"/"+std::to_string(i)+".bmp");
	}
	bmps.LoadBitmapByString(bmpList, RGB(0, 0, 0));
}

void Map::drawBack()
{
	for(int y=0;y < mapSize.y ;y++){
		for (int x=0;x < mapSize.x ;x++){
			int i = backTile[y*mapSize.x + x];
			if(i==0) continue;
			bmps.SetFrameIndexOfBitmap(i-1);
			bmps.position = { x * 16, y * 16 };
			bmps.position = bmps.position * bmps.GetScale();
			bmps.Draw();
		}
	}
}

void Map::drawBuilding()
{
	for(int y=0;y < mapSize.y ;y++){
		for (int x=0;x < mapSize.x ;x++){
			int i = buildingTile[y*mapSize.x + x];
			if(i==0) continue;
			bmps.SetFrameIndexOfBitmap(i-1);
			bmps.position = { x * 16, y * 16 };
			bmps.position = bmps.position * bmps.GetScale();
			bmps.Draw();
		}
	}
}

void Map::drawFront()
{
	for(int y=0;y < mapSize.y ;y++){
		for (int x=0;x < mapSize.x ;x++){
			int i = frontTile[y*mapSize.x + x];
			if(i==0) continue;
			bmps.SetFrameIndexOfBitmap(i-1);
			bmps.position = { x * 16, y * 16 };
			bmps.position = bmps.position * bmps.GetScale();
			bmps.Draw();
		}
	}
}
