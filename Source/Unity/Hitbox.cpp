#include "stdafx.h"
#include "Hitbox.h"
#include "Rect.h"

#include <cmath>
#include <algorithm>

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
    struct
    {
        Rect subject = subject;
        bool operator()(Rect a, Rect b) const {
            auto ca = a.getCenter();
			auto cb = b.getCenter();
			auto cs = subject.getCenter();
            auto da = pow(ca.x - cs.x, 2) + pow(ca.y - cs.y, 2);
            auto db = pow(cb.x - cs.x, 2) + pow(cb.y - cs.y, 2);
            return da < db;
        }
    } euclideanDistance;
	std::sort(result.begin(), result.end(), euclideanDistance);
    return result;
}

void HitboxPool::AddHitbox(const Rect& hitbox) {
    this->vec.push_back(hitbox);
}

HitboxPool HitboxPool::operator+(const HitboxPool& other) const {
    HitboxPool newpool = HitboxPool();
    vector<Rect> v;
    v.insert(v.end(), this->vec.begin(), this->vec.end());
    v.insert(v.end(), other.vec.begin(), other.vec.end());
    newpool.vec = v;
    return newpool;
}