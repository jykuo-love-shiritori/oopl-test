#pragma once
#include "Bittermap.h"

class Throwable
{
public:
   Throwable()
   {
         sprite.LoadBitmapByString({
            "Resource/super/tower_super_1.bmp",
            "Resource/super/tower_super_2.bmp",
            "Resource/super/tower_super_3.bmp",
            "Resource/super/tower_super_4.bmp",
            "Resource/super/tower_super_5.bmp",
            "Resource/super/tower_super_6.bmp",
            "Resource/super/tower_super_7.bmp",
            "Resource/super/tower_super_8.bmp",
         },RGB(255,255,255));
         sprite.position = {0,0};
   }
   game_framework::Bittermap sprite;
   Vector2f movePosition={0,0};
   void SetPosition(Vector2f v){
      sprite.position = v;
   }
   void SetMovePosition(Vector2f v){
      movePosition = v;
   }
   void Update()
   {
      SetPosition(sprite.position+movePosition);
   }
   void Show()
   {
      sprite.Draw();
   }
};
