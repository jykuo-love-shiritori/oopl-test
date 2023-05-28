#ifndef X_H
#define X_H

#include "Bittermap.h"
#include "Updatable.h"

class X : public Updatable, public game_framework::Bittermap {
    int _timer = -1;
public:
    void Play() { _timer = 10; }
    void Update() override;
};

#endif /* X_H */