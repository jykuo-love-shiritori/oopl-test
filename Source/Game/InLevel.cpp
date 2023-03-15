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
	isLeftKeyDown = false;
	isRightKeyDown = false;
	isUpKeyDown = false;
	isDownKeyDown = false;
}

InLevel::~InLevel()
{
}

void InLevel::OnBeginState()
{
}

void InLevel::OnMove()							// 移動遊戲元素
{
	const int speed=10;
	if(isLeftKeyDown){
		player.Move({-speed,0});
	}
	if(isRightKeyDown){
		player.Move({speed,0});
	}
	if(isUpKeyDown){
		player.Move({0,-speed});
	}
	if(isDownKeyDown){
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

	map.LoadBitmapByString({
        "resources/MineEntrance.bmp",
        "resources/DwarfRoom.bmp"
	}, RGB(255, 255, 255));
	map.SetScale(2.3);
    map.SetTopLeft(0,0);
	map.SetFrameIndexOfBitmap(0); // set init map for test

	Bittermap::CameraPosition = &player.position;
}

void InLevel::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == KEY_MOVE_LEFT) {
        isLeftKeyDown = true;
	}
	if (nChar == KEY_MOVE_RIGHT) {
        isRightKeyDown = true;
	}
	if (nChar == KEY_MOVE_UP) {
        isUpKeyDown = true;
	}
	if (nChar == KEY_MOVE_DOWN) {
        isDownKeyDown = true;
	}
}

void InLevel::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == KEY_MOVE_LEFT) {
        isLeftKeyDown = false;
	}
	if (nChar == KEY_MOVE_RIGHT) {
        isRightKeyDown = false;
	}
	if (nChar == KEY_MOVE_UP) {
        isUpKeyDown = false;
	}
	if (nChar == KEY_MOVE_DOWN) {
        isDownKeyDown = false;
	}
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
	map.Draw();
    player.ShowBitmap();
}
