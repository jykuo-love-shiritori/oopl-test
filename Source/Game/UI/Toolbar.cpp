#include "stdafx.h"
#include "./Toolbar.h"

#include "../../Config/config.h"

#define LEFT 670
#define TOP 800
#define OFFSET 70

const auto kleftTop = Vector2i(LEFT, TOP);

void Toolbar::Init() {
    // _frame.LoadBitmapByString({
    //     "resources/EHBar.bmp"
    // },RGB(255,255,255));
    // _frame.SetScale(3.5);
    // _frame.SetTopLeft(LEFT, TOP);

    _itemSprite.LoadBitmapByString({
        "resources/Bomb/cherryBomb.bmp",
        "resources/hotGod.bmp"
    }, RGB(0,0,0));
    _itemSprite.SetScale(1);
}

void Toolbar::Show() {
    _count1 = _bag->getCount(Item::Bomb);
    _itemSprite.SetTopLeft(LEFT, TOP);
    _itemSprite.SetFrameIndexOfBitmap(0);
    _itemSprite.Show();
    _d1.lsb_location = kleftTop + Vector2i(55,55);
    _d1.Show();

    _count2 = _bag->getCount(Item::Food);
    _itemSprite.SetTopLeft(LEFT+OFFSET, TOP);
    _itemSprite.SetFrameIndexOfBitmap(1);
    _itemSprite.Show();
	_d2.lsb_location = kleftTop + Vector2i(125, 55);
	_d2.Show();
}