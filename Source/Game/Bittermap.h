#pragma once

#include "../Library/gameutil.h"
#include "Vector2.h"

using namespace Unity;

namespace game_framework {
	class Bittermap : public CMovingBitmap {
	public:
		static Vector2i *CameraPosition;
		Vector2i position;
		void Draw();
		void Move(Vector2i vec);
	};
}