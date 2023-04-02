#pragma once

#include "../Library/gameutil.h"
#include "./Bittermap.h"
#include "../Unity/Vector2.h"
#include "../Unity/Hitbox.h"
//#include "./Hitbox.h"

namespace temp_name {
	class Map {
	public:
		static std::vector<Unity::Vector2i> startPosition;

		Unity::HitboxPool hp;
		game_framework::Bittermap bmps;

		std::vector<unsigned short> backTile;
		std::vector<unsigned short> buildingTile;
		std::vector<unsigned short> frontTile;
	public:
		void loadFile(std::string file);
		void loadBMPs(std::string datapath);

		/* put in OnShow */
		void drawBack();
		void drawBuilding();
		void drawFront();

		/* Getter */
		Unity::Vector2i getMapSize();
	private:
		Unity::Vector2i mapSize;
		void loadHitbox();
		void drawTiles(std::vector<unsigned short> tile);
	};
}