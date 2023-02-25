#include "crabController.h"

CrabController::CrabController()
{
	load_textures();
}

void CrabController::update_crab(vector<shared_ptr<Sprite>>& crab_sprites,
	vector<shared_ptr<Crab>>& crabObj)
{
	if (!crabObj.empty())
	{
		auto crab_ptr = crabObj.begin();
		auto crab_spritePtr = crab_sprites.begin();

		while (crab_ptr != crabObj.end())
		{
			animate(*crab_spritePtr, *crab_ptr);

			auto cycle = (*crab_ptr)->get_cycle();
			if (cycle == first_cycle)
			{
				std::cout << "crab moves!" << std::endl;
			}

			else if (cycle == second_cycle)
			{
				std::cout << "crab not move!" << std::endl;
			}

			++crab_ptr;
			++crab_spritePtr;
		}
	}
}

void CrabController::load_textures()
{
	crab1.loadFromFile("resources/crab1.png");
	crab2.loadFromFile("resources/crab2.png");
	crab3.loadFromFile("resources/crab3.png");
	crab4.loadFromFile("resources/crab4.png");
	crab5.loadFromFile("resources/crab5.png");
	crab6.loadFromFile("resources/crab6.png");
}

void CrabController::animate(shared_ptr<Sprite>& sprite_ptr, shared_ptr<Crab>& obj_ptr)
{
	obj_ptr ->increment_counter();
	auto counter = obj_ptr->get_counter();

	if (counter > 0 && counter <= 10)
	{
		sprite_ptr->setTexture(crab1);
	}

	else if (counter > 10 && counter <= 20)
	{
		sprite_ptr->setTexture(crab2);
	}

	else if (counter > 20 && counter <= 30)
	{
		sprite_ptr->setTexture(crab3);
	}

	else if (counter > 30 && counter <= 40)
	{
		sprite_ptr->setTexture(crab4);
	}

	else if (counter > 40 && counter <= 50)
	{
		sprite_ptr->setTexture(crab5);
	}

	else if (counter > 50 && counter <= 60)
	{
		sprite_ptr->setTexture(crab6);
		obj_ptr->reset_counter();
		auto cycle = obj_ptr->get_cycle();
		obj_ptr->increment_cycle();
	
		if (cycle > second_cycle)
		{
			obj_ptr->reset_cycle();
		}
	}
}


