#include "stdafx.h"

#include <algorithm>

#include "Bag.h"
#include "Item.h"

bool Bag::useBomb() {
    auto i=std::find(_items.begin(),_items.end(),Item::Bomb);
    if(i==_items.end()){
        return false;
    }
    else{
        _items.erase(i);
        return true;
    }
}

bool Bag::useFood() {
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