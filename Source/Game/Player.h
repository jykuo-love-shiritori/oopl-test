#ifndef PLAYER_H
#define PLAYER_H

#include "../Game/Bittermap.h"

#include "../Config/scaler.h"

#define PLAYER_ATTACK_CD	15
#define PLAYER_ATTACK_TIME	5

using Unity::Vector2i;

class Player {
public:
    void Init();
    void Update();
    void Draw();

    /* Getter */
    Rect getHitBox() const { return _sprite_player.GetHitbox(); }
    Rect getAttackBox() const { return _sprite_attack.GetHitbox(); }
    bool isAttacking() const { return _sprite_attack.isShown(); }
    bool canAttack() const { return _attackTimer <= 0; }

    /* Method */
    // reset the attack timer to attacking state
    void attack();
    void Move(Vector2i moveVec);
	void MoveWithCollision(Vector2i moveVec, HitboxPool hitboxPool);

private:
    int _attackTimer = 0;
    Vector2i _attackDirection;
public:
    int health; //FIXME: why no use :pinched_fingers:
    Vector2i& position = _sprite_player.position;
    game_framework::Bittermap _sprite_player;
    game_framework::Bittermap _sprite_attack;
};

#endif /* PLAYER_H */
