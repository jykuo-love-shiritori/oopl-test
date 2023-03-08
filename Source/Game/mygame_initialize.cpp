#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"

using namespace game_framework;
/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲開頭畫面物件
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame *g) : CGameState(g)
{
}

void CGameStateInit::OnInit()
{
	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	// ShowInitProgress(0, "Start Initialize...");	// 一開始的loading進度為0%
	// FIXME: nobody call ^this but still display.
	//
	// 開始載入資料
	//
	background.LoadBitmapByString({
        "resources/Intro.bmp"
    });
    background.SetTopLeft(0,0);

	title.LoadBitmapByString({
		"resources/logo.bmp"
	}, RGB(255, 255, 255));
	title.SetTopLeft(
		SIZE_X/2 - title.GetWidth()/2,
		SIZE_Y/10);

	LMBtoStart.LoadBitmapByString({
		"resources/LMBtoStart.bmp"
	}, RGB(255, 255, 255));
	LMBtoStart.SetTopLeft(
		SIZE_X/2 - LMBtoStart.GetWidth()/2,
		SIZE_Y/2);
	//Sleep(1000);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
}

void CGameStateInit::OnBeginState()
{
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{

}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
	GotoGameState(GAME_STATE_RUN);		// 切換至GAME_STATE_RUN
}

void CGameStateInit::OnShow()
{
	background.ShowBitmap(10);
	title.ShowBitmap(1.5);
	LMBtoStart.ShowBitmap(1);
}
