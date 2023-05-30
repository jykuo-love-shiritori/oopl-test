#pragma once
#include <time.h>
#include "../Library/gameutil.h"

#include "./Bittermap.h"
#include "../Unity/Vector2.h"

class Fish{
    public:
		enum fishState {
			infish,
			fishsuccess,
			fishfail,
		};
        /* getter */
		int GetFishState();
		/* setter */
		void SetFishState(int state);

        void init();
        void useFishing(Vector2i playerLocation,int type);
		void Update();
		void fishOverlay();
		void fishSuccess();
		void showFish();
		void fishMove();
		void fishKeyDown(bool ispress);
		void playercontrol();
		void fishReset();
    private:
		int _fishstate,_fishposition;
		int _process;
        int _randomMove;
		int _presstime,_unpresstime;
		int _fishprogress;
		bool _fishDone;
		bool _ispress;
		Vector2f _fishMove;
		Vector2f _greenbarMove;
		game_framework::Bittermap _FishGameFrame;
		game_framework::Bittermap _innerBar;
        game_framework::Bittermap _fish;
		game_framework::Bittermap _greenbar;
};