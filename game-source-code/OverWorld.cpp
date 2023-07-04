#include "OverWorld.h"

OverWorld::OverWorld():
	//Initially, no enemies are spawned
	region1{ false },
	region2{ false },
	region3{ false },
	region4{ false },
	region1Position{ 260.0f },
	region2Position{ 342.0f },
	region3Position{ 424.0f },
	region4Position{ 506.0f },
	gapBetweeenAnimals{ 120.0f },
	//Initially, there should be no animal in region
	animalInRegion1{AnimalType::none},
	animalInRegion2{AnimalType::none},
	animalInRegion3{AnimalType::none},
	animalInRegion4{AnimalType::none}
{}

void OverWorld::create_animal(vector<shared_ptr<Crab>>& crabsObj, vector<shared_ptr<Clamp>>& clampsObj,
	vector<shared_ptr<Bird>>& birdsObj, vector<shared_ptr<Fish>>& fishObj, const float& regionPos)
{
		if (regionPos == region1Position)
		{
			//First select type of enemy to be spawned
			auto enemyType = generate_enemy_type();
			if (enemyType == crab_)
			{
				place_animal(crabsObj, region1Position);
				animalInRegion1 = AnimalType::crabs;
			}

			else if (enemyType == clamp_)
			{
				//create clamps
				place_animal(crabsObj, region1Position);
				animalInRegion1 = AnimalType::clamps;
			}

			else if (enemyType == fish_)
			{
				place_animal(fishObj, region1Position);
				animalInRegion1 = AnimalType::fish;
			}

			else if (enemyType == bird_)
			{
				place_animal(birdsObj, region1Position);
				animalInRegion1 = AnimalType::birds;
			}
			region1 = true; //region 1 is occupied
		}

		if (regionPos == region2Position)
		{
			auto enemyType = generate_enemy_type();
			if (enemyType == crab_)
			{
				place_animal(crabsObj, region2Position);
				animalInRegion2 = AnimalType::crabs;
			}

			else if (enemyType == clamp_)
			{
				//create clamps
				place_animal(crabsObj, region2Position);
				animalInRegion2 = AnimalType::clamps;
			}

			else if (enemyType == fish_)
			{
				place_animal(fishObj, region2Position);
				animalInRegion2 = AnimalType::fish;
			}

			else if (enemyType == bird_)
			{
				place_animal(birdsObj, region2Position);
				animalInRegion2 = AnimalType::birds;
			}
			region2 = true;
		}

		if (regionPos == region3Position)
		{
			auto enemyType = generate_enemy_type();
			if (enemyType == crab_)
			{
				place_animal(crabsObj, region3Position);
				animalInRegion3 = AnimalType::crabs;
			}

			else if (enemyType == clamp_)
			{
				//create clamps
				place_animal(clampsObj, region3Position);
				animalInRegion3 = AnimalType::clamps;
			}

			else if (enemyType == fish_)
			{
				place_animal(fishObj, region3Position);
				animalInRegion3 = AnimalType::fish;
			}

			else if (enemyType == bird_)
			{
				place_animal(birdsObj, region3Position);
				animalInRegion3 = AnimalType::birds;
			}
			region3 = true;
		}

		if (regionPos == region4Position)
		{
			auto enemyType = generate_enemy_type();
			if (enemyType == crab_)
			{
				place_animal(crabsObj, region4Position);
				animalInRegion4 = AnimalType::crabs;
			}

			else if (enemyType == clamp_)
			{
				place_animal(crabsObj, region4Position);
				animalInRegion4 = AnimalType::clamps;
			}

			else if (enemyType == fish_)
			{
				place_animal(fishObj, region4Position);
				animalInRegion4 = AnimalType::fish;
			}

			else if (enemyType == bird_)
			{
				place_animal(birdsObj, region4Position);
				animalInRegion4 = AnimalType::birds;
			}
			region4 = true;
		}
}

int OverWorld::generate_enemy_type()
{
	std::random_device rd;
	std::uniform_int_distribution<int>dist(1, 4);
	auto enemyType = dist(rd);
	return enemyType;
}

int OverWorld::pick_side()
{
	std::random_device rd;
	std::uniform_int_distribution<int>dist(1, 2);
	auto side = dist(rd);
	return side;
}

bool OverWorld::Isanimal_in_region1() const
{
	return region1;
}

bool OverWorld::Isanimal_in_region2() const
{
	return region2;
}

bool OverWorld::Isanimal_in_region3() const
{
	return region3;
}

bool OverWorld::Isanimal_in_region4() const
{
	return region4;
}

/*T OverWorld::place_animal(vector<shared_ptr<T>>_animal, const float _regionPos)
{

}*/