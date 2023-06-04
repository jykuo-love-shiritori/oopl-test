#include "stdafx.h"
#include "X.h"

#include <queue>
#include "../../Config/config.h"

void X::Play() {
	_timerQueue.push_back(10);
}


void X::Update() {
    std::vector<int> newQueue;
    for(auto t : _timerQueue) {
        if(t <= 0) continue;
        t--;
        newQueue.push_back(t);
    }
    _timerQueue = newQueue;
}

void X::Show() {
    for(auto _timer : _timerQueue) {
        _sprite.SetCenter(
                SIZE_X/2,
                SIZE_Y/2 + _timer*3
            );
        _sprite.Show();
    }
}
