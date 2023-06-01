#pragma once
#include "../Library/gameutil.h"
#include "Bittermap.h"
#include "../Unity/Vector2.h"
class Cavallo
{
public:
	void load();
	void init(Vector2i startLocation, bool autoAttack = true, bool follow = true, Vector2i* playerPos = nullptr);
	void Throw(Vector2f bombTarget);
	void draw();
	void move(const HitboxPool hitboxPool);
	void setDest(Vector2i target);
	void setPosition(Vector2i position);
	bool isAutoAttack();
private:
	class CherryBomb {
	public:
		void load();
		void init(Vector2i startLocation, Vector2f direction);
		bool draw();
		void move();
	private:
		clock_t _spawnTime;
		clock_t _duration;
		double _speed;
		Vector2f _position;
		Vector2f _direction;
		Vector2f _target;
		game_framework::Bittermap _sprite;
		game_framework::Bittermap _explosionSprite;
	};
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
	vector<CherryBomb> _cherryBomb;
	game_framework::Bittermap _sprite;
	game_framework::Bittermap _sprite_mirror;
};

