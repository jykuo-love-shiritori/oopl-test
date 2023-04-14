#pragma once

#include "../Library/gameutil.h"
#include "./Bittermap.h"
#include "../Unity/Vector2.h"
#include "../Unity/Hitbox.h"

#include <set>
#include <vector>
#include <string>

namespace temp_name {
	class Map {
	public:
		/* Types and type aliases */
		struct Info {
			Vector2i startPosition;
			bool hasPresetExit;
			Vector2i presetExitPosition;
		};
		
		/* Loader */
		void loadFile(std::string filePath);
		void loadBMPs(std::string dirPath);

		/* put in OnShow */
		void drawBack();
		void drawBuilding();
		void drawFront();

		/* misc */
		bool isPlaceable(Vector2i position) const;
		std::vector<Vector2i> getPlaceablePositions() const;

		/* Getter */
		Unity::Vector2i getMapSize() const;
		Info getInfo() const;
		unsigned int getLevel() const;

		/* Setter */
		void setLevel(unsigned int index);
		/**
		 * if no next level return false and don't change level;
		 */
		bool nextLevel();

		/* All other PUBLIC data members */
		Unity::HitboxPool hp;
		game_framework::Bittermap bmps;

	private:
		/* Static constants */
		static std::set<unsigned int> kTilesAvailableForRocks;
		static std::vector<Unity::Vector2i> kStartPosition;
		
		/* helper functions */
		void loadHitbox();
		void drawTiles(std::vector<unsigned short> tile);

		/* All other data members */
		std::vector<unsigned short> m_backTile;
		std::vector<unsigned short> m_buildingTile;
		std::vector<unsigned short> m_frontTile;
		
		unsigned int m_mapIndex;
		Unity::Vector2i m_mapSize;
	};
}