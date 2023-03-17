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

	int mapBack[] = {
		78,78,78,78,78,78,0,0,0,0,0,0,0,0,78,78,78,78,78,78,
		78,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,78,78,78,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,78,78,78,
		0,0,0,0,0,0,189,219,219,219,219,219,188,203,0,0,0,0,0,78,
		0,0,189,219,219,219,219,187,235,235,235,186,219,219,219,219,219,0,0,0,
		0,218,219,187,235,235,235,236,139,141,139,234,235,235,186,219,219,188,204,0,
		0,234,235,236,138,141,139,139,140,139,170,139,138,139,234,235,186,219,188,0,
		0,139,139,154,139,139,156,139,139,139,139,139,139,156,139,155,234,186,219,188,
		0,0,139,139,139,139,139,139,138,139,156,139,139,139,139,139,139,234,186,219,
		0,0,139,138,139,171,172,139,139,139,139,139,138,139,138,139,156,139,218,219,
		0,0,139,139,139,139,139,139,156,139,139,139,139,140,139,139,139,202,189,219,
		0,0,139,139,156,139,139,139,139,139,141,138,139,139,139,139,139,218,219,219,
		0,0,139,139,139,139,139,139,139,139,139,138,139,139,139,139,202,189,219,219,
		0,0,203,204,141,139,139,156,155,139,139,139,139,139,156,139,218,219,219,219,
		0,0,219,220,139,139,139,139,139,139,139,139,139,139,139,139,234,235,186,219,
		0,0,235,236,155,139,139,139,139,139,156,139,139,139,139,141,139,139,218,219,
		78,78,78,139,139,139,139,139,202,203,204,139,139,139,139,139,139,156,218,219,
		78,78,78,139,139,139,139,156,218,219,220,139,139,139,154,139,139,139,234,235,
		78,78,78,139,139,139,139,139,234,235,236,139,139,139,139,139,139,0,0,0,
		78,78,78,78,78,0,0,0,0,0,0,0,0,0,0,0,0,0,78,78};

	std::string datapath="resources/MapTextures/mine";
	map.loadBMPs(datapath);
	for (int i = 0; i < 400; i++) {
		map.backTile[i] = mapBack[i];
	}
	map.bmps.SetScale(4);

	test.LoadBitmapByString({
	//"resources/MapTextures/mine/0.bmp"
		//"resources/MineEntrance.bmp"
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
	//test.Draw();
	map.drawBack();
    player.ShowBitmap();
}
