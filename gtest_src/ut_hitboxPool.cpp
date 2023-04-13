#include <gtest/gtest.h>

#include "../Source/Unity/Hitbox.h"

using namespace Unity;

TEST(HitboxTest, a) {
    auto subject = Rect::FromTopLeft({1,2}, {3,4});

    HitboxPool hp = HitboxPool();
    ASSERT_EQ(hp.Collide(subject).size(), 0);

    hp.AddHitbox(Rect::FromTopLeft({5,2}, {3,4}));
    ASSERT_EQ(hp.Collide(subject).size(), 0);

    hp.AddHitbox(Rect::FromTopLeft({1,7}, {3,4}));
    ASSERT_EQ(hp.Collide(subject).size(), 0);

    hp.AddHitbox(Rect::FromTopLeft({0,0}, {3,3}));
    auto result = hp.Collide(subject);
    ASSERT_EQ(result.size(), 1);
    //ASSERT_EQ(result[0], a);
}