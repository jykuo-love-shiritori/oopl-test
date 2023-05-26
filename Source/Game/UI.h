#pragma once

#include "../Library/gameutil.h"
#include "./Bittermap.h"

#include "./UI/eh.h"
#include "./UI/Digit.h"

class UI{
    public:
        EH eh;
    public:
        void load();
        void showUI();

        /*getter*/
        int getScore() const { return _score; }

        /*setter*/
        void alterScore(int delta);
        void setScore(int score) { _score = score; }
    private:
        game_framework::Bittermap _UIsprite;
        unsigned int _score = 0;
        Digit _moneyNumbers = Digit(&_score, 1.5);
};