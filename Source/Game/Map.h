#pragma once

#include "../Library/gameutil.h"
#include "./Bittermap.h"
#include "../Unity/Vector2.h"
#include "../Unity/Hitbox.h"

#include <set>

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
		/* Loader */
		void loadFile(std::string file);
		void loadBMPs(std::string datapath);

		/* put in OnShow */
		void drawBack();
		void drawBuilding();
		void drawFront();

		/* something */
		bool isPlaceable(Vector2i position) const;
		std::vector<Vector2i> getPlaceablePositions() const;

		/* Getter */
		Unity::Vector2i getMapSize() const;
	private:
		Unity::Vector2i mapSize;
		void loadHitbox();
		void drawTiles(std::vector<unsigned short> tile);
		const std::set<unsigned int> _tilesAvailableForRocks = {
			//FIXME: cant catch 140 235 and some others as tiles available
			1,2,3,17,18,19,33,34,35,137,
			138,139,140,149,150,151,152,153,154,155,
			165,166,167,168,169,170,171,172,181,182,
			183,184,185,186,187,188,198,199,200,201,
			202,203,217,218,219,233,234,235,240,241,
			242,256,257,258,272,273,274};
	};
}