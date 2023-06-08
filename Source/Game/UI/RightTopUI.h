#pragma once

#include "../Bittermap.h"

#include "../UI/UI.h"
#include "../UI/Digit.h"

class RightTopUI : public UI {
    public:
        void Init() override;
        void Show() override;

        /* setter */
        void setMoneyPtr(unsigned const  *money) { _moneyNumbers.setNumptr(money); }
    private:
        game_framework::Bittermap _UIsprite;
        Digit _moneyNumbers = Digit(NULL, 1.5);
};