#pragma once

namespace Unity {
	class Vector2i
	{
	public:
		int x=0, y=0;
		Vector2i() = default;
		Vector2i(int x, int y) : x(x), y(y) {}
	};
}