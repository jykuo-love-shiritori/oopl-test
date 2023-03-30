#include "stdafx.h"

#include <cmath>

#include "../Unity/Rect.h"
#include "../Unity/Vector2.h"

using namespace Unity;

Rect Rect::FromTopLeft(Vector2i topLeft, Vector2i widthAndHeight) {
    //FIXME: Verity Data
    Rect rect;
    rect.topLeft = topLeft;
    rect.BottomRight = {
        topLeft.x + widthAndHeight.x,
        topLeft.y + widthAndHeight.y,
    };
    return rect;
}

Rect Rect::FromVertice(Vector2i topLeft, Vector2i bottomRight) {
    //FIXME: Verity Data
    Rect rect;
    rect.topLeft = topLeft;
    rect.BottomRight = bottomRight;
    return rect;
}

Rect Rect::FromCenter(Vector2i center, Vector2i radius) {
    //FIXME: Verity Data
    Rect rect;
    rect.topLeft = center - radius;
    rect.BottomRight = center + radius;
    return rect;
}

Vector2f Rect::getRadius() const {
    return Vector2f(BottomRight-topLeft)/2;
}

Vector2f Rect::getCenter() const {
    return Vector2f(topLeft) + getRadius();
}

Vector2i Rect::getTopLeft() const {
    return topLeft;
}

Vector2i Rect::getBottomRight() const {
    return BottomRight;
}

bool Rect::isOverlay(const Rect &a, const Rect &b) {
    auto centetA = a.getCenter();
    auto centetB = b.getCenter();
    auto radiusA = a.getRadius();
    auto radiusB = b.getRadius();
    
    auto d = centetA - centetB;
    auto r = radiusA + radiusB;

    return abs(d.x) < r.x && abs(d.y) < r.y;
}
