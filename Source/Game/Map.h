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
		static void loadFile(std::string file);
		static std::vector<unsigned short> backTile;
		static std::vector<unsigned short> buildingTile;
		static std::vector<unsigned short> frontTile;
		void drawBack();
		void drawBuilding();
		void drawFront();
		void loadBMPs(std::string datapath);
	};
}