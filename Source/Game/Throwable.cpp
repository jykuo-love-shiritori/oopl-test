#include "stdafx.h"
#include "Throwable.h"

void Throwable::Init()
{
    sprite.LoadBitmapByString({
                                  "Resources/super/dart_1.bmp",
                                  "Resources/super/dart_2.bmp",
                                  "Resources/super/dart_3.bmp",
                                  "Resources/super/dart_4.bmp",
                                  "Resources/super/dart_5.bmp",
                                  "Resources/super/dart_6.bmp",
                                  "Resources/super/dart_7.bmp",
                                  "Resources/super/dart_8.bmp",
                              },RGB(255,255,255));
    sprite.position = {0,0};
}
