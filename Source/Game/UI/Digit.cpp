#include "stdafx.h"
#include "Digit.h"
#include "../Config/config.h"

#include <string>

//#define LSB_LOCATION {SIZE_X-85, 193}
#define OFFSET 14 // each digit offset for scaler 1

game_framework::Bittermap Digit::_n;

void Digit::Init() {
    if (_n.IsBitmapLoaded()) return;
    _n.LoadBitmapByString({
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
}

void Digit::Show() {
    _n.SetScale(_scalar);
    std::string result = std::to_string(*_number);
    for (unsigned int i = 0; i < result.length(); ++i) {
        const auto pos = lsb_location - Vector2i(OFFSET*_scalar*i, 0);
        const auto num = result[result.length()-1 -i] - '0';
        _n.ShowBitmap(pos.x, pos.y, num);
    }
}