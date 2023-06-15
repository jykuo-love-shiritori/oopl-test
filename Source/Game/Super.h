#pragma once
#include "Bittermap.h"
#include "Bug.h"
#include "Throwable.h"

float Distance(game_framework::Bittermap a,game_framework::Bittermap b);

class Super
{
   game_framework::Bittermap sprite;
    vector<Throwable> throwables ;
public:

    void Init();
   void draw();

   void update(Bug &b);
   void SetPosition(Vector2i vector2);;
   int shootTimeCounter =0;
   void attack(Vector2f bug);
};
