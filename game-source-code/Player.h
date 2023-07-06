#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "SfmlLibrary.h"
#include "gameConstants.h"

class Player
{
public:
	Player();
    void spawnPlayer(vector2f initPosition);
    void virtual handleInput() = 0;
    Sprite getSprite() const;
    void update(const float timeElapsed);

protected:
    Sprite player_sprite;
    Texture player_texture;

    //Direction the player is currently moving
    bool rightPressed;
    bool leftPressed;
    bool upPressed;
    bool downPressed;
 
private:
    vector2f position;
    float gravity;
    float right_boundary;
};

#endif // !PLAYER_H

