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

        template<Item ITEM_T>
        bool use() {
            auto i=std::find(_items.begin(),_items.end(), ITEM_T);
            if(i==_items.end()) return false; // not found
            // found
            _items.erase(i);
            return true;
        }

        /* getter */
        unsigned int getWeight() const { return _weight; }
        
        /* helper */
        unsigned int calculateWeight() const;
    private:
        std::vector<Item> _items;
        unsigned int _weight;
};

#endif /* BAG_H */
