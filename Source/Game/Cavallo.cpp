#include "stdafx.h"
#include "Cavallo.h"
#include "../Config/config.h"
#include "../Config/scaler.h"
void Cavallo::load() {
    auto BaseFilename = "Resources/Cavallo/Cavallo_0";
    vector<string> filenames;
    vector<string> mirror_filenames;
    for (int i = 0; i < 4; i++) {
		filenames.emplace_back(BaseFilename + to_string(i + 1) + ".bmp");
        mirror_filenames.emplace_back(BaseFilename + to_string(i + 1) + "_m.bmp");
	}
	_sprite.LoadBitmapByString(filenames, RGB(1, 11, 111));
	_sprite_mirror.LoadBitmapByString(mirror_filenames, RGB(1, 11, 111));
    _sprite.SetAnimation(100, 0);
    _sprite_mirror.SetAnimation(100, 0);
    _baseCherryBomb.load();
    _cooldown = 1200;
    _speed = 1.5;
    _direction = { 0, 0 };
    _smoothMoving = { 0.0f, 0.0f };
}
void Cavallo::init(Vector2i startLocation, bool autoAttack, bool followPlayer, Vector2i* playerPos) {
	_sprite.position = startLocation;
	_sprite_mirror.position = startLocation;
    _autoAttack = autoAttack;
    _follow = followPlayer;
    _playerPos = playerPos;
    _lastAttack = clock();
}
void Cavallo::setPosition(Vector2i position) { 
    _sprite.position = position;
    _sprite_mirror.position = position;
}
void Cavallo::Throw(Vector2f bombTarget) {
    _bombTarget = bombTarget;
	_cherryBomb.push_back(_baseCherryBomb);
	_cherryBomb.back().init(_sprite.position, Vector2f(bombTarget - _sprite.position).normalized()*2.0f);
}
void Cavallo::draw() {
    if (_dest.x - _sprite.position.x < 0.0f) {
		_sprite_mirror.Draw();
	}
    else {
		_sprite.Draw();
	}
    for (auto it = _cherryBomb.begin(); it != _cherryBomb.end(); ) {
        if (!it->draw()) {
			it = _cherryBomb.erase(it);
		}
        else {
			it++;
		}
    }
}
void Cavallo::move(const HitboxPool hitboxPool) {
    if (_follow){
	    _direction = Vector2f(*_playerPos - _sprite.position).normalized() * 2;
        _dest = *_playerPos;
    }
    if ((_sprite.GetHitbox().getCenter() - _dest).norm() < 40)
    {
		_direction = { 0, 0 };
	}
    
    auto dis = _direction * _speed;
    auto disint = Vector2i(dis.x, dis.y);
    _smoothMoving = _smoothMoving + (dis - disint);
    if (fabs(_smoothMoving.x) > 1.0f) {
        disint.x  += static_cast<int>(_smoothMoving.x);
        _smoothMoving.x -= static_cast<int>(_smoothMoving.x);
    }
    if (fabs(_smoothMoving.y) > 1.0f) {
		disint.y += static_cast<int>(_smoothMoving.y);
        _smoothMoving.y -= static_cast<int>(_smoothMoving.y);
	}
	_sprite_mirror.MoveWithCollision(_direction * _speed, hitboxPool);
	_sprite.MoveWithCollision(_direction * _speed, hitboxPool);
    if (_autoAttack && clock() - _lastAttack > _cooldown) {
        Throw(*_playerPos);
        _lastAttack = clock();
    }
    for (auto& cherryBomb : _cherryBomb) {
		cherryBomb.move();
	}
}
void Cavallo::setDest(Vector2i dest) {
    _dest = dest;
    _direction = Vector2f(_dest - _sprite.position).normalized() * 2.0;
}
bool Cavallo::isAutoAttack() {
    return _autoAttack;
}
void Cavallo::CherryBomb::load() {
	auto BaseFilename = "Resources/Cavallo/CherryBomb/Cherry_r";
    auto ExplosionFilename = "Resources/Cavallo/CherryBomb/Burst";
    vector<string> filenames;
    vector<string> explosionFilenames;
    for (int i = 0; i < 360; i += 10) {
        filenames.emplace_back(BaseFilename + to_string(i) + ".bmp");
    }
    for (int i = 1; i <= 5; i++) {
		explosionFilenames.emplace_back(ExplosionFilename + to_string(i) + ".bmp");
	}
    _sprite.LoadBitmapByString(filenames, RGB(1, 11, 111));
    _sprite.SetAnimation(30, 0);
    _explosionSprite.LoadBitmapByString(explosionFilenames, RGB(1, 11, 111));
    _explosionSprite.SetAnimation(100, 1);
    _speed = 3;
    _duration = 1250; // ms
}
void Cavallo::CherryBomb::init(Vector2i startLocation, Vector2f direction) {
    _sprite.position = startLocation;
    _direction = direction;
    _spawnTime = clock();
}
bool Cavallo::CherryBomb::draw() {
	_sprite.Draw();
    if (clock() - _spawnTime > _duration) {
        _explosionSprite.position = _sprite.position;
        _sprite = _explosionSprite;
        _sprite.ToggleAnimation();
        _duration = 99999;
    }
    if (_sprite.IsAnimationDone())
        return false;
    return true;
}
void Cavallo::CherryBomb::move() {
	_sprite.Move(_direction * _speed);
}