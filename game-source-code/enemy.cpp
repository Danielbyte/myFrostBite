#include "enemy.h"

Enemy::Enemy(): 
	//Initially, no enemies are spawned
	region1{false},
	region2{false},
	region3{false},
	region4{false},
	region1Pos{260.0f},
	region2Pos{281.0f},
	region3Pos{322.0f},
	region4Pos{363.0f},
	gapBetweeenAnimals{120.0f}
{
	load_textures();
}

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
			create_crabs(crabs, crabsObj);
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
	srand((unsigned int)time(0));
	auto side = (rand() % 1) + 2;
	return side;
}

int Enemy::generate_enemy_type()
{
	srand((unsigned int)time(0));
	auto enemyType = (rand() % 4) + 1;
	return enemyType;
}

void Enemy::load_textures()
{
	_crab.loadFromFile("resources/crab1.png");
	_clamp.loadFromFile("resources/clamp1.png");
	_fish.loadFromFile("resources/fish1.png");
}

float Enemy::get_region1() const
{
	return region1Pos;
}

float Enemy::get_region2() const
{
	return region2Pos;
}

float Enemy::get_region3() const
{
	return region3Pos;
}

float Enemy::get_region4() const
{
	return region4Pos;
}

void Enemy::create_crabs(vector<shared_ptr<Sprite>>& _crab_sprite, vector<shared_ptr<Crab>>& crab_obj)
{
	//Randomly decide which side enemy should be created (left or right)
	auto EnemySide = pick_side();
	//spawn enemy on respective side (crab object)
	shared_ptr<Crab>crab_ptr(new Crab(EnemySide, region1Pos));
	crab_obj.push_back(crab_ptr);

	//create crab sprite based on created object
	auto crab_sprite = std::make_shared<Sprite>(Sprite());
	crab_sprite->setOrigin(crab_width / 2.0f, crab_height / 2.0f);
	crab_sprite->setTexture(_crab);
	auto pos = crab_ptr->get_position();
	crab_sprite->setPosition(pos);
	_crab_sprite.push_back(crab_sprite);

	//create second crab
	shared_ptr<Crab>crab_ptr2(new Crab(EnemySide, region1Pos));
	crab_ptr2->set_x_position(gapBetweeenAnimals);
	crab_obj.push_back(crab_ptr2);

	//create second crab sprite based on created object
	auto crab_sprite2 = std::make_shared<Sprite>(Sprite());
	crab_sprite2->setOrigin(crab_width / 2.0f, crab_height / 2.0f);
	crab_sprite2->setTexture(_crab);
	auto pos_ = crab_ptr2->get_position();
	crab_sprite2->setPosition(pos_);
	_crab_sprite.push_back(crab_sprite2);
}
