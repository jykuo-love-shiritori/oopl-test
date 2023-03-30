#ifndef HITBOX_H
#define HITBOX_H

#include <string>
#include <vector>
#include <memory>

#include "../Unity/Rect.h"

using namespace std;

namespace Unity
{
   class HitboxPool {
        vector<Rect> vec;
      public:
        vector<Rect> Collide(const Rect& subject) const;
        void AddHitbox(const Rect& hitbox);
    };
} /* namespace Unity */

#endif /* HITBOX_H */