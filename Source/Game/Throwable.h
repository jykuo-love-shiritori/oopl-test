#pragma once
#include "Bittermap.h"

class Throwable
{
public:
   void Init();
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
