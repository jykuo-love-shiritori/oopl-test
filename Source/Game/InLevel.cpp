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
	player.Move(playerMoving);
	/* Map move */
	/* Border detect */
    if(player.GetCenter().x < 0){
		if (map.hasLeftMap()) {
			map.MoveToLeft();
			player.Move(SIZE_X, 0);
		}
		else
			player.Move(-player.GetCenter().x, 0);
    }
	if (player.GetCenter().x > SIZE_X) {
		if (map.hasRightMap()) {
			map.MoveToRight();
			player.Move(-SIZE_X, 0);
		}
		else
			player.Move(SIZE_X-player.GetCenter().x, 0);
	}
	if (player.GetCenter().y < 0) {
		if (map.hasUpMap()) {
			map.MoveToUp();
			player.Move(0, SIZE_Y);
		}
		else
			player.Move(0, -player.GetCenter().y);
	}
	if (player.GetCenter().y > SIZE_Y) {
		if (map.hasDownMap()) {
			map.MoveToDown();
			player.Move(0, -SIZE_Y);
		}
		else
			player.Move(0, SIZE_Y-player.GetCenter().y);
	}
}

void InLevel::OnInit()  								// 遊戲的初值及圖形設定
{
	player.LoadBitmapByString({
        "resources/giraffe.bmp"
	}, RGB(255, 255, 255));
	player.SetScale(1);
	player.SetTopLeft(750,700);

	map.LoadBitmapByString({
        "resources/MineEntrance.bmp",
        "resources/DwarfRoom.bmp"
	}, RGB(255, 255, 255));
	map.SetScale(2.3);
    map.SetTopLeft(0,0);
	map.SetFrameIndexOfBitmap(0); // set init map for test
}

void InLevel::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const int speed = 10;
	if (nChar == KEY_MOVE_LEFT) {
        playerMoving = Unity::Vector2i(-speed, 0);
	}
	if (nChar == KEY_MOVE_RIGHT) {
        playerMoving = Unity::Vector2i(speed, 0);
	}
	if (nChar == KEY_MOVE_UP) {
        playerMoving = Unity::Vector2i(0, -speed);
	}
	if (nChar == KEY_MOVE_DOWN) {
        playerMoving = Unity::Vector2i(0, speed);
	}
}

void InLevel::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == KEY_MOVE_LEFT) {
        playerMoving = Unity::Vector2i(0, 0);
	}
	if (nChar == KEY_MOVE_RIGHT) {
        playerMoving = Unity::Vector2i(0, 0);
	}
	if (nChar == KEY_MOVE_UP) {
        playerMoving = Unity::Vector2i(0, 0);
	}
	if (nChar == KEY_MOVE_DOWN) {
        playerMoving = Unity::Vector2i(0, 0);
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
    map.ShowBitmap();
    player.ShowBitmap();
}
