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
    struct RockInfo {
        int score;
        int mohs;
    };
    std::map<int,RockInfo> rockInfos{
        {0,{1,1}},{1,{1,1}},{2,{2,2}},{3,{3,2}},{4,{5,3}},
        {5,{20,5}},{6,{7,4}},{7,{7,4}},{8,{3,2}},{9,{3,2}},
        {10,{7,4}},{11,{4,2}},{12,{6,3}},{13,{15,5}},{14,{8,4}},
        {15,{5,3}},{16,{9,4}}
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
