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
	void clear_regions();
	void clear_animals();

	AnimalType animalInRegion1, animalInRegion2, animalInRegion3, animalInRegion4;

	void update_animals_in_regions(vector<shared_ptr<Crab>>&, vector<shared_ptr<Clamp>>&,
		vector<shared_ptr<Bird>>&, vector<shared_ptr<Fish>>&);

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

	template<typename _Animal, typename _AnimalType>
	_Animal update_regions(const vector<shared_ptr<_Animal>>& animal, const _AnimalType animal_type)
	{
		auto animal_ptr = animal.begin();
		while (animal_ptr != animal.end())
		{
			auto y_pos = ((*animal_ptr)->getPosition()).y;
			//update the first region if it has not been updated
			if (y_pos == region1Position && !region1)
			{
				region1 = true;
				animalInRegion1 = animal_type;
			}

			if (y_pos == region2Position && !region2)
			{
				region2 = true;
				animalInRegion2 = animal_type;
			}

			if (y_pos == region3Position && !region3)
			{
				region3 = true;
				animalInRegion3 = animal_type;
			}
			if (y_pos == region4Position && !region4)
			{
				region4 = true;
				animalInRegion4 = animal_type;
			}
			++animal_ptr;
		}
	}
};

#endif // !OVERWORLD_H

