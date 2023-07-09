#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "SfmlLibrary.h"
#include "gameConstants.h"

enum class PlayerRegion { region1, region2, region3, region4, unknown };

class Player
{
public:
	Player();
    void spawnPlayer(vector2f initPosition);
    void virtual handleInput(bool keyPressed) = 0;
    Sprite getSprite() const;
    void update(const float timeElapsed);
    void jump_down(const float& deltaTime, const float start_position);
    void jump_up(const float deltaTime, const float start_position);
    void calibrate();
    void update_bailey_region();
    void setSpeed(const float _Force);
    bool IsplayerMoving();
    bool isRightPressed() const;
    bool isLeftPressed() const;
    bool isPlayerJumping() const;
    bool isFacingRight() const;
    bool isFacingLeft() const;
    void updateSprite(Texture& newTexture);
    bool isPlayerInSafeZone();
    vector2f getPosition() const;
    void setPlayerToMoveWithIce(const Direction& dir, const float deltaTime);
    void playerShouldDrown(const bool should_drown);
    bool isPlayerDrowning() const;
    void set_to_dead();
    bool isReverseBtnPressed() const;
    void resetReverseBtnPress();
    PlayerRegion get_bailey_region() const;
    bool isPlayerKilledByAnimal() const;
    void KilledByAnimal();

protected:
    Sprite player_sprite;
    Texture player_texture;

    //Direction the player is currently moving
    bool rightPressed;
    bool leftPressed;
    bool upPressed;
    bool downPressed;
    bool playerJumping;
    bool reverseBtnPressed;
    bool playerInSafeZone;
 
private:
    vector2f position;
    float gravity;
    float right_boundary;
    float left_boundary;
    float speed;
    float speed_attenuater;
    float distance_between_iceRows;

    //Regions
    PlayerRegion player_region;
    float Region1;
    float Region2;
    float Region3;
    float Region4;
    float safe_zone_boundary;
    float downJumpForce;
    float player_mass;
    float prevRegion;
    bool isJumpingDown;
    bool isJumpingUp;
    float upJumpForce;
    bool playerMoving;
    vector2f prevPosition;
    bool facingRight;
    bool facingLeft;
    float new_speed;
    bool playerDrown;
    bool isDead;
    bool playerKilledByAnimal;
};

#endif // !PLAYER_H

