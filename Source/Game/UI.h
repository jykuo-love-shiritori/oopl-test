#pragma once

#include "../Library/gameutil.h"
#include "./Bittermap.h"

class UI{
    public:
        void load();
        void showUI();

        /*getter*/
        int getScore() const { return _score; }

        /*setter*/
        void alterScore(int delta);
        void setScore(int score) { _score = score; }
        void setHealth(long int* health) {_health = health;}
    private:
        long int *_health;
        game_framework::Bittermap _UIsprite;
        game_framework::Bittermap _moneyNumbers;
        game_framework::Bittermap _ehBar;
        game_framework::Bittermap _innerBar;
        unsigned int _score = 0;
};