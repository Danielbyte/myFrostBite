#include "enemy.h"

Enemy::Enemy(): 
	//Initially, no enemies are spawned
	region1{false},
	region2{false},
	region3{false},
	region4{false},
	region1Pos{240.0f},
	region2Pos{281.0f},
	region3Pos{322.0f},
	region4Pos{363.0f}
{}

void Enemy::create_enemy(vector<shared_ptr<Sprite>>& crabs, vector<shared_ptr<Sprite>>& clamps,
	vector<shared_ptr<Sprite>>& birds, vector<shared_ptr<Sprite>>& fish,
	vector<shared_ptr<Crab>>& crabsObj, vector<shared_ptr<Clamp>>& clampsObj,
	vector<shared_ptr<Bird>>& birdsObj, vector<shared_ptr<Fish>>& fishObj, const float& regionPos)
{

	if (region1Pos == regionPos)
	{
		//First select type of enemy to be spawned
		auto enemyType = generate_enemy_type();
		if (enemyType == crab_)
		{
			//Randomly decide which side enemy should be created (left or right)
			auto EnemySide = pick_side();

			if (EnemySide == right)
			{
				//spawn enemy on the right
				shared_ptr<Crab>crab_ptr(new Crab);
				crabsObj.push_back(crab_ptr);
			}
			
		}

		region1 = true; //region 1 is occupied
	}

	if (region2Pos == regionPos)
	{

	}

	if (region3Pos == regionPos)
	{

	}

	if (region4Pos == regionPos)
	{

	}
}

bool Enemy::enemy_in_region1() const
{
	return region1;
}

bool Enemy::enemy_in_region2() const
{
	return region2;
}

bool Enemy::enemy_in_region3() const
{
	return region3;
}

bool Enemy::enemy_in_region4() const
{
	return region4;
}

int Enemy::pick_side()
{
	//This function randomly generates side at which enemy should be spawned
	srand(time(0));
	auto side = (rand() % 1) + 2;
	return side;
}

int Enemy::generate_enemy_type()
{
	srand(time(0));
	auto enemyType = (rand() % 4) + 1;
	return enemyType;
}
