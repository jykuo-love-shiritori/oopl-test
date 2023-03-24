#include "stdafx.h"
#include "../Unity/Vector2.h"

using namespace Unity;

Vector2i Vector2i::operator+(const Vector2i& other) const {
    return {
        this->x + other.x,
        this->y + other.y,
    };
}