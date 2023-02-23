#ifndef ENEMY_H
#define ENEMY_H

#include "fish.h"
#include "bird.h"
#include "crab.h"
#include "clamp.h"
#include "stopwatch.h"
#include "SfmlLibrary.h"
#include "gameConstants.h"

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
	//Function below creates different enemy entities
	void create_enemy(vector<shared_ptr<Sprite>>&, vector<shared_ptr<Sprite>>&, vector<shared_ptr<Sprite>>&,
		vector<shared_ptr<Sprite>>&, vector<shared_ptr<Crab>>&, vector<shared_ptr<Clamp>>&,
		vector<shared_ptr<Bird>>&, vector<shared_ptr<Fish>>&, const float&);

private:

	//Regions where enemies can be possibly spawned
	bool region1;
	bool region2;
	bool region3;
	bool region4;

	float region1Pos;
	float region2Pos;
	float region3Pos;
	float region4Pos;
};
#endif
