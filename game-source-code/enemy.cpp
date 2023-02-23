#include "enemy.h"

Enemy::Enemy(): 
	//Initially, no enemies are spawned
	region1{false},
	region2{false},
	region3{false},
	region4{false}
{}

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
