#pragma once

#include "../Library/gameutil.h"
#include "./Map.h"


class Rock{
    public:
        void load();
        int getType();
        int getHealth();
        game_framework::Bittermap getRockBMPs();
        bool createRockInstance(unsigned int tileID);
        void createRocks(temp_name::Map map);
        void drawRocks();
    private:
        int _type;
        int _health;
        game_framework::Bittermap _rockBMPs;
        std::vector<Unity::Vector2i> _rockCoordinates;
		std::vector<int> _tilesAvailableForRocks={
			1,2,3,17,18,19,33,34,35,137,
			138,139,140,149,150,151,152,153,154,155,
			165,166,167,168,169,170,171,172,181,182,
			183,184,185,186,187,188,198,199,200,201,
			202,203,217,218,219,233,234,235,240,241,
			242,256,257,258,272,273,274};
};