#pragma once
#include <functional>
#include "../Library/gameutil.h"
#include "Bittermap.h"
#include "RockManager.h"
#include "../Unity/Vector2.h"

#define CAVALLO_SPEED			1.0f
#define CHERRY_BOMB_CD			10000
#define CHERRY_BOMB_SPEED		3
#define CHERRY_BOMB_DURATION	5250
#define CHERRY_BOMB_DAMAGE		100
#define SNIPER_ROF				3000
#define SNIPER_DEV				0.1f	
#define SNIPER_BULLET_SPEED		5.0f
#define SNIPER_BULLET_DAMAGE	50
/*
*	usage: load and intialize with corresponding functions
*	Move in OnMove()
*	Draw in OnDraw()
*/ 
class Cavallo
{
public:
	// load dependences
	void load(); 
	// initial with start location, map hitbox pool pointer, hurtPlayer function, getRocks function, autoAttack, follow (player), player position pointer 
	void init(Vector2i startLocation, std::function<void(int)> hurtPlayer, std::function<std::vector<Rock*>(Rect hitbox)> getRocks, HitboxPool* mapHP, bool autoAttack = true, bool follow = true, Vector2i* playerPos = nullptr);
	// throw bomb to target, the cooldown system already implemented in it
	void Throw(Vector2f bombTarget);
	// draw sprites with mirror implemented
	void draw();
	// move with collision
	void move(const HitboxPool hitboxPool);
	// set Cavallo destination
	void setDest(Vector2i dest);
	// set Cavallo attack target (snipe target)
	void setAttackTarget(Vector2i target);
	// set Cavallo position
	void setPosition(Vector2i position);
	// get isAutoAttack
	bool isAutoAttack();
private:
	class CherryBomb {
	public:
		// load dependences and pass map hitbox pool pointer and getRocks function
		void load(std::function<std::vector<Rock*>(Rect hitbox)> getRocks, HitboxPool* mapHP);
		// initial with start location and moving direction
		void init(Vector2i startLocation, Vector2f direction);
		// draw sprite
		bool draw();
		// move along direction
		void move();
	private:
		std::function<std::vector<Rock*>(Rect hitbox)> _getRocks;
		clock_t _spawnTime;
		clock_t _duration;
		double _speed;
		Vector2f _position;
		Vector2f _direction;
		Vector2f _target;
		HitboxPool* _mapHP;
		int _damage;
		game_framework::Bittermap _sprite;
		game_framework::Bittermap _explosionSprite;
	};
	enum class GunType {
		PISTOL,
		SHOTGUN,
		SNIPER_RIFLE
	};
	class Gun {
	public:
		// load dependences and pass start location, map hitbox pool pointer, hurtPlayer function, getRocks function, player position pointer
		void load(GunType type, std::function<void(int)> hurtPlayer, std::function<std::vector<Rock*>(Rect hitbox)> getRocks, HitboxPool* mapHP, Vector2i* playerPos);
		// init with covallo position and aiming direction
		void init(Vector2i* 🐼Pos, Vector2f direction);
		// draw the sprite
		void draw();
		// move sprite to Covallo position
		void move();
		// set shooting target
		void setTarget(Vector2f target);
		// set _target to traget if sarget setted, and shoot to target
		void shoot(Vector2f target = {0.0f, 0.0f});
	protected:
		std::function<void(int)> _hurtPlayer;
		std::function<std::vector<Rock*>(Rect hitbox)> _getRocks;
		class Bullet {
		public:
			void load(const vector<string>& bullletFilename, COLORREF clr, int damage, Vector2i* _target);
			void init(Vector2i startLocation, Vector2f direction);
			bool draw();
			bool move();
			void reduceDuration(int duration);
			Rect getAttackBox();
		private:
			int _damage;
			clock_t _spawnTime;
			clock_t _duration;
			double _speed;
			Vector2f _position;
			Vector2f _direction;
			Vector2i* _target;
			game_framework::Bittermap _sprite;
		};
		int _damage;
		double _speed;
		double _rof; // rate of fire
		double _dev; // deviation
		clock_t _lastShootTime;
		Bullet _baseBullet;
		vector<Bullet> _bullets;
		Vector2i* _🐼Pos;
		Vector2f _position;
		Vector2f _direction;
		Vector2f _target;
		HitboxPool* _mapHP;
		game_framework::Bittermap _sprite;
	};
	class SniperRifle : public Gun {};
	double _speed;
	bool _autoAttack;
	bool _follow;
	clock_t _cooldown;
	clock_t _lastAttack;
	Vector2f _direction;
	Vector2f _dest;
	Vector2f _bombTarget;
	Vector2f _smoothMoving;
	Vector2i* _playerPos;
	CherryBomb _baseCherryBomb;
	SniperRifle _sniperRifle;
	vector<CherryBomb> _cherryBomb;
	Gun _baseGun;
	game_framework::Bittermap _sprite;
	game_framework::Bittermap _sprite_mirror;
};
// get rotation angle from moving / aiming direction
const auto dir2rotation = [](Vector2f v) {
	if (v.x == 0 && v.y == 0)
		return 0;
	return (-(static_cast<int>((atan2(v.y, v.x) * 180 / 3.1415926 + 0.5))) + 360) % 360;
};