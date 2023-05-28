#include "stdafx.h"
#include "X.h"

#include "../../Config/config.h"

void X::Update() {
    this->SetShow(_timer>0);
    if (_timer>0) {
        _timer--;
        this->SetCenter(
            SIZE_X/2,
            SIZE_Y/2 + _timer*2
        );
    }
}