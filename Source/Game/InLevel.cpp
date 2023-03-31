#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "stages.h"

#include "../Config/keymap.h"

using namespace game_framework;
using namespace game_framework::stage;

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////

InLevel::InLevel(CGame *g) : CGameState(g)
{
}

InLevel::~InLevel()
{
}

void InLevel::OnBeginState()
{
}

void InLevel::OnMove()							// 移動遊戲元素
{
	const int KEY_PRESS = 0x8000;
	const int speed=10;
	if(GetKeyState(KEY_MOVE_LEFT) & KEY_PRESS){
		player.Move({-speed,0});
	}
	if(GetKeyState(KEY_MOVE_RIGHT) & KEY_PRESS){
		player.Move({speed,0});
	}
	if(GetKeyState(KEY_MOVE_UP) & KEY_PRESS){
		player.Move({0,-speed});
	}
	if(GetKeyState(KEY_MOVE_DOWN) & KEY_PRESS){
		player.Move({0,speed});
	}
}

void InLevel::OnInit()  								// 遊戲的初值及圖形設定
{
	player.LoadBitmapByString({
        "resources/giraffe.bmp"
	}, RGB(255, 255, 255));
	player.SetScale(1);
	player.SetTopLeft(SIZE_X/2, SIZE_Y/2);
	player.position=Vector2i(10,4)*16*4;

	map = temp_name::Map::loadFile("resources/MapData/1.ttt");
	map.loadBMPs(datapath);
	map.bmps.SetScale(4);

	test.load();
	test.createRocks(map);

	Bittermap::CameraPosition = &player.position;
}

void InLevel::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if(nChar=='J' || nChar=='K'){
		if(nChar=='J'){
			if(phase<16){
				phase++;
			}
		}
		else{
			if(phase>0){
				phase--;
			}
		}
		
		switch(phase) {
			case 0:
				map = temp_name::Map::loadFile("resources/MapData/1.ttt");
				player.position=map.startPosition[phase]*16*4;
				break;
			case 1:
				map = temp_name::Map::loadFile("resources/MapData/2.ttt");
				player.position=map.startPosition[phase]*16*4;
				break;
			case 2:
				map = temp_name::Map::loadFile("resources/MapData/3.ttt");
				player.position=map.startPosition[phase]*16*4;
				break;
			case 3:
				map = temp_name::Map::loadFile("resources/MapData/4.ttt");
				player.position=map.startPosition[phase]*16*4;
				break;
			case 4:
				map = temp_name::Map::loadFile("resources/MapData/5.ttt");
				player.position=map.startPosition[phase]*16*4;
				break;
			case 5:
				map = temp_name::Map::loadFile("resources/MapData/6.ttt");
				player.position=map.startPosition[phase]*16*4;
				break;
			case 6:
				map = temp_name::Map::loadFile("resources/MapData/7.ttt");
				player.position=map.startPosition[phase]*16*4;
				break;
			case 7:
				map = temp_name::Map::loadFile("resources/MapData/8.ttt");
				player.position=map.startPosition[phase]*16*4;
				break;
			case 8:
				map = temp_name::Map::loadFile("resources/MapData/9.ttt");
				player.position=map.startPosition[phase]*16*4;
				break;
			case 9:
				map = temp_name::Map::loadFile("resources/MapData/10.ttt");
				player.position=map.startPosition[phase]*16*4;
				break;
			case 10:
				map = temp_name::Map::loadFile("resources/MapData/11.ttt");
				player.position=map.startPosition[phase]*16*4;
				break;
			case 11:
				map = temp_name::Map::loadFile("resources/MapData/12.ttt");
				player.position=map.startPosition[phase]*16*4;
				break;
			case 12:
				map = temp_name::Map::loadFile("resources/MapData/13.ttt");
				player.position=map.startPosition[phase]*16*4;
				break;
			case 13:
				map = temp_name::Map::loadFile("resources/MapData/14.ttt");
				player.position=map.startPosition[phase]*16*4;
				break;
			case 14:
				map = temp_name::Map::loadFile("resources/MapData/15.ttt");
				player.position=map.startPosition[phase]*16*4;
				break;
			case 15:
				map = temp_name::Map::loadFile("resources/MapData/16.ttt");
				player.position=map.startPosition[phase]*16*4;
				break;
		}
		map.loadBMPs(datapath);
		map.bmps.SetScale(4);
		test.createRocks(map);
	}
}

void InLevel::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
}

void InLevel::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void InLevel::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void InLevel::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void InLevel::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void InLevel::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void InLevel::OnShow()
{
	map.drawBack();
	test.drawRocks();
	map.drawBuilding();
	player.ShowBitmap();
	map.drawFront();
}
