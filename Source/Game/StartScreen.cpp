#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "stages.h"

using namespace game_framework;
using namespace game_framework::stage;
/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲開頭畫面物件
/////////////////////////////////////////////////////////////////////////////

StartScreen::StartScreen(CGame *g) : CGameState(g)
{
}

void StartScreen::OnInit()
{
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	// ShowInitProgress(0, "Start Initialize...");	// 一開始的loading進度為0%

	background.LoadBitmapByString({
        "resources/Intro.bmp"
    });
	{
		double scaleX = (double)(SIZE_X)/background.GetWidth();
		double scaleY = (double)(SIZE_Y)/background.GetHeight();
		background.SetScale(scaleX>scaleY ? scaleX : scaleY);
	}
    background.SetCenter(SIZE_X/2, SIZE_Y/2);

	title.LoadBitmapByString({
		"resources/logo.bmp"
	}, RGB(255, 255, 255));
	title.SetScale(1.5);
	title.SetCenter(SIZE_X/2, SIZE_Y/4);

	LMBtoStart.LoadBitmapByString({
		"resources/LMBtoStart.bmp"
	}, RGB(255, 255, 255));
	LMBtoStart.SetScale(1);
	LMBtoStart.SetCenter(SIZE_X/2, SIZE_Y*3/5);
}

void StartScreen::OnLButtonDown(UINT nFlags, CPoint point)
{
	GotoGameState(GAME_STATE_RUN);		// 切換至GAME_STATE_RUN
}

void StartScreen::OnShow()
{
	background.ShowBitmap();
	title.ShowBitmap();
	LMBtoStart.ShowBitmap();
}
