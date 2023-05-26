#include "stdafx.h"

#include "Bag.h"
#include "Item.h"

bool Bag::use(Item itemType) {
    auto i=std::find(_items.begin(),_items.end(), itemType);
    if(i==_items.end()) return false; // not found
    // found
    _items.erase(i);
    return true;
}

unsigned int Bag::calculateWeight() const {
    /*TODO: Fake function */
    return 0;
}

std::vector<Rock> Bag::popMinerals() {
    /*TODO: Fake function */
    /* pop things */
    calculateWeight();
    return {};
}

void Bag::append(Item item) {
    _items.push_back(item);
    calculateWeight();
}