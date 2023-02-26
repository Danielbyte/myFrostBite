#include "enemy.h"

Enemy::Enemy(): 
	//Initially, no enemies are spawned
	region1{false},
	region2{false},
	region3{false},
	region4{false},
	region1Pos{260.0f},
	region2Pos{342.0f},
	region3Pos{424.0f},
	region4Pos{506.0f},
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
			create_crabs(crabs, crabsObj,region1Pos);
		}

		else if (enemyType == clamp_)
		{
			//create clamps
			create_crabs(crabs, crabsObj, region1Pos);
		}

		else if (enemyType == fish_)
		{
			create_fish(fish, fishObj, region1Pos);
		}

		else if (enemyType == bird_)
		{
			create_birds(birds, birdsObj, region1Pos);
		}
		region1 = true; //region 1 is occupied
	}

	if (region2Pos == regionPos)
	{
		auto enemyType = generate_enemy_type();
		if (enemyType == crab_)
		{
			create_crabs(crabs, crabsObj,region2Pos);
		}

		else if (enemyType == clamp_)
		{
			//create clamps
			create_crabs(crabs, crabsObj, region2Pos);
		}

		else if (enemyType == fish_)
		{
			create_fish(fish, fishObj, region2Pos);
		}

		else if (enemyType == bird_)
		{
			create_birds(birds, birdsObj, region2Pos);
		}
		region2 = true;
	}

	if (region3Pos == regionPos)
	{
		auto enemyType = generate_enemy_type();
		if (enemyType == crab_)
		{
			create_crabs(crabs, crabsObj,region3Pos);
		}

		else if (enemyType == clamp_)
		{
			//create clamps
			create_clamps(clamps, clampsObj, region3Pos);
		}

		else if (enemyType == fish_)
		{
			create_fish(fish, fishObj, region3Pos);
		}

		else if (enemyType == bird_)
		{
			create_birds(birds, birdsObj, region3Pos);
		}
		region3 = true;
	}

	if (region4Pos == regionPos)
	{
		auto enemyType = generate_enemy_type();
		if (enemyType == crab_)
		{
			create_crabs(crabs, crabsObj,region4Pos);
		}

		else if (enemyType == clamp_)
		{
			create_crabs(crabs, crabsObj, region4Pos);
		}

		else if (enemyType == fish_)
		{
			create_fish(fish, fishObj, region4Pos);
		}

		else if (enemyType == bird_)
		{
			create_birds(birds, birdsObj, region4Pos);
		}
		region4 = true;
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
	std::random_device rd;
	std::uniform_int_distribution<int>dist(1, 2);
	auto side = dist(rd);
	return side;
}

int Enemy::generate_enemy_type()
{
	std::random_device rd;
	std::uniform_int_distribution<int>dist(1, 4);
	auto enemyType = dist(rd);
	return enemyType;
}

void Enemy::load_textures()
{
	_crab.loadFromFile("resources/crab1.png");
	_clamp_left.loadFromFile("resources/clamp1_left.png");
	_fish_left.loadFromFile("resources/fish1_left.png");
	_bird_left.loadFromFile("resources/bird1_left.png");
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

void Enemy::create_crabs(vector<shared_ptr<Sprite>>& _crab_sprite, vector<shared_ptr<Crab>>& crab_obj, 
	const float& regionPos)
{
	//Randomly decide which side enemy should be created (left or right)
	auto EnemySide = pick_side();
	//spawn enemy on respective side (crab object)
	shared_ptr<Crab>crab_ptr(new Crab(EnemySide, regionPos));
	crab_obj.push_back(crab_ptr);

	//create crab sprite based on created object
	auto crab_sprite = std::make_shared<Sprite>(Sprite());
	crab_sprite->setOrigin(crab_width / 2.0f, crab_height / 2.0f);
	crab_sprite->setTexture(_crab);
	auto pos = crab_ptr->get_position();
	crab_sprite->setPosition(pos);
	_crab_sprite.push_back(crab_sprite);

	//create second crab
	shared_ptr<Crab>crab_ptr2(new Crab(EnemySide, regionPos));
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

void Enemy::create_clamps(vector<shared_ptr<Sprite>>& _clamp_sprite, vector<shared_ptr<Clamp>>& clampObj,
	const float& regionPos)
{
	//select side
	auto EnemySide = pick_side();
	//create new clamp object
	shared_ptr<Clamp>clamp_ptr(new Clamp(EnemySide, regionPos));
	clampObj.push_back(clamp_ptr);

	//create clamp sprite based on object
	auto clamp_sprite = std::make_shared<Sprite>(Sprite());
	clamp_sprite->setOrigin(clamp_width / 2.0f, clamp_height / 2.0f);
	clamp_sprite->setTexture(_clamp_left);
	auto pos = clamp_ptr->get_position();
	clamp_sprite->setPosition(pos);
	_clamp_sprite.push_back(clamp_sprite);

	//crate second clamp
	shared_ptr<Clamp>clamp_ptr2(new Clamp(EnemySide, regionPos));
	clamp_ptr2->set_x_position(gapBetweeenAnimals);
	clampObj.push_back(clamp_ptr2);

	//create second clamp sprite
	auto clamp_sprite2 = std::make_shared<Sprite>(Sprite());
	clamp_sprite2->setOrigin(clamp_width / 2.0f, clamp_height / 2.0f);
	clamp_sprite2->setTexture(_clamp_left);
	auto pos2 = clamp_ptr2->get_position();
	clamp_sprite2->setPosition(pos2);
	_clamp_sprite.push_back(clamp_sprite2);
}

void Enemy::create_fish(vector<shared_ptr<Sprite>>& _fish_sprite, vector<shared_ptr<Fish>>& fishObj,
	const float& regionPos)
{
	//select side
	auto EnemySide = pick_side();
	//create new fish object
	shared_ptr<Fish>fish_ptr(new Fish(EnemySide, regionPos));
	fishObj.push_back(fish_ptr);

	//create fish sprite based on object
	auto fish_sprite = std::make_shared<Sprite>(Sprite());
	fish_sprite->setOrigin(clamp_width / 2.0f, clamp_height / 2.0f);
	fish_sprite->setTexture(_fish_left);
	auto pos = fish_ptr->get_position();
	fish_sprite->setPosition(pos);
	_fish_sprite.push_back(fish_sprite);

	//crate second fish
	shared_ptr<Fish>fish_ptr2(new Fish(EnemySide, regionPos));
	fish_ptr2->set_x_position(gapBetweeenAnimals);
	fishObj.push_back(fish_ptr2);

	//create second fish sprite
	auto fish_sprite2 = std::make_shared<Sprite>(Sprite());
	fish_sprite2->setOrigin(clamp_width / 2.0f, clamp_height / 2.0f);
	fish_sprite2->setTexture(_fish_left);
	auto pos2 = fish_ptr2->get_position();
	fish_sprite2->setPosition(pos2);
	_fish_sprite.push_back(fish_sprite2);
}

void Enemy::create_birds(vector<shared_ptr<Sprite>>& _bird_sprite, vector<shared_ptr<Bird>>& birdObj,
	const float& regionPos)
{
	//select side
	auto EnemySide = pick_side();
	//create new bird object
	shared_ptr<Bird>bird_ptr(new Bird(EnemySide, regionPos));
	birdObj.push_back(bird_ptr);

	//create bird sprite based on object
	auto bird_sprite = std::make_shared<Sprite>(Sprite());
	bird_sprite->setOrigin(bird_width / 2.0f, bird_height / 2.0f);
	bird_sprite->setTexture(_bird_left);
	auto pos = bird_ptr->get_position();
	bird_sprite->setPosition(pos);
	_bird_sprite.push_back(bird_sprite);

	//crate second bird
	shared_ptr<Bird>bird_ptr2(new Bird(EnemySide, regionPos));
	bird_ptr2->set_x_position(gapBetweeenAnimals);
	birdObj.push_back(bird_ptr2);

	//create second bird sprite
	auto bird_sprite2 = std::make_shared<Sprite>(Sprite());
	bird_sprite2->setOrigin(bird_width / 2.0f, bird_height / 2.0f);
	bird_sprite2->setTexture(_bird_left);
	auto pos2 = bird_ptr2->get_position();
	bird_sprite2->setPosition(pos2);
	_bird_sprite.push_back(bird_sprite2);
}

void Enemy::update_enemy_regions(vector<shared_ptr<Crab>>& crabs, vector<shared_ptr<Clamp>>& clamps,
	vector<shared_ptr<Bird>>& birds, vector<shared_ptr<Fish>>& fish)
{
	//reset regions to be re-updated
	reset_regions();
	//crabs in the sea
	if (!crabs.empty())
	{
		//check for crabs in region
		crabs_in_region(crabs);
		
	}

	if (!clamps.empty())
	{
		//check for clamps in region
		clamps_in_region(clamps);
	}

	if (!birds.empty())
	{
		//check for birds in region
		birds_in_region(birds);
	}

	if (!fish.empty())
	{
		//check for fish in region
		fish_in_region(fish);
	}
}

void Enemy::birds_in_region(vector<shared_ptr<Bird>>& birds)
{
	auto bird_ptr = birds.begin();
	while (bird_ptr != birds.end())
	{
		auto y_pos = ((*bird_ptr)->get_position()).y;
		//update the first region if it has not been updated
		if (y_pos == region1Pos && !region1)
		{
			region1 = true;
		}

		if (y_pos == region2Pos && !region2)
		{
			region2 = true;
		}

		if (y_pos == region3Pos && !region3)
		{
			region3 = true;
		}
		if (y_pos == region4Pos && !region4)
		{
			region4 = true;
		}
		++bird_ptr;
	}
}

void Enemy::crabs_in_region(vector<shared_ptr<Crab>>& crabs)
{
	auto crab_ptr = crabs.begin();
	while (crab_ptr != crabs.end())
	{
		auto y_pos = ((*crab_ptr)->get_position()).y;
		//update the first region if it has not been updated
		if (y_pos == region1Pos && !region1)
		{
			region1 = true;
		}

		if (y_pos == region2Pos && !region2)
		{
			region2 = true;
		}

		if (y_pos == region3Pos && !region3)
		{
			region3 = true;
		}
		if (y_pos == region4Pos && !region4)
		{
			region4 = true;
		}
		++crab_ptr;
	}
}

void Enemy::fish_in_region(vector<shared_ptr<Fish>>& fish)
{
	auto fish_ptr = fish.begin();
	while (fish_ptr != fish.end())
	{
		auto y_pos = ((*fish_ptr)->get_position()).y;
		//update the first region if it has not been updated
		if (y_pos == region1Pos && !region1)
		{
			region1 = true;
		}

		if (y_pos == region2Pos && !region2)
		{
			region2 = true;
		}

		if (y_pos == region3Pos && !region3)
		{
			region3 = true;
		}
		if (y_pos == region4Pos && !region4)
		{
			region4 = true;
		}
		++fish_ptr;
	}
}

void Enemy::clamps_in_region(vector<shared_ptr<Clamp>>& clamps)
{
	auto clamp_ptr = clamps.begin();
	while (clamp_ptr != clamps.end())
	{
		auto y_pos = ((*clamp_ptr)->get_position()).y;
		//update the first region if it has not been updated
		if (y_pos == region1Pos && !region1)
		{
			region1 = true;
		}

		if (y_pos == region2Pos && !region2)
		{
			region2 = true;
		}

		if (y_pos == region3Pos && !region3)
		{
			region3 = true;
		}
		if (y_pos == region4Pos && !region4)
		{
			region4 = true;
		}
		++clamp_ptr;
	}
}

void Enemy::reset_regions()
{
	//reset regions to be re-updated
	region1 = false;
	region2 = false;
	region3 = false;
	region4 = false;
}