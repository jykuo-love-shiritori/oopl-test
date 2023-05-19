#ifndef BAG_H
#define BAG_H

#include <vector>

#include "RockManager.h"
#include "./Bittermap.h"
#include "Item.h"

class Bag {
    public:
        std::vector<Rock> popMinerals();
        void append(Item item);

        bool useBomb();
        bool useFood();

        /* getter */
        unsigned int getWeight() const { return _weight; }
        
        /* helper */
        unsigned int calculateWeight() const;
    private:
        std::vector<Item> _items;
        unsigned int _weight;
};

#endif /* BAG_H */
