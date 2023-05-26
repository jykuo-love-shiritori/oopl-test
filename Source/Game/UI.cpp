#include "stdafx.h"
#include "UI.h"
#include "../Config/config.h"

#include <string>

void UI::alterScore(int delta){
    _score+=delta;
}

const auto LSB_LOCATION = Vector2i(SIZE_X-85, 193);

void UI::load() {
    _UIsprite.LoadBitmapByString({
		"resources/moneyUI.bmp"
	},RGB(255,255,255));
	_UIsprite.SetScale(3.5);
	_UIsprite.SetTopLeft(SIZE_X-300,20);

    _moneyNumbers.Init();

    eh.Init();
}

void UI::showUI() {
    const int offset=21; // each digit offset

    _UIsprite.ShowBitmap();

    _moneyNumbers.Show();

	eh.Show();
}