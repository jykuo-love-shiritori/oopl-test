#pragma once

#include "../Library/gameutil.h"

namespace game_framework {
	class Character : public CMovingBitmap {
	public:
		void Move(int x, int y);
	};
}