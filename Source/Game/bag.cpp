#include "stdafx.h"

#include "Bag.h"
#include "Item.h"

void Bag::reset(){
    _items.clear();
    _money=0;
}

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

bool Bag::trade(Item item, unsigned int price) {
    const bool canBuy = _money >= price;
    //const bool isOverweight = calculateWeight() //TODO: bag Overweight
    if (!canBuy) return false;
    _money -= price;
    _items.push_back(item);
    return true;
}

unsigned int Bag::getCount(Item itemType) const {
    return std::count(_items.begin(),_items.end(), itemType);
}
