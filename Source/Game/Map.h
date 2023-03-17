#pragma once

#include "../Library/gameutil.h"
#include "./Bittermap.h"
//#include "./Hitbox.h"

namespace temp_name {
	class Map {
		Bittermap bmps;

		//std::vector<Hitbox> hbs;
	public:
		void drawBack();
		void drawFront();
		void pushBMP(game_framework::Bittermap bmp);
	};
}