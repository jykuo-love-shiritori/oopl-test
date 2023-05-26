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
    unsigned int permaType=0;
    int health = 1; // negative number for over damage handle
    int timer=-1;
    std::map<int,int> rockScore{
        {0,1},{1,1},{2,2},{3,3},{4,5},
        {5,20},{6,7},{7,7},{8,3},{9,3},
        {10,7},{11,4},{12,6},{13,15},{14,8},
        {15,5},{16,9}
    };
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
