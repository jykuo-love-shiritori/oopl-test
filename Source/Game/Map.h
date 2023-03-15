#pragma once

#include "../Library/gameutil.h"
#include "../Unity/Vector2.h"

namespace game_framework {
	class Map : public CMovingBitmap {
		//int current_map;
	public:
		void Draw(Unity::Vector2i playerPos);
	};
}