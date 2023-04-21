#pragma once

#include "../Game/Bittermap.h"
#include "Map.h"

using Unity::HitboxPool;
using Unity::Vector2i;
using temp_name::Map;

struct Rock {
    Vector2i position = {0, 0};
    unsigned int type = 0;
    unsigned int health = 1;
};

class RockManager{
    public:
        void loadBMP();
        int rockSelector();
        void createRocksOn(const std::vector<Vector2i> placeablePositions);
        void drawRocks() const;
        HitboxPool getHitbox() const;
        void clear();
    private:
        // TODO: bind map in manager but read-only
        // MapGetter _mapGetter;
		HitboxPool _hp;
        std::vector<Rock> _rocks;
        game_framework::Bittermap _rockBMPs;
};
