#ifndef UI_EH_H
#define UI_EH_H

#include "../Bittermap.h"

class EH {
    int const  *_health;
    int const  *_energy;
public:
    void Init();
    void Show();
    void setHealth(int const  *health) {_health = health;}
    void setEnergy(int const  *energy) {_energy = energy;}
    game_framework::Bittermap _frame;
    game_framework::Bittermap _innerBar;
};

#endif /* UI_EH_H */
