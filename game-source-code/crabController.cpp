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
			(*crab_ptr)->increment_counter();
			auto counter = (*crab_ptr)->get_counter();

			if (counter > 0 && counter <= 10)
			{
				(*crab_spritePtr)->setTexture(crab1);
			}

			else if (counter > 10 && counter <= 20)
			{
				(*crab_spritePtr)->setTexture(crab2);
			}

			else if (counter > 20 && counter <= 30)
			{
				(*crab_spritePtr)->setTexture(crab3);
			}

			else if (counter > 30 && counter <= 40)
			{
				(*crab_spritePtr)->setTexture(crab4);
			}

			else if (counter > 40 && counter <= 50)
			{
				(*crab_spritePtr)->setTexture(crab5);
			}

			else if (counter > 50 && counter <= 60)
			{
				(*crab_spritePtr)->setTexture(crab6);
				(*crab_ptr)->reset_counter();
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

