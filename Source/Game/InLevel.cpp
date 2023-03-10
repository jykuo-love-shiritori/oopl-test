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
    if(phase==1){
        if(character.GetLeft()>1300 && character.GetTop()>425 && character.GetTop()<475){
            phase++;
            character.SetTopLeft(100,character.GetTop());
        }
    }
    else if(phase==2){
        if(character.GetLeft()<100 && character.GetTop()>425 && character.GetTop()<475){
            phase--;
            character.SetTopLeft(1300,character.GetTop());
        }
    }
    if(character.GetLeft()<0){
        character.SetTopLeft(0,character.GetTop());
    }
    if(character.GetLeft()+character.GetWidth()>1400){
        character.SetTopLeft(1400-character.GetWidth(),character.GetTop());
    }
    if(character.GetTop()<0){
        character.SetTopLeft(character.GetLeft(),0);
    }
    if(character.GetTop()+character.GetHeight()>900){
        character.SetTopLeft(character.GetLeft(),900-character.GetHeight());
    }
}

void InLevel::OnInit()  								// 遊戲的初值及圖形設定
{
	character.LoadBitmapByString({
        "resources/giraffe.bmp"
	}, RGB(255, 255, 255));
    character.SetTopLeft(750,700);

	background.LoadBitmapByString({
        "resources/MineEntrance.bmp",
        "resources/DwarfRoom.bmp"
	}, RGB(255, 255, 255));
    background.SetTopLeft(0,0);
}

void InLevel::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_LEFT) {
		character.SetTopLeft(character.GetLeft()-50,character.GetTop());
	}
	if (nChar == VK_RIGHT) {
		character.SetTopLeft(character.GetLeft()+50,character.GetTop());
	}
	if (nChar == VK_UP) {
		character.SetTopLeft(character.GetLeft(),character.GetTop()-50);
	}
	if (nChar == VK_DOWN) {
		character.SetTopLeft(character.GetLeft(),character.GetTop()+50);
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
    if(phase==1){
        background.SetFrameIndexOfBitmap(0);
    }
    else if(phase==2){
        background.SetFrameIndexOfBitmap(1);
    }
    background.ShowBitmap(2.3);
    character.ShowBitmap(1);
}
