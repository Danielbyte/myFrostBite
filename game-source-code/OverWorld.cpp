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
	temperature{45},
	startedTempDecrease{false},
	timeUp{false},
	//Initially, there should be no animal in region
	animalInRegion1{AnimalType::none},
	animalInRegion2{AnimalType::none},
	animalInRegion3{AnimalType::none},
	animalInRegion4{AnimalType::none}
{
	temperatureFont.loadFromFile("resources/sansation.ttf");
	temperature_disp.setFont(temperatureFont);
	temperature_disp.setCharacterSize(20);
	temperature_disp.setStyle(Text::Bold);
	temperature_disp.setFillColor(Color::Cyan);
	temperature_disp.setPosition(0.0f, 3.0f);

	degree_symbol.setFont(temperatureFont);
	degree_symbol.setCharacterSize(15);
	degree_symbol.setStyle(Text::Bold);
	degree_symbol.setFillColor(Color::Cyan);
	degree_symbol.setPosition(188.0f, 0.0f);
	degree_symbol.setString("o");
}

void OverWorld::create_animal(vector<shared_ptr<Crab>>& crabsObj, vector<shared_ptr<Clamp>>& clampsObj,
	vector<shared_ptr<Bird>>& birdsObj, vector<shared_ptr<Fish>>& fishObj, const float& regionPos)
{
		if (regionPos == region1Position)
		{
			//First select type of enemy to be spawned
			auto enemyType = generate_enemy_type();
			switch (enemyType)
			{
			case crab_:
				place_animal(crabsObj, region1Position);
				animalInRegion1 = AnimalType::crabs;
				break;

			case clamp_:
				//create clamps
				place_animal(clampsObj, region1Position);
				animalInRegion1 = AnimalType::clamps;
				break;

			case fish_:
				place_animal(fishObj, region1Position);
				animalInRegion1 = AnimalType::fish;
				break;

			case bird_:
				place_animal(birdsObj, region1Position);
				animalInRegion1 = AnimalType::birds;
				break;

			default:
				break;
			}
			region1 = true; //region 1 is occupied
		}

		if (regionPos == region2Position)
		{
			auto enemyType = generate_enemy_type();

			switch (enemyType)
			{
			case crab_:
				place_animal(crabsObj, region2Position);
				animalInRegion2 = AnimalType::crabs;
				break;

			case clamp_:
				place_animal(clampsObj, region2Position);
				animalInRegion2 = AnimalType::clamps;
				break;

			case fish_:
				place_animal(fishObj, region2Position);
				animalInRegion2 = AnimalType::fish;
				break;

			case bird_:
				place_animal(birdsObj, region2Position);
				animalInRegion2 = AnimalType::birds;
				break;

			default:
				break;
			}
			region2 = true;
		}

		if (regionPos == region3Position)
		{
			auto enemyType = generate_enemy_type();

			switch (enemyType)
			{
			case crab_:
				place_animal(crabsObj, region3Position);
				animalInRegion3 = AnimalType::crabs;
				break;

			case clamp_:
				place_animal(clampsObj, region3Position);
				animalInRegion3 = AnimalType::clamps;
				break;

			case fish_:
				place_animal(fishObj, region3Position);
				animalInRegion3 = AnimalType::fish;
				break;

			case bird_:
				place_animal(birdsObj, region3Position);
				animalInRegion3 = AnimalType::birds;
				break;

			default:
				break;
			}
			region3 = true;
		}

		if (regionPos == region4Position)
		{
			auto enemyType = generate_enemy_type();
			switch (enemyType)
			{
			case crab_:
				place_animal(crabsObj, region4Position);
				animalInRegion4 = AnimalType::crabs;
				break;

			case clamp_:
				place_animal(clampsObj, region4Position);
				animalInRegion4 = AnimalType::clamps;
				break;

			case fish_:
				place_animal(fishObj, region4Position);
				animalInRegion4 = AnimalType::fish;
				break;

			case bird_:
				place_animal(birdsObj, region4Position);
				animalInRegion4 = AnimalType::birds;
				break;

			default:
				break;
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

void OverWorld::update_animals_in_regions(vector<shared_ptr<Crab>>& crabs, vector<shared_ptr<Clamp>>& clamps,
	vector<shared_ptr<Bird>>& birds, vector<shared_ptr<Fish>>& fish)
{
	//clear state of regions
	clear_regions();
	//clear animals in regions
	clear_animals();

	if (!crabs.empty())
	{
		//update each region wrt crabs
		update_regions(crabs, AnimalType::crabs);

	}

	if (!clamps.empty())
	{
		//update regions wrt clamps
		update_regions(clamps, AnimalType::clamps);
	}

	if (!birds.empty())
	{
		//update regions wrt birds
		update_regions(birds, AnimalType::birds);
	}

	if (!fish.empty())
	{
		//update regions wrt fish
		update_regions(fish, AnimalType::fish);
	}
}

void OverWorld::create_ice(vector<shared_ptr<IceBlocks>>& iceBlocks)
{
		//Create first row of ice
		vector2f _pos1;
		_pos1.x = 550.0f;
		_pos1.y = 305.0f;
		shared_ptr<IceBlocks>ice1(new IceBlocks(_pos1));
		ice1->set_region(IceRegion::R1);
		ice1->set_direction(IceDirection::L);
		iceBlocks.push_back(ice1);

		//Create second row of ice
		vector2f _pos2;
		_pos2.x = 250.0f;
		_pos2.y = 387.0f;
		shared_ptr<IceBlocks>ice2(new IceBlocks(_pos2));
		ice2->set_region(IceRegion::R2);
		ice2->set_direction(IceDirection::R);
		iceBlocks.push_back(ice2);

		//create third row of ice
		vector2f _pos3;
		_pos3.x = 550.0f;
		_pos3.y = 469.0f;
		shared_ptr<IceBlocks>ice3(new IceBlocks(_pos3));
		ice3->set_region(IceRegion::R3);
		ice3->set_direction(IceDirection::L);
		iceBlocks.push_back(ice3);

		//create fourth row of ice
		vector2f _pos4;
		_pos4.x = 250.0f;
		_pos4.y = 551.0f;
		shared_ptr<IceBlocks>ice4(new IceBlocks(_pos4));
		ice4->set_region(IceRegion::R4);
		ice4->set_direction(IceDirection::R);
		iceBlocks.push_back(ice4);
}

std::tuple<AnimalType, AnimalType, AnimalType, AnimalType> OverWorld::get_type_of_animal_in_region() const
{
	return { animalInRegion1, animalInRegion2, animalInRegion3, animalInRegion4 };
}

void OverWorld::clear_regions()
{
	region1 = false;
	region2 = false;
	region3 = false;
	region4 = false;
}

void OverWorld::clear_animals()
{
	animalInRegion1 = AnimalType::none;
	animalInRegion2 = AnimalType::none;
	animalInRegion3 = AnimalType::none;
	animalInRegion4 = AnimalType::none;
}

float OverWorld::getRegion1Position() const
{
	return region1Position;
}

float OverWorld::getRegion2Position() const
{
	return region2Position;
}
float OverWorld::getRegion3Position() const
{
	return region3Position;
}

float OverWorld::getRegion4Position() const
{
	return region4Position;
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

std::tuple<AnimalType, AnimalType, AnimalType, AnimalType> OverWorld::get_animals_in_regions() const
{
	return {animalInRegion1, animalInRegion2, animalInRegion3, animalInRegion4 };
}

void OverWorld::initialize_temperature()
{
	if (!startedTempDecrease)
	{
		tempStopWatch.restart_timer();
		startedTempDecrease = true;
	}
}

void OverWorld::update_temperature()
{
	if (startedTempDecrease)
	{
		auto _time = tempStopWatch.elapsed_time();
		if (_time >= 1.0f && temperature >= 1) // decrease temperature every 1 second
		{
			--temperature; //decrease the temperature
			tempStopWatch.restart_timer();
		}

		if (temperature == 0)
		{
			timeUp = true;
		}
	}
}

void OverWorld::resetTemperature()
{
	timeUp = false;
	startedTempDecrease = false;
	temperature = 45;
	initialize_temperature();
}

Text OverWorld::getTemperature()
{
	string _temperature = std::to_string(temperature);
	temperature_disp.setString("TEMPERATURE: " + _temperature);
	return temperature_disp;
}

Text OverWorld::getTemperatureSymbol() const
{
	return degree_symbol;
}

int OverWorld::isTimeUp() const
{
	return timeUp;
}