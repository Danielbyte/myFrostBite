#ifndef ENEMY_H
#define ENEMY_H

#include "fish.h"
#include "bird.h"
#include "crab.h"
#include "clamp.h"

class Enemy : public Fish, public Bird, public Crab, public Clamp
{
public:
	Enemy();

private:
};
#endif
