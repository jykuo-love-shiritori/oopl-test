#pragma once

#include "../Library/gameutil.h"
#include "../Unity/Vector2.h"

namespace game_framework {
	class Character : public CMovingBitmap {
	public:
		void Move(int x, int y);
		void Move(Unity::Vector2i vec);
	};
}