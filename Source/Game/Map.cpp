#include "stdafx.h"
#include "Map.h"

#include <string>

using namespace temp_name;


void Map::loadBMPs(std::string datapath)
{
	std::vector<std::string> bmpList;
	for(int i=0;i<288;i++){
		bmpList.push_back(datapath+"/"+std::to_string(i)+".bmp");
	}
	bmps.LoadBitmapByString(bmpList, RGB(255, 255, 255));
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

void Map::drawFront()
{
	//TODO:
}