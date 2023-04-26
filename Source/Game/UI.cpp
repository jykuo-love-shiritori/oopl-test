#include "stdafx.h"
#include "UI.h"
#include "../Config/config.h"

#include <string>

game_framework::Bittermap UI::getUIsprite(){
    return _UIsprite;
}
game_framework::Bittermap UI::getNumberSprite(){
    return _moneyNumbers;
}

int UI::getScore(){
    return _score;
}

void UI::init(){
    _score=1234067;

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
    _moneyNumbers.SetFrameIndexOfBitmap(0);
    _moneyNumbers.SetTopLeft(SIZE_X-85,193);  // LSB location: (SIZE_X-85,193), <<1 -21
}

void UI::showUI(){
    const int offset=21;

    _UIsprite.ShowBitmap();

    if(_score==0){
        _moneyNumbers.ShowBitmap();
        return;
    }
    int i=0;
    while(_score/int(pow(10,i))!=0){
        if((_score%int(pow(10,i+1))<pow(10,i))){
            _moneyNumbers.SetFrameIndexOfBitmap(0);
        }
        else{
            int wut=std::to_string(_score%int(pow(10,i+1)))[0]-'0';
            _moneyNumbers.SetFrameIndexOfBitmap(wut);
        }
        _moneyNumbers.SetTopLeft(SIZE_X-85-offset*i,193);
        _moneyNumbers.ShowBitmap();
        i++;
    }
}