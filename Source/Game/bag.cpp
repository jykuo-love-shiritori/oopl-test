#include "stdafx.h"

#include "Bag.h"
#include "Item.h"

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