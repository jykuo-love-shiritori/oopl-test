#pragma once

#include "../Library/gameutil.h"
#include "../Unity/Vector2.h"
#include "../Unity/Hitbox.h"

using namespace Unity;

namespace game_framework {
	class Bittermap : public CMovingBitmap {
		Vector2i size = Vector2i(1,1);
		bool _isShow = true;
	public:
		static Vector2i *CameraPosition;
		Vector2i position;
		void Show(); /* ShowBitmap if(_isShow) */
		void Draw();
		void Draw(Vector2i position, int frameIndex) const;
		void Move(Vector2i vec);
		void MoveWithCollision(Vector2i moveVec, HitboxPool hitboxPool);
		
		/* Setter */
		void SetHitBox(Vector2i size);
		void SetShow(bool isShow=true) {_isShow = isShow;}
		
		/* Getter */
		/* Get the hitbox with the current position as the top left */
		Rect GetHitbox() const ;
		bool isShown() const {return _isShow;}
	};
}