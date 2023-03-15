#pragma once

#include "../Unity/Vector2.h"

namespace game_framework {
    struct Rectangle {
        int x,y,width,height;
    };

	class Hitbox {
        Rectangle rect;
	public:
        Hitbox(int x, int y, int width, int height);
        Unity::Vector2i GetCenter();
		bool isHit(Hitbox &other);
	};
}
