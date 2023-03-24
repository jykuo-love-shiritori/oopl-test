#ifndef BOX_H
#define BOX_H

#include "../Unity/Vector2.h"

namespace Unity
{
    class Rect {
      private:
        Vector2i topLeft, BottomRight;
      public:
        Rect() = default;
        static Rect FromTopLeft(Vector2i topLeft, Vector2i widthAndHeight);
        static Rect FromCenter(Vector2i center, Vector2i radius);
        static Rect FromVertice(Vector2i topLeft, Vector2i bottomRight);
        Vector2i getTopLeft() const;
        Vector2i getBottomRight() const;
        Vector2i getCenter() const;
        Vector2i getLength() const;
        Vector2i getRadius() const;
        static bool isOverlay(Rect &a, Rect &b);
    };
} // namespace Unity

#endif /* BOX_H */