#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "stages.h"

#include <shobjidl_core.h>
#include <string>
#include <winuser.h>

#include "../Config/keymap.h"
#include "../Config/scaler.h"

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
	player.position = Vector2i(10,4) * TILE_SIZE * SCALE_SIZE;

	map.loadFile("resources/MapData/1.ttt");
	map.loadBMPs(datapath);
	map.bmps.SetScale(SCALE_SIZE);

	test.load();

	Bittermap::CameraPosition = &player.position;
}

void InLevel::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	/* debug key start */
	switch (nChar) {
		case 'J': // next map
		case 'K': // previous map
			if(nChar=='J'){
				if(++phase > 15) phase--;
			} else { // nChar=='K'
				if(--phase < 0) phase++;
			}

			map.loadFile("resources/MapData/" + std::to_string(phase+1) + ".ttt");
			player.position=map.startPosition[phase] * TILE_SIZE * SCALE_SIZE; // hard code 1-16(0-15)
			break;
		case 'O': // create rock
			test.createRocks(map);
			break;
	}
	/* debug key end */
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
	player.Draw();
	map.drawFront();
}
