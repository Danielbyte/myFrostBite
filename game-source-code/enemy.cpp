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
	auto crab_ = 1;
	auto clamp_ = 2;
	auto bird_ = 3;
	auto fish_ = 4;

	if (region1Pos == regionPos)
	{
		srand(time(0));
		auto enemyType = (rand() % 4) + 1;
		if (enemyType == crab_)
		{
			shared_ptr<Crab>crab_ptr(new Crab);
			crabsObj.push_back(crab_ptr);
		}

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
