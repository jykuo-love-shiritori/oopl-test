#pragma once

#include "../Game/Map.h"


class Rock{
    public:
        void load();
        int getType();
        int getHealth();
        game_framework::Bittermap getRockBMPs();
        int rockSelector();
        void createRocks(temp_name::Map map);
        void drawRocks();
		Unity::HitboxPool hp;
    private:
        int _type;
        int _health;
        game_framework::Bittermap _rockBMPs;
        std::vector<Unity::Vector2i> _rockCoordinates;
        std::vector<int> _rockTypes;
        
        enum Minerals{
        stoneType1,
        stoneType2,
        copperNode,
        ironNode,
        goldNode,
        iridiumnNode,
        amethystNode,
        topazNode,
        quartz,
        earthCrystal,
        aquamarineNode,
        frozenTear,
        jadeNode,
        diamondNode,
        emeraldNode,
        fireQuartz,
        rubyNode
    };
};