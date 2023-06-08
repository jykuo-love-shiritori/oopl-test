#include "stdafx.h"
#include "Super.h"

float Distance(game_framework::Bittermap a, game_framework::Bittermap b)
{
    return sqrt((a.position.x-b.position.x)
        * (a.position.x-b.position.x)+
        (a.position.y-b.position.y)
        * (a.position.y-b.position.y));
}

Super::Super()
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

void Super::draw()
{
    sprite.Draw();
    for(auto & t : throwables)
    {
        t.Show();
    }
}

void Super::update(Bug& b)
{
    shootTimeCounter +=1;
    int index =0;
    for( auto & t : throwables)
    {
        t.Update();
        game_framework::Bittermap tmp;
        tmp.position = b.GetHitbox().getTopLeft();
        if(Distance (t.sprite ,tmp)<3.f)
        {
            b.alterHealth(100);
            break;
        }else if(
            Distance (sprite ,t.sprite)>600.f
        )
        {
            break;
        }
        index ++;
    }
    if(index !=(int)throwables.size())
    {
        throwables.erase(throwables.begin()+index);
    }
    if(shootTimeCounter>=10)
    {
        attack(b.GetHitbox().getTopLeft());
    }
}

void Super::SetPosition(Vector2i vector2)
{
    sprite.position  =vector2;
}

void Super::attack(Vector2f bug)
{
    shootTimeCounter = 0;
    Vector2f target = sprite.position - bug;
    Throwable next ;
    next.SetPosition(sprite.position);
    next.SetMovePosition(target);
    throwables.push_back(next);
}
