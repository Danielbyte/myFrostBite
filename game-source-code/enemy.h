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

	//Textures
	Texture _crab,_clamp_left,_bird_left,_fish_left;
	void load_textures();

	//get regions
	float get_region1() const;
	float get_region2() const;
	float get_region3() const;
	float get_region4() const;

	//Create animals
	void create_crabs(vector<shared_ptr<Sprite>>&, vector<shared_ptr<Crab>>&, const float&);
	void create_clamps(vector<shared_ptr<Sprite>>&, vector<shared_ptr<Clamp>>&, const float&);
	void create_fish(vector<shared_ptr<Sprite>>&, vector<shared_ptr<Fish>>&, const float&);
	void create_birds(vector<shared_ptr<Sprite>>&, vector<shared_ptr<Bird>>&, const float&);

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

	float gapBetweeenAnimals;

	int pick_side();
	int generate_enemy_type();
};
#endif
