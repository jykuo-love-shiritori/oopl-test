#include "gtest/gtest.h"

#include "../Source/Unity/Rect.h"

using Unity::Rect;

TEST(UnityRectangleTest, Getters) {
    Rect r = Rect::FromVertice({1,4}, {3, 8});
    ASSERT_EQ(r.getCenter(), Unity::Vector2i(2, 6));
    ASSERT_EQ(r.getRadius(), Unity::Vector2i(1, 2));
}

TEST(UnityRectangleTest, Overlay) {
    Rect r1 = Rect::FromTopLeft({0,0}, {2, 2});
    Rect r2 = Rect::FromTopLeft({1,1}, {2, 2});
    Rect r3 = Rect::FromTopLeft({2,2}, {2, 2});

    ASSERT_TRUE(Rect::isOverlay(r1, r2));
    ASSERT_TRUE(Rect::isOverlay(r2, r3));
    ASSERT_TRUE(Rect::isOverlay(r2, r2));
    ASSERT_FALSE(Rect::isOverlay(r1, r3));
}

TEST(UnityRectangleTest, Overlay2) {
    auto subject = Rect::FromTopLeft({1,2}, {3,4});

    EXPECT_EQ(subject.getTopLeft(), Unity::Vector2i(1,2));
    EXPECT_EQ(subject.getBottomRight(), Unity::Vector2i(4,6));


    auto box = Rect::FromTopLeft({5,2}, {3,4});
    EXPECT_FALSE(Rect::isOverlay(subject, box));


    auto box2 = (Rect::FromTopLeft({0,0}, {3,3}));

    EXPECT_EQ(box2.getTopLeft(), Unity::Vector2i(0,0));
    EXPECT_EQ(box2.getBottomRight(), Unity::Vector2i(3,3));

    EXPECT_TRUE(Rect::isOverlay(subject, box2));
}