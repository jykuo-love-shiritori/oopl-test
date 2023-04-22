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
		auto thisHitbox = GetHitBox();
		auto collisions = hitboxPool.Collide(thisHitbox);
		if (collisions.size() == 0) break;

		auto totalReaction = Vector2i(0, 0);
		for (auto const &wallBox : collisions) {
			auto currDist = thisHitbox.getCenter() - wallBox.getCenter();

			auto limitDist = wallBox.getRadius() + thisHitbox.getRadius();
			auto reactionVec = Vector2i(
				(currDist.x >= 0 ? limitDist.x : -limitDist.x) - currDist.x,
				(currDist.y >= 0 ? limitDist.y : -limitDist.y) - currDist.y
			);

			if (abs(reactionVec.x) == abs(reactionVec.y)) {
				// nop
			}
			else if (abs(reactionVec.x) < abs(reactionVec.y)) {
				reactionVec.y = 0;
			}
			else {
				reactionVec.x = 0;
			}
			totalReaction = totalReaction + reactionVec;
		}
		if (moveVec.y == 0) {
			totalReaction.y = 0;
		}
		else if (moveVec.x == 0) {
			totalReaction.x = 0;
		}
		else {
			if (abs(totalReaction.x) == abs(totalReaction.y)) {
				// nop
			}
			else if (abs(totalReaction.x) > abs(totalReaction.y)) {
				totalReaction.y = 0;
			}
			else {
				totalReaction.x = 0;
			}
		}
		this->Move(totalReaction);
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

Rect Bittermap::GetHitBox() const {
	return Rect::FromTopLeft(this->position, this->size);
}