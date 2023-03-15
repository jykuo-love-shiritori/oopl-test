#include "stdafx.h"
#include "Bittermap.h"

using namespace game_framework;

Vector2i *Bittermap::CameraPosition;

void Bittermap::Move(Unity::Vector2i vec)
{
	position = position + vec;
}

void Bittermap::Draw() {
	SetTopLeft(
		position.x - CameraPosition->x,
		position.y - CameraPosition->y
	);
	ShowBitmap();
}
