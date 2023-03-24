#pragma once

#include "../Library/gameutil.h"
#include "./Bittermap.h"
//#include "./Hitbox.h"

namespace temp_name {
	class Map {
		Unity::Vector2i mapSize={20,20}; // FIXME: hardcode map size
		//std::vector<Hitbox> hbs;
	public:
		game_framework::Bittermap bmps;
		static Map loadFile(std::string file);
		std::vector<unsigned short> backTile;
		std::vector<unsigned short> buildingTile;
		std::vector<unsigned short> frontTile;
		void drawBack();
		void drawBuilding();
		void drawFront();
		void loadBMPs(std::string datapath);
	};
}