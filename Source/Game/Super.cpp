#include "stdafx.h"
#include "Super.h"

float Distance(game_framework::Bittermap a, game_framework::Bittermap b)
{
    return sqrt((a.position.x-b.position.x)
        * (a.position.x-b.position.x)+
        (a.position.y-b.position.y)
        * (a.position.y-b.position.y));
}

void Super::Init()
{
    sprite.LoadBitmapByString({
                                  "Resources/super/tower_super_1.bmp",
                                  "Resources/super/tower_super_2.bmp",
                                  "Resources/super/tower_super_3.bmp",
                                  "Resources/super/tower_super_4.bmp",
                                  "Resources/super/tower_super_5.bmp",
                                  "Resources/super/tower_super_6.bmp",
                                  "Resources/super/tower_super_7.bmp",
                                  "Resources/super/tower_super_8.bmp",
                              },RGB(0,0,0));
    sprite.position = {-100,-100};
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
        bool isHitting =game_framework::CMovingBitmap::IsOverlap((game_framework::CMovingBitmap)t.sprite,(game_framework::CMovingBitmap)b.GetSprite());
        b.setHit(isHitting);
        if ( isHitting ) { /* if isHitting */
            b.alterHealth(-100);
            break;
        }
        if( Distance (sprite ,t.sprite)>600.f )
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
        attack(b.GetSprite().position);
        shootTimeCounter = 0;
    }
}

void Super::SetPosition(Vector2i vector2)
{
    sprite.position  =vector2;
}

void Super::attack(Vector2f bug)
{
    Vector2f target = bug - sprite.position ;
    Throwable next ;
    next.Init();
    next.sprite.SetHitBox({next.sprite.GetWidth(),next.sprite.GetHeight()});
    next.SetPosition(sprite.position);
    next.SetMovePosition(target/2);
    throwables.push_back(next);
}
