#include "stdafx.h"
#include "Bittermap.h"

#include "../Config/config.h"

using namespace game_framework;
using namespace Unity;

Vector2i *Bittermap::CameraPosition;

void Bittermap::Move(Unity::Vector2i vec)
{
	position = position + vec;
}

void Bittermap::MoveWithCollision(const Vector2i moveVec, const HitboxPool hitboxPool)
{
	this->position = this->position + moveVec;
	while (true) {
		auto thisHitbox = GetHitbox();
		auto collisions = hitboxPool.Collide(thisHitbox);
		if (collisions.size() == 0) break;
		auto totalReaction = Vector2i(0, 0);
		for (auto const &wallBox : collisions) {
			auto currDist = thisHitbox.getCenter() - wallBox.getCenter();
			totalReaction = (totalReaction + currDist) / 20; // base on giraffe speed
			continue;
		}
		this->Move(totalReaction);
	}
}

void Bittermap::Show() {
	if (_isShow) {
		ShowBitmap();
	}
}

void Bittermap::Draw() {
	if (_isShow) {
		SetTopLeft(
			position.x - CameraPosition->x + SIZE_X/2,
			position.y - CameraPosition->y + SIZE_Y/2
		);
		ShowBitmap();
	}
}

void Bittermap::Draw(Vector2i pos, int fIndex) const {
	ShowBitmap(
		pos.x - CameraPosition->x + SIZE_X/2,
		pos.y - CameraPosition->y + SIZE_Y/2,
		fIndex
	);
}


void Bittermap::SetHitBox(Vector2i size) {
	this->size = size;
}

Rect Bittermap::GetHitbox() const {
	return Rect::FromTopLeft(this->position, this->size);
}