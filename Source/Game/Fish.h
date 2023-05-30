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
			fishcolddown,
		};
        /* getter */
		int GetFishState();
		int GetFIshColddown();
		/* setter */
		void SetFishState(int state);

        void init();
		void Update();
		void fishOverlay();
		void fishSuccess();
		void showFish();
		void fishMove();
		void fishKeyDown(bool ispress);
		void playercontrol();
		void fishReset();
		void fishgameColddown();

    private:
		int _colddown;
		int _fishstate,_fishposition;
		int _process;
        int _randomMove;
		int _presstime,_unpresstime;
		int _fishprogress;
		int _fishMove;
		int _greenbarMove;
		bool _fishDone;
		bool _ispress;
		game_framework::Bittermap _FishGameFrame;
		game_framework::Bittermap _innerBar;
        game_framework::Bittermap _fish;
		game_framework::Bittermap _greenbar;
};