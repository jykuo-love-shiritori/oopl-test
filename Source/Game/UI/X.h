#ifndef X_H
#define X_H

#include "../Bittermap.h"
#include "../Updatable.h"

#include <queue>

class X : public Updatable {
    std::vector<int> _timerQueue;
    game_framework::Bittermap _sprite;
public:
    void Init() {
        _sprite.LoadBitmapByString({"Resources/x.bmp"}, RGB(31,31,31));
    }
    void Play();
    void Update() override;
    void Show();
};

#endif /* X_H */