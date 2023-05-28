#include "stdafx.h"
#include "RightTopUI.h"
#include "../../Config/config.h"

#include <string>

void RightTopUI::alterScore(int delta){
    _score+=delta;
}

const auto LSB_LOCATION = Vector2i(SIZE_X-85, 193);

void RightTopUI::Init() {
    _UIsprite.LoadBitmapByString({
		"resources/moneyUI.bmp"
	},RGB(255,255,255));
	_UIsprite.SetScale(3.5);
	_UIsprite.SetTopLeft(SIZE_X-300,20);

    _moneyNumbers.Init();
    _moneyNumbers.lsb_location = {SIZE_X-85, 193};
}

void RightTopUI::Show() {
    const int offset=21; // each digit offset

    _UIsprite.ShowBitmap();

    _moneyNumbers.Show();
}