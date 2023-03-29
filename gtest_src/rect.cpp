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