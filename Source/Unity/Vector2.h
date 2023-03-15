#pragma once

namespace Unity {
	struct Vector2i
	{
		int x=0, y=0;
		Vector2i() = default;
		Vector2i(int x, int y) : x(x), y(y) {}
	};
}