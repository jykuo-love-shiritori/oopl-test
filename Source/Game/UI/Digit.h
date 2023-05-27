#ifndef DIGIT_H
#define DIGIT_H

#include "./UI.h"
#include "../Bittermap.h"
#include "../Unity/Vector2.h"

class Digit : public UI {
    unsigned const  *_number;
    float _scalar;
public:
    Unity::Vector2i lsb_location;
public:
    Digit(unsigned const  *numptr, float scalar) :
		_scalar(scalar),
		_number(numptr)
	{}
    void Init() override;
    void Show() override;
private:
    static game_framework::Bittermap _n;
};

#endif /* DIGIT_H */
