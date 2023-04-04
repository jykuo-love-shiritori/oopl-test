#pragma once

#include "../Game/Map.h"


class Rock{
    public:
        void load();
        int getType();
        int getHealth();
        game_framework::Bittermap getRockBMPs();
        void createRocks(temp_name::Map map);
        void drawRocks();
		Unity::HitboxPool hp;
    private:
        int _type;
        int _health;
        game_framework::Bittermap _rockBMPs;
        std::vector<Unity::Vector2i> _rockCoordinates;
        std::vector<int> _rockTypes;
};