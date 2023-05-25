#include "StdAfx.cpp"
#include "eh.h"
#include "../../Config/config.h"

void EH::Init() {
    _frame.LoadBitmapByString({
        "resources/EHBar.bmp"
    },RGB(255,255,255));
    _frame.SetScale(3.5);
    _frame.SetTopLeft(SIZE_X-140,SIZE_Y-230);

    _innerBar.LoadBitmapByString({
        "resources/barInner.bmp"
    },RGB(0,0,0));
    _innerBar.SetScale(3.5);
}

#define BOTTOM SIZE_Y-43
#define H_LEFT SIZE_X-83
#define E_LEFT SIZE_X-123
#define FULL_HEIGHT 143 

void EH::Show() {
    _frame.ShowBitmap();

    for(int i=(FULL_HEIGHT**_health); i>=0; --i){
        _innerBar.SetTopLeft(H_LEFT, BOTTOM-i);
        _innerBar.ShowBitmap();
    }
    for(int i=(FULL_HEIGHT**_energy); i>=0; --i){
        _innerBar.SetTopLeft(E_LEFT, BOTTOM-i);
        _innerBar.ShowBitmap();
    }
}