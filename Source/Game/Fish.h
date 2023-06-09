#pragma once
#include <time.h>
#include "../Library/gameutil.h"
#include "./Bittermap.h"
#include "../Unity/Vector2.h"

class Fish{
    public:
		enum fishState {
			fishReady,
			fishcolddown,
		};
        /* getter */
		int GetFishState();
		int GetFishColddown();
		bool GetFishSuccess();
		bool isFishKeyDown();
		bool isInFishGame();
		/* setter */
		void SetFishState(int state);
		void SetinFishGame(bool ingame);

        void init();
		void Update();
		void fishOverlay();
		void FishResult();
		void showFish();
		void fishKeyDown(bool ispress);
		void playercontrol();
		void fishMove();
		void fishReset(Vector2i pos);
		void fishgameColddown();

    private:
		int _colddown;
		int _fishstate;
		int _process;
		int _QteTime;
		bool _ispress;
		bool _infishgame;
		bool _fishsuccess;
		game_framework::Bittermap _FishGameFrame;
		game_framework::Bittermap _innerBar;
        game_framework::Bittermap _fish;
		game_framework::Bittermap _greenbar;
};