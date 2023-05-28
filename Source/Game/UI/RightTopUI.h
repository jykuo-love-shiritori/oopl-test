#pragma once

#include "../Bittermap.h"

#include "../UI/UI.h"
#include "../UI/Digit.h"

class RightTopUI : public UI {
    public:
        void Init() override;
        void Show() override;

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