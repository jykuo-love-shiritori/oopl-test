#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "stages.h"

#include "keymap.h"

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

	std::string datapath="resources/MapTextures/mine";
	map = temp_name::Map::loadFile("resources/MapData/29.ttt");
	map.loadBMPs(datapath);
	map.bmps.SetScale(4);

	test.LoadBitmapByString({
		"resources/giraffe.bmp"
		}, RGB(255, 255, 255));
	test.SetScale(10);

	Bittermap::CameraPosition = &player.position;
}

void InLevel::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
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
	map.drawBuilding();
	map.drawFront();
    player.ShowBitmap();
}
