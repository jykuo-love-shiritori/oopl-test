#pragma once

#include "../Library/gameutil.h"
#include "./Bittermap.h"
//#include "./Hitbox.h"

namespace temp_name {
	class Map {
		Unity::Vector2i mapSize={20,20};
		//std::vector<Hitbox> hbs;
	public:
		game_framework::Bittermap bmps;
		int backTile[400];
		void drawBack();
		void drawFront();
		void loadBMPs(std::string datapath);
	};
}