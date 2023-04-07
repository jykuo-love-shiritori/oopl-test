#pragma once

#include "../Library/gameutil.h"
#include "../Unity/Vector2.h"

using namespace Unity;

namespace game_framework {
	class Bittermap : public CMovingBitmap {
	public:
		static Vector2i *CameraPosition;
		Vector2i position;
		bool isShow = true;
		void Draw();
		void Move(Vector2i vec);
	};
}