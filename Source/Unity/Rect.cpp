#include "Vector2.h"
#ifndef STOP_YELLING
#include "stdafx.h"
#endif

#include <cmath>

#include "../Unity/Rect.h"

using namespace Unity;

Rect Rect::FromTopLeft(Vector2i topLeft, Vector2i widthAndHeight) {
    Rect rect;
    rect.topLeft = topLeft;
    rect.BottomRight = {
        topLeft.x + widthAndHeight.x,
        topLeft.y + widthAndHeight.y,
    };
    return rect;
}

Rect Rect::FromVertice(Vector2i topLeft, Vector2i bottomRight) {
    Rect rect;
    rect.topLeft = topLeft;
    rect.BottomRight = bottomRight;
    return rect;
}

Rect Rect::FromCenter(Vector2i center, Vector2i radius) {
    Rect rect;
    rect.topLeft = center - radius;
    rect.BottomRight = center + radius;
    return rect;
}

Vector2i Rect::getRadius() const {
    return (BottomRight-topLeft)/2; 
}

Vector2i Rect::getCenter() const {
    return topLeft + getRadius();
}

bool Rect::isOverlay(Rect &a, Rect &b) {
    auto centetA = a.getCenter();
    auto centetB = b.getCenter();
    auto radiusA = (a.BottomRight-a.topLeft)/2;
    auto radiusB = (b.BottomRight-b.topLeft)/2;
    
    auto d = centetA - centetB;
    auto r = radiusA + radiusB;

    return abs(d.x) < r.x || abs(d.y) < r.y;
}
