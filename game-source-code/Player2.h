#pragma once
#ifndef PLAYER2_H
#define PLAYER2_H

#include "Player.h"

class Player2 : public Player
{
public:
	Player2();
	void virtual handleInput(bool keyPressed);
};

#endif // !PLAYER2_H

