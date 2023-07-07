#include "crabController.h"

CrabController::CrabController():
	speed_controller{100.0f}
{
	load_textures();
}

void CrabController::update_crab(vector<shared_ptr<Crab>>& crabs, const float deltaTime)
{
	if (!crabs.empty())
	{
		auto crab_iter = crabs.begin();
		//auto crab_spritePtr = crab_sprites.begin();

		while (crab_iter != crabs.end())
		{
			auto cycle = (*crab_iter)->get_cycle();
			if (cycle == first_cycle)
			{
				//the crab should move
				auto [left, right] = (*crab_iter)->getSide();
				if (left)
				{
					//(*crab_spritePtr)->move(deltaTime * speed_controller, 0);
					vector2f pos = (*crab_iter)->getPosition();
					pos.x += speed_controller * deltaTime;
					(*crab_iter)->setPosition(pos);

					auto outOfBounds = windowWidth + (crab_width / 2.0f);
					if (pos.x >= outOfBounds)
					{
						crabs.erase(crab_iter);
						return;
					}
				}

				else if (right)
				{
					//(*crab_spritePtr)->move(-deltaTime * speed_controller, 0);
					vector2f pos = (*crab_iter)->getPosition();
					pos.x -= speed_controller * deltaTime;
					(*crab_iter)->setPosition(pos);

					auto outOfBounds = -crab_width / 2.0f;
					if (pos.x <= outOfBounds)
					{
						crabs.erase(crab_iter);
						return;
					}
				}
			}
			animate(*crab_iter);
			++crab_iter;
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

void CrabController::animate(shared_ptr<Crab>& crab)
{
	crab ->increment_counter();
	auto counter = crab->get_counter();

	if (counter > 0 && counter <= 10)
	{
		crab->updateSpriteTexture(crab1);
		crab->updateSpritePosition();
	}

	else if (counter > 10 && counter <= 20)
	{
		crab->updateSpriteTexture(crab2);
		crab->updateSpritePosition();
	}

	else if (counter > 20 && counter <= 30)
	{
		crab->updateSpriteTexture(crab3);
		crab->updateSpritePosition();
	}

	else if (counter > 30 && counter <= 40)
	{
		crab->updateSpriteTexture(crab4);
		crab->updateSpritePosition();
	}

	else if (counter > 40 && counter <= 50)
	{
		crab->updateSpriteTexture(crab5);
		crab->updateSpritePosition();
	}

	else if (counter > 50 && counter <= 60)
	{
		crab->updateSpriteTexture(crab6);
		crab->updateSpritePosition();
		crab->reset_counter();
		auto cycle = crab->get_cycle();
		crab->increment_cycle();
	
		if (cycle > second_cycle)
		{
			crab->reset_cycle();
		}
	}
}


