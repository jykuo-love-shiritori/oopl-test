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
class Cavallo
{
public:
	void load();
	void init(Vector2i startLocation, std::function<void(int)> hurtPlayer, std::function<std::vector<Rock*>(Rect hitbox)> getRocks,  bool autoAttack = true, bool follow = true, Vector2i* playerPos = nullptr );
	void Throw(Vector2f bombTarget);
	void draw();
	void move(const HitboxPool hitboxPool);
	void setDest(Vector2i dest);
	void setAttackTarget(Vector2i target);
	void setPosition(Vector2i position);
	bool isAutoAttack();
private:
	class CherryBomb {
	public:
		void load(std::function<std::vector<Rock*>(Rect hitbox)> getRocks);
		void init(Vector2i startLocation, Vector2f direction);
		bool draw();
		void move();
	private:
		std::function<std::vector<Rock*>(Rect hitbox)> _getRocks;
		clock_t _spawnTime;
		clock_t _duration;
		double _speed;
		Vector2f _position;
		Vector2f _direction;
		Vector2f _target;
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
		void load(GunType type, std::function<void(int)> hurtPlayer, std::function<std::vector<Rock*>(Rect hitbox)> getRocks, Vector2i* playerPos);
		void init(Vector2i* 🐼Pos, Vector2f direction);
		void draw();
		void move();
		void setTarget(Vector2f target);
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

const auto dir2rotation = [](Vector2f v) {
	if (v.x == 0 && v.y == 0)
		return 0;
	return (-(static_cast<int>((atan2(v.y, v.x) * 180 / 3.1415926 + 0.5))) + 360) % 360;
};