#pragma once

#include "../Library/gameutil.h"

namespace game_framework {
	class Map : public CMovingBitmap {
		//int current_map;
	public:
		//void SetMap(int MapNo);

		bool hasLeftMap();
		bool hasRightMap();
		bool hasUpMap();
		bool hasDownMap();

		void MoveToLeft();
		void MoveToRight();
		void MoveToUp();
		void MoveToDown();
	};
}