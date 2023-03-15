#pragma once

#include "../Library/gameutil.h"
#include "../Unity/Vector2.h"

using namespace Unity;

namespace game_framework {
	class NPOjbect : public CMovingBitmap { // Non-Player Ojbect
	public:
		static Vector2i *CameraPosition;
		Vector2i positsion;
		void DrawInCamera(); // ShowBitmap by camera position
		void Move(Vector2i vec);
	};

	Vector2i *NPOjbect::CameraPosition;
}
