#include "stdafx.h"
#include "Map.h"

#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <iostream>


using namespace temp_name;

void Map::loadFile(std::string file)
{
    std::ifstream tttFile(file,std::ios::binary);

    std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(tttFile),{});
       
	short width, height;
	width=buffer[3];
	height=buffer[5];

	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){
			backTile.push_back(buffer[7+2*(i*width+j)]);
		}
	}
	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){
			buildingTile.push_back(buffer[7+2*width*height+2*(i*width+j)]);
		}
	}
	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){
			frontTile.push_back(buffer[7+4*width*height+2*(i*width+j)]);
		}
	}
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

std::vector<unsigned short> Map::backTile={};
std::vector<unsigned short> Map::buildingTile={};
std::vector<unsigned short> Map::frontTile={};