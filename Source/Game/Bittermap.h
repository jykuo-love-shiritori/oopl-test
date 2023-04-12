#pragma once

#include "../Library/gameutil.h"
#include "../Unity/Vector2.h"
#include "../Unity/Hitbox.h"

using namespace Unity;

namespace game_framework {
	class Bittermap : public CMovingBitmap {
		Vector2i size = Vector2i(1,1);
	public:
		static Vector2i *CameraPosition;
		Vector2i position;
		bool isShow = true;
		void Draw();
		void Move(Vector2i vec);
		void MoveWithCollision(Vector2i moveVec, HitboxPool hitboxPool);
		
		/* Setter */
		void SetHitBox(Vector2i size);
		
		/* Getter */
		/* Get the hitbox with the current position as the top left */
		Rect GetHitBox() const ;
	};
}