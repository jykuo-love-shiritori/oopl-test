#include "stdafx.h"
#include "Character.h"

using namespace game_framework;

void Character::Move(int deltaX, int deltaY)
{
	int x = GetLeft() + deltaX;
	int y = GetTop() + deltaY;
	SetTopLeft(x, y);
}

void Character::Move(Unity::Vector2i vec)
{
	Move(vec.x, vec.y);
}
