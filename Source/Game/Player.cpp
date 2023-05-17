#include "../Game/Player.h"

void Player::Init() {
    const Vector2i regularBoxSize = Vector2i(1, 1) * TILE_SIZE * SCALE_SIZE;
    
    _sprite_player.LoadBitmapByString({
        "resources/giraffe.bmp",
        "resources/giraffe-hit.bmp",
    }, RGB(255, 255, 255));
    _sprite_player.SetScale(1);
    _sprite_player.SetHitBox(regularBoxSize * 0.7);

    _sprite_attack.LoadBitmapByString({
        "resources/slashLeft.bmp",
        "resources/slashDown.bmp",
        "resources/slashRight.bmp",
        "resources/slashUp.bmp"
    }, RGB(25, 28, 36));
    _sprite_attack.SetScale(1);
    _sprite_attack.SetHitBox(regularBoxSize * 1.0);
}

void Player::Draw() {
    _sprite_player.Draw();
    _sprite_attack.Draw();
}

/* helper BEGIN */
unsigned int getFrameIndexOfBitmapBy(Vector2i attackDirection) {
	if(attackDirection==Vector2i(0,1)){
		return 1; // Down
	}
	if(attackDirection==Vector2i(0,-1)){
		return 3; // Up
	}
	if(attackDirection.x == -1){
		return 2; // Left
	}
	if(attackDirection.x == 1){
		return 0; // Right
	}
	throw "wtf";
}
/* helper END */

void Player::attack() {
    _attackTimer = PLAYER_ATTACK_TIME + PLAYER_ATTACK_CD;
}

void Player::Update() {
    { // attack timer BEGIN
        if(_attackTimer > 0) {
            _attackTimer--;
            _sprite_attack.SetShow(_attackTimer > PLAYER_ATTACK_CD);
        }
        _sprite_attack.position = _sprite_player.position + _attackDirection * TILE_SIZE * SCALE_SIZE;
        _sprite_attack.SetFrameIndexOfBitmap(
            getFrameIndexOfBitmapBy(_attackDirection)
        );
    } // attack timer END
}
