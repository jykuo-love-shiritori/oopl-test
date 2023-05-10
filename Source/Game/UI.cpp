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

    _moneyNumbers.LoadBitmapByString({
        "resources/Fonts/0.bmp",
        "resources/Fonts/1.bmp",
        "resources/Fonts/2.bmp",
        "resources/Fonts/3.bmp",
        "resources/Fonts/4.bmp",
        "resources/Fonts/5.bmp",
        "resources/Fonts/6.bmp",
        "resources/Fonts/7.bmp",
        "resources/Fonts/8.bmp",
        "resources/Fonts/9.bmp"
    },RGB(0,0,0));
    _moneyNumbers.SetScale(1.5);

    _ehBar.LoadBitmapByString({
        "resources/EHBar.bmp"
    },RGB(255,255,255));
    _ehBar.SetScale(3.5);
    _ehBar.SetTopLeft(SIZE_X-140,SIZE_Y-230);

    _innerBar.LoadBitmapByString({
        "resources/barInner.bmp"
    },RGB(0,0,0));
    _innerBar.SetScale(3.5);
    _innerBar.SetTopLeft(SIZE_X-83,SIZE_Y-43);  //inner health bar init position
}

void UI::showUI() {
    const int offset=21; // each digit offset

    _UIsprite.ShowBitmap();
    _ehBar.ShowBitmap();

    std::string result = std::to_string(_score);
    for (unsigned int i = 0; i < result.length(); ++i) {
        const auto pos = LSB_LOCATION - Vector2i(offset*i, 0);
        const auto num = result[result.length()-1 -i] - '0';
        _moneyNumbers.ShowBitmap(pos.x, pos.y, num);
    }
    const auto fullHP = 143;
    for(int i=0;i<*_health;i++){
        _innerBar.SetTopLeft(SIZE_X-83,SIZE_Y-43-i);
        _innerBar.ShowBitmap();
    }
}