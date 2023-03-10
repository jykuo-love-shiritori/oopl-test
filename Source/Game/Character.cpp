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
	int x = GetLeft() + vec.x;
	int y = GetTop() + vec.y;
	SetTopLeft(x, y);
}
