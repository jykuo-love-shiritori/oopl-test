#ifndef BAG_H
#define BAG_H

#include <vector>
#include <algorithm>

#include "RockManager.h"
#include "./Bittermap.h"
#include "Item.h"

class Bag {
    public:
        std::vector<Rock> popMinerals();

        bool use(Item itemType);
        bool trade(Item item, unsigned int price);
        void reset();

        /* getter */
        unsigned int getWeight() const { return _weight; }
        unsigned int getCount(Item itemType) const;
        
        /* helper */
        unsigned int calculateWeight() const;
    public:
        unsigned int _money = 0;
    private:
        std::vector<Item> _items;
        unsigned int _weight;
};

#endif /* BAG_H */
