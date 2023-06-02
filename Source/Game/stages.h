/*
 * mygame.h: 本檔案儲遊戲本身的class的interface
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#pragma once

#include "Map.h"
#include "RockManager.h"
#include "Bug.h"
#include "Bag.h"
#include "Bittermap.h"
#include "./UI/RightTopUI.h"
#include "./UI/UI.h"
#include "./UI/eh.h"
#include "./UI/Toolbar.h"
#include "Bomb.h"
#include "ShopKeeper.h"
#include "Updatable.h"
#include "./UI/X.h"
#include "../Unity/Vector2.h"
#include "../Game/Player.h"

#include "../Config/config.h"

using temp_name::Map;

namespace game_framework {	namespace stage {
	/////////////////////////////////////////////////////////////////////////////
	// Constants
	/////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲開頭畫面物件
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////
	class StartScreen : public CGameState {
	public:
		StartScreen(CGame *g);
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
	protected:
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		CMovingBitmap background;	// Start screen background 
		CMovingBitmap title;		// title logo
		CMovingBitmap LMBtoStart;	// "Press LMB to start" text
	};

	class InLevel : public CGameState {
	public:
		InLevel(CGame *g);
		~InLevel();
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnLButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
		void OnMouseMove(UINT nFlags, CPoint point);	// 處理滑鼠的動作 
		void OnRButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnRButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private: /* helper */
		void InLevel::SetupLevel(Map::Info mapInfo);
	private:
		/* BIG BLACK CANVAS */
		CMovingBitmap BBC;
		bool DEATH = false;
		Player player;
		struct __ps__ {
			float health;
			float energy;
		} playerStatus;

		std::string datapath="resources/MapTextures/mine"; //FIXME: hardcode textures files
		Map map;

		int phase=0;

		int playerAttackTimer=0; // use int for conveniently handle underflow
		Unity::Vector2i attackDirection={1,0};

		RockManager rockManager;
		Bittermap testExit;
		Bug bug;
		Bomb bombAnime;

		BombShop clint;
		FoodShop gus;
		X X;

		int m = 0;
		Bag bag;
		std::vector<Updatable*> skillOrAnime = {
			&bombAnime,
			&X,
		};

		struct {
			RightTopUI rtui;
			EH eh;
			Toolbar tb;
		} uis;
		std::vector<UI*> ouioui = {
			&uis.rtui,
			&uis.eh,
			&uis.tb,
		};
	};

	class GameOver : public CGameState {
	public:
		GameOver(CGame *g);
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		int counter;	// 倒數之計數器
	};
	
}}
