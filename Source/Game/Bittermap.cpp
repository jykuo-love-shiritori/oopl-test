#include "stdafx.h"
#include "Bittermap.h"

#include "../Config/config.h"

using namespace game_framework;

Vector2i *Bittermap::CameraPosition;

void Bittermap::Move(Unity::Vector2i vec)
{
	position = position + vec;
}

void Bittermap::Draw() {
	if (isShow) {
		SetTopLeft(
			position.x - CameraPosition->x + SIZE_X/2,
			position.y - CameraPosition->y + SIZE_Y/2
		);
		ShowBitmap();
	}
}
