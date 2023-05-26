#ifndef UI_EH_H
#define UI_EH_H

#include "../Bittermap.h"
#include "./UI.h"

class EH : public UI {
    float const  *_health;
    float const  *_energy;
public:
    void Init() override;
    void Show() override;
    void setHealth(float const  *health) {_health = health;}
    void setEnergy(float const  *energy) {_energy = energy;}
    game_framework::Bittermap _frame;
    game_framework::Bittermap _innerBar;
};

#endif /* UI_EH_H */
