#include "Hitbox.h"
#include "Rect.h"
#include "stdafx.h"

using Unity::HitboxPool;
using Unity::Rect;

vector<Rect> HitboxPool::Collide(const Rect& subject) const {
    vector<Rect> result;
    for(const auto &box: this->vec) {
        if(Rect::isOverlay(subject, box)) {
            auto a = box;
            result.push_back(box);
        }
    }
    return result;
}

void HitboxPool::AddHitbox(const Rect& hitbox) {
    this->vec.push_back(hitbox);
}