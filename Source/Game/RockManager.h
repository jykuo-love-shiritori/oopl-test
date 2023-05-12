#pragma once

#include "../Game/Bittermap.h"
#include "Map.h"

#include <vector>
#include <set>

using Unity::HitboxPool;
using Unity::Vector2i;
using temp_name::Map;

struct Rock {
    Vector2i position = {0, 0};
    unsigned int type = 0;
    int health = 1; // negative number for over damage handle
    int timer=-1;
};

class RockManager{
    public:
        void loadBMP();
        int rockSelector();
        void createRocksOn(const std::vector<Vector2i> placeablePositions);
        void drawRocks() const;

        HitboxPool getHitbox() const;
        std::vector<Rock*> getCollisionWith(Rect hitbox);
        std::vector<Vector2i> getPositions() const;

        void remove(std::set<Rock*> ptrs);
        bool playBreakAnimation(Vector2i exit, unsigned int *score);
        void clear();
    private:
        // TODO: bind map in manager but read-only
        // MapGetter _mapGetter;
		HitboxPool _hp;
        std::vector<Rock> _rocks;
        //std::map<position, Rock> _rocks;
        game_framework::Bittermap _rockBMPs;
};