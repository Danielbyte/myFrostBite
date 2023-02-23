#ifndef ENEMY_H
#define ENEMY_H

#include "fish.h"
#include "bird.h"
#include "crab.h"
#include "clamp.h"
#include "stopwatch.h"
#include "SfmlLibrary.h"

//Multiple inheritance
class Enemy : public Fish, public Bird, public Crab, public Clamp, public Stopwatch
{
public:
	Enemy();
	//Get if there is an enemy spawned per region
	bool enemy_in_region1() const;
	bool enemy_in_region2() const;
	bool enemy_in_region3() const;
	bool enemy_in_region4() const;

private:

	//Regions where enemies can be possibly spawned
	bool region1;
	bool region2;
	bool region3;
	bool region4;
};
#endif
