#pragma once
#ifndef PLAYER1_H
#define PLAYER1_H

#include "Player.h"

class Player1 : public Player
{
public:
	Player1();
	void virtual handleInput(bool keyPressed);
};

#endif // !PLAYER1_H

