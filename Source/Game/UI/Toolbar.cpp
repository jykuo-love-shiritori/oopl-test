#include "stdafx.h"
#include "./Toolbar.h"

#include "../../Config/config.h"

#define LEFT 600
#define TOP 800
#define OFFSET 70

const auto kLeftTop = Vector2i(LEFT, TOP);

void Toolbar::Init() {
    // _frame.LoadBitmapByString({
    //     "resources/EHBar.bmp"
    // },RGB(255,255,255));
    // _frame.SetScale(3.5);
    // _frame.SetTopLeft(LEFT, TOP);

    _itemSprite.LoadBitmapByString({
        "resources/Bomb/cherryBomb.bmp",
        "resources/Bomb/bomb.bmp",
        "resources/Bomb/megaBomb.bmp",
        "resources/hotGod.bmp"
    }, RGB(0,0,0));
    _itemSprite.SetScale(1);
    
    _d1.lsb_location = kLeftTop + Vector2i(55 + OFFSET*0, 55);
    _d2.lsb_location = kLeftTop + Vector2i(55 + OFFSET*1, 55);
    _d3.lsb_location = kLeftTop + Vector2i(55 + OFFSET*2, 55);
    _d4.lsb_location = kLeftTop + Vector2i(55 + OFFSET*3, 55);

    _d1_price.lsb_location = kLeftTop + Vector2i(20 + OFFSET*0, 0);
    _d2_price.lsb_location = kLeftTop + Vector2i(20 + OFFSET*1, 0);
    _d3_price.lsb_location = kLeftTop + Vector2i(20 + OFFSET*2, 0);
    _d4_price.lsb_location = kLeftTop + Vector2i(20 + OFFSET*3, 0);
}

void Toolbar::Show() {
    for (int i = 0; i<4; i++) {
        _itemSprite.SetTopLeft(LEFT+OFFSET*i, TOP);
        _itemSprite.SetFrameIndexOfBitmap(i);
		_itemSprite.Show();
    }

    _count1 = _bag->getCount(Item::cherryBomb);
    _d1.Show();

    _count2 = _bag->getCount(Item::Bomb);
    _d2.Show();

    _count3 = _bag->getCount(Item::megaBomb);
    _d3.Show();

    _count4 = _bag->getCount(Item::Food);
	_d4.Show();

    if( _isShowPrice ) {
        _d1_price.Show();
        _d2_price.Show();
        _d3_price.Show();
        _d4_price.Show();
    }
}
