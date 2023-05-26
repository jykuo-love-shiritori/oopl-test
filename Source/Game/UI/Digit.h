#ifndef DIGIT_H
#define DIGIT_H

#include "../Bittermap.h"

class Digit {
    unsigned const  *_number;
    float _scalar;
public:
    Digit(unsigned const  *numptr, float scalar) :
		_scalar(scalar),
		_number(numptr)
	{}
    void Init();
    void Show();
private:
    static game_framework::Bittermap _n;
};

#endif /* DIGIT_H */
