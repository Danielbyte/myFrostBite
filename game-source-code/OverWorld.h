#pragma once
#ifndef OVERWORLD_H
#define OVERWORLD_H

#include "stopwatch.h"
#include "crab.h"
#include "clamp.h"
#include "bird.h"
#include "fish.h"

enum class AnimalType { crabs, clamps, birds, fish, none };

class OverWorld
{
public:
	OverWorld();

	//Get if there is an animal spawned in region
	bool Isanimal_in_region1() const;
	bool Isanimal_in_region2() const;
	bool Isanimal_in_region3() const;
	bool Isanimal_in_region4() const;

	//Create animals
	void create_animal(vector<shared_ptr<Crab>>&, vector<shared_ptr<Clamp>>&, vector<shared_ptr<Bird>>&,
		vector<shared_ptr<Fish>>&, const float&);
	//void create_crabs(vector<shared_ptr<Crab>>&, const float&);
	//void create_clamps(vector<shared_ptr<Clamp>>&, const float&);
	//void create_fish(vector<shared_ptr<Fish>>&, const float&);
	//void create_birds(vector<shared_ptr<Bird>>&, const float&);

private:

	//Regions where animals can be possibly spawned
	bool region1;
	bool region2;
	bool region3;
	bool region4;

	//Demacate region positions
	float region1Position;
	float region2Position;
	float region3Position;
	float region4Position;

	float gapBetweeenAnimals;

	int pick_side();
	int generate_enemy_type();

	//check for sea animals in each region to update status of each region to empty or not
	void check_for_crabs_in_region(vector<shared_ptr<Crab>>&);
	void check_for_clamps_in_region(vector<shared_ptr<Clamp>>&);
	void check_for_birds_in_region(vector<shared_ptr<Bird>>&);
	void check_for_fish_in_region(vector<shared_ptr<Fish>>&);

	void reset_regions();
	void clear_animals();

	AnimalType animalInRegion1, animalInRegion2, animalInRegion3, animalInRegion4;

	template<typename T>
	T place_animal(vector<shared_ptr<T>>& animal, const float region)
	{
		//select side
		auto EnemySide = pick_side();
		//create new animal object
		shared_ptr<T>animal_ptr(new T(EnemySide, region));
		animal.push_back(animal_ptr);

		//crate second animal
		shared_ptr<T>animal_ptr2(new T(EnemySide, region));
		animal_ptr2->set_x_position(gapBetweeenAnimals);
		animal.push_back(animal_ptr2);
	}
};

#endif // !OVERWORLD_H

