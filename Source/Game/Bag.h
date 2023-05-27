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
        void append(Item item);

        bool use(Item itemType);

        /* getter */
        unsigned int getWeight() const { return _weight; }
        unsigned int getCount(Item itemType) const;
        
        /* helper */
        unsigned int calculateWeight() const;
    private:
        std::vector<Item> _items;
        unsigned int _weight;
};

#endif /* BAG_H */
