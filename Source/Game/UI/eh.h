#ifndef UI_EH_H
#define UI_EH_H

#include "../Bittermap.h"

class EH {
    float const  *_health;
    float const  *_energy;
public:
    void Init();
    void Show();
    void setHealth(float const  *health) {_health = health;}
    void setEnergy(float const  *energy) {_energy = energy;}
private:
    game_framework::Bittermap _frame;
    game_framework::Bittermap _innerBar;
};

#endif /* UI_EH_H */
