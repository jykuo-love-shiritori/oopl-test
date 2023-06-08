#include "stdafx.h"
#include "Cavallo.h"
#include "Map.h"
#include <functional>
#include <random>
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
    _sprite.SetHitBox({_sprite.GetWidth(), _sprite.GetHeight()});
    _sprite_mirror.SetHitBox({_sprite_mirror.GetWidth(), _sprite_mirror.GetHeight()});
    _cooldown = CHERRY_BOMB_CD;
    _speed = CAVALLO_SPEED;
    _direction = { 0, 0 };
    _smoothMoving = { 0.0f, 0.0f };
}
void Cavallo::init(Vector2i startLocation, std::function<void(int)> hurtPlayer, std::function<std::vector<Rock*>(Rect hitbox)> getRocks, bool autoAttack, bool followPlayer, Vector2i* playerPos) {
	_sprite.position = startLocation;
	_sprite_mirror.position = startLocation;
    _autoAttack = autoAttack;
    _follow = followPlayer;
    _playerPos = playerPos;
    _lastAttack = clock();
    _baseCherryBomb.load(getRocks);
    _sniperRifle.load(GunType::SNIPER_RIFLE, hurtPlayer, getRocks, playerPos);
    _sniperRifle.init(&_sprite.position, Vector2f(1.0f, 0.0f));
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
    _sniperRifle.draw();
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
   
    _sniperRifle.move();
    if (_autoAttack) {
        setAttackTarget(*_playerPos);
        _sniperRifle.shoot(*_playerPos);
    }
    if (_autoAttack && clock() - _lastAttack > _cooldown) {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_real_distribution<float> dis(-1000, 1000);
        Throw({dis(gen), dis(gen)});  // yes CherryBomb :)
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
void Cavallo::setAttackTarget(Vector2i target) {
    _sniperRifle.setTarget(target);
}
bool Cavallo::isAutoAttack() {
    return _autoAttack;
}
void Cavallo::CherryBomb::load(std::function<std::vector<Rock*>(Rect hitbox)> getRocks) {
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
    _sprite.SetHitBox({ _sprite.GetWidth(), _sprite.GetHeight() });
    _explosionSprite.LoadBitmapByString(explosionFilenames, RGB(1, 11, 111));
    _explosionSprite.SetAnimation(100, 1);
    _getRocks = getRocks;
    _speed = CHERRY_BOMB_SPEED;
    _damage = CHERRY_BOMB_DAMAGE;
    _duration = CHERRY_BOMB_DURATION;
}
void Cavallo::CherryBomb::init(Vector2i startLocation, Vector2f direction) {
    _sprite.position = startLocation;
    _direction = direction;
    _spawnTime = clock();
}
bool Cavallo::CherryBomb::draw() {
	_sprite.Draw();
    if (_duration != -1 && clock() - _spawnTime > _duration) {
        _explosionSprite.position = _sprite.position;
        _sprite = _explosionSprite;
        _sprite.ToggleAnimation();
        _duration = -1;
        _speed = 0.6f;
    }
    if (_sprite.IsAnimationDone())
        return false;
    return true;
}
void Cavallo::CherryBomb::move() {
	_sprite.Move(_direction * _speed);
    const vector<Rock*> rocks = _getRocks(_sprite.GetHitbox());
    if (rocks.size() > 0 && _duration != -1) {
        _duration = 0;
    }
    for (auto rock : rocks) {
        rock->health -= _damage * 10000;
	}
	
}
void Cavallo::Gun::load(GunType type, std::function<void(int)> hurtPlayer, std::function<std::vector<Rock*>(Rect hitbox)> getRocks, Vector2i* playerPos) {
    string BaseFilename = "Resources/Cavallo/Gun/";
    string BaseBulletFilename = "Resources/Cavallo/Gun/";
    switch (type) {
        case GunType::SNIPER_RIFLE:
            BaseFilename += "sniper_rifle/sniper_rifle_r";
            BaseBulletFilename += "sniper_rifle/bullet/sniper_bullet_r";
			_rof = SNIPER_ROF;
			_damage = SNIPER_BULLET_DAMAGE;
            _dev = SNIPER_DEV;
            _speed = SNIPER_BULLET_SPEED;
			break;
        // NOT IMPLEMENTED
		case GunType::SHOTGUN:
        case GunType::PISTOL:
        throw "Not implemented";
    }
	vector<string> filenames;
    vector<string> bulletFilenames;
    for (int i = 0; i < 360; i += 10) {
		filenames.emplace_back(BaseFilename + to_string(i) + ".bmp");
        bulletFilenames.emplace_back(BaseBulletFilename + to_string(i) + ".bmp");
	}
    _sprite.LoadBitmapByString(filenames, RGB(255, 255, 255));
	_baseBullet.load(bulletFilenames, RGB(1, 11, 111), _damage, playerPos);
    _hurtPlayer = hurtPlayer;
    _getRocks = getRocks;
}
void Cavallo::Gun::init(Vector2i* 🐼Pos, Vector2f direction) {
    _🐼Pos = 🐼Pos;
    _position = *(_🐼Pos);
    _direction = direction;
    _sprite.position = _position;
    int rot = dir2rotation(direction);
    _sprite.SetFrameIndexOfBitmap(static_cast<int>(((rot + 5) % 360) / 10));
}
void Cavallo::Gun::draw() {
	_sprite.Draw();
    for (auto it = _bullets.begin(); it != _bullets.end();) {
        if (!it->draw()) {
			it = _bullets.erase(it);
		}
        else {
			it++;
		}
	}
}
void Cavallo::Gun::move() {
    _direction = Vector2f(_target - _sprite.position).normalized() * 2;
	_position = *_🐼Pos;
	_sprite.position = _position;
	_sprite.SetFrameIndexOfBitmap(static_cast<int>(((dir2rotation(Vector2f(_target - _sprite.position)) + 5) % 360) / 10));
    int damageAll = 0;
    for (auto& bullet : _bullets) {
        if (bullet.move()) {
			damageAll += _damage;
		}
        auto 🚀 = bullet.getAttackBox();
        // Enumerate all the rocks that collide with the attack area
        const vector<Rock*> 🗿🗿🗿 = _getRocks(🚀);
        if (🗿🗿🗿.size() != 0)
            bullet.reduceDuration(4000); // can pass 3 rocks
        for (auto 🗿 : 🗿🗿🗿) {
			🗿->health -= _damage * 10000;
		}
	}
    _hurtPlayer(damageAll);
}
void Cavallo::Gun::setTarget(Vector2f target) {
	_target = target;
}
void Cavallo::Gun::shoot(Vector2f target) {
    if (clock() - _lastShootTime < _rof)
		return;
    if (target != Vector2f{ 0.0f, 0.0f }) {
        _target = target;
    }
    _lastShootTime = clock();
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<> dis(-_dev, _dev);
	_baseBullet.init(_sprite.position, Vector2f(target - _sprite.position).normalized() + Vector2f(dis(gen), dis(gen)));
	_bullets.push_back(_baseBullet);
}
void Cavallo::Gun::Bullet::load(const vector<string>& bullletFilename, COLORREF clr, int damage, Vector2i* target) {
    _sprite.LoadBitmapByString(bullletFilename, clr);
    _sprite.SetHitBox({ _sprite.GetWidth(), _sprite.GetHeight() });
    _damage = damage;
    _duration = 10000; // infinite
    _target = target;
}
void Cavallo::Gun::Bullet::init(Vector2i position, Vector2f direction) {
	_sprite.position = position;
	_direction = direction;
    _sprite.SetFrameIndexOfBitmap(static_cast<int>(((dir2rotation(direction) + 5) % 360) / 10));
    _spawnTime = clock();
    _speed = 30;
}
bool Cavallo::Gun::Bullet::draw() {
    if (clock() - _spawnTime > _duration) {
		return false;
	}
	_sprite.Draw();
    return true;
}
bool Cavallo::Gun::Bullet::move() {
	_sprite.Move(_direction * _speed);
    if ((_sprite.position - *_target).norm() < 30) {
        _duration = 0;
        return true;
    }
    return false;
}
void Cavallo::Gun::Bullet::reduceDuration(int duration) {
	_duration -= duration;
}
Rect Cavallo::Gun::Bullet::getAttackBox() {
	return _sprite.GetHitbox();
}