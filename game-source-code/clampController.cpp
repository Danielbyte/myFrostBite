#include "clampController.h"

ClampController::ClampController():
	speed_controller{100.0f},
	LOutOfBounds{821.0f},
	ROutOfBounds{-21.0f},
	mLOutOfBounds{622.473f},
	mROutOfBounds{179.0f}
{
	load_tectures();
}

void ClampController::setMultiPlayerBounds()
{
	LOutOfBounds = mLOutOfBounds;
	ROutOfBounds = mROutOfBounds;
}

void ClampController::update_clamp(vector<shared_ptr<Clamp>>& clamps, const float deltaTime)
{
	if (!clamps.empty())
	{
		auto clamp_iter = clamps.begin();

		while (clamp_iter != clamps.end())
		{
			auto cycle = (*clamp_iter)->get_cycle();

			if (cycle == clamp_first_cycle) //move clamp for first cycle, else stationary
			{
				auto [left, right] = (*clamp_iter)->getSide();

				if (left) //clamp was spawned on the left
				{
					vector2f pos = (*clamp_iter)->getPosition();
					pos.x += speed_controller * deltaTime;
					(*clamp_iter)->setPosition(pos);

					if (pos.x >= LOutOfBounds)
					{
						clamps.erase(clamp_iter);
						return;
					}
				}

				else if (right) //clamp was spawned on the right
				{
					//(*sprite_ptr)->move(-deltaTime * speed_controller, 0);
					vector2f pos = (*clamp_iter)->getPosition();
					pos.x -= speed_controller * deltaTime;
					(*clamp_iter)->setPosition(pos);

					if (pos.x <= ROutOfBounds)
					{
						clamps.erase(clamp_iter);
						return;
					}
				}
			}
			animate(*clamp_iter);
			++clamp_iter;
		}
	}
}

void ClampController::animate(shared_ptr<Clamp>& clamp)
{
	clamp->increment_counter();
	auto counter = clamp->get_counter();
	auto [left, right] = clamp->getSide();

	if (left)
	{
		if (counter > 0 && counter <= 10)
		{
			clamp->updateSpriteTexture(clamp1_left);
			clamp->updateSpritePosition();
		}
		else if (counter > 10 && counter <= 20)
		{
			clamp->updateSpriteTexture(clamp2_left);
			clamp->updateSpritePosition();
		}
		else if (counter > 20 && counter <= 30)
		{
			clamp->updateSpriteTexture(clamp3_left);
			clamp->updateSpritePosition();
		}
		else if (counter > 30 && counter <= 40)
		{
			clamp->updateSpriteTexture(clamp4_left);
			clamp->updateSpritePosition();
		}
		else if (counter > 40 && counter <= 50)
		{
			clamp->updateSpriteTexture(clamp5_left);
			clamp->updateSpritePosition();
		}
		else if (counter > 50 && counter <= 60)
		{
			clamp->updateSpriteTexture(clamp6_left);
			clamp->updateSpritePosition();
		}
		else if (counter > 60 && counter <= 70)
		{
			clamp->updateSpriteTexture(clamp7_left);
			clamp->updateSpritePosition();
		}
		else if (counter > 70 && counter <= 80)
		{
			clamp->updateSpriteTexture(clamp8_left);
			clamp->updateSpritePosition();
		}
		else if (counter > 80 && counter <= 90)
		{
			clamp->updateSpriteTexture(clamp9_left);
			clamp->updateSpritePosition();
		}
		else if (counter > 90 && counter <= 100)
		{
			clamp->updateSpriteTexture(clamp10_left);
			clamp->updateSpritePosition();
			clamp->reset_counter();
			clamp->increment_cycle();
			auto cycle = clamp->get_cycle();
			if (cycle > clamp_second_cycle)
			{
				//past the last cycle of the movement pattern
				clamp->reset_cycle();//start over again
			}
		}
	}

	else if (right)
	{
		if (counter > 0 && counter <= 10)
		{
			clamp->updateSpriteTexture(clamp1_right);
			clamp->updateSpritePosition();
		}
		else if (counter > 10 && counter <= 20)
		{
			clamp->updateSpriteTexture(clamp2_right);
			clamp->updateSpritePosition();
		}
		else if (counter > 20 && counter <= 30)
		{
			clamp->updateSpriteTexture(clamp3_right);
			clamp->updateSpritePosition();
		}
		else if (counter > 30 && counter <= 40)
		{
			clamp->updateSpriteTexture(clamp4_right);
			clamp->updateSpritePosition();
		}
		else if (counter > 40 && counter <= 50)
		{
			clamp->updateSpriteTexture(clamp5_right);
			clamp->updateSpritePosition();
		}
		else if (counter > 50 && counter <= 60)
		{
			clamp->updateSpriteTexture(clamp6_right);
			clamp->updateSpritePosition();
		}
		else if (counter > 60 && counter <= 70)
		{
			clamp->updateSpriteTexture(clamp7_right);
			clamp->updateSpritePosition();
		}
		else if (counter > 70 && counter <= 80)
		{
			clamp->updateSpriteTexture(clamp8_right);
			clamp->updateSpritePosition();
		}
		else if (counter > 80 && counter <= 90)
		{
			clamp->updateSpriteTexture(clamp9_right);
			clamp->updateSpritePosition();
		}
		else if (counter > 90 && counter <= 100)
		{
			clamp->updateSpriteTexture(clamp10_right);
			clamp->updateSpritePosition();
			clamp->reset_counter();
			clamp->increment_cycle();
			auto cycle = clamp->get_cycle();
			if (cycle > clamp_second_cycle)
			{
				//past the last cycle of the movement pattern
				clamp->reset_cycle();//start over again
			}
		}
	}
}

void ClampController::load_tectures()
{
	//load textures if clamp spawned from the left
	clamp1_left.loadFromFile("resources/clamp1_left.png");
	clamp2_left.loadFromFile("resources/clamp2_left.png");
	clamp3_left.loadFromFile("resources/clamp3_left.png");
	clamp4_left.loadFromFile("resources/clamp4_left.png");
	clamp5_left.loadFromFile("resources/clamp5_left.png");
	clamp6_left.loadFromFile("resources/clamp6_left.png");
	clamp7_left.loadFromFile("resources/clamp7_left.png");
	clamp8_left.loadFromFile("resources/clamp8_left.png");
	clamp9_left.loadFromFile("resources/clamp9_left.png");
	clamp10_left.loadFromFile("resources/clamp10_left.png");

	//load textures if clamp spawned from the right
	clamp1_right.loadFromFile("resources/clamp1_right.png");
	clamp2_right.loadFromFile("resources/clamp2_right.png");
	clamp3_right.loadFromFile("resources/clamp3_right.png");
	clamp4_right.loadFromFile("resources/clamp4_right.png");
	clamp5_right.loadFromFile("resources/clamp5_right.png");
	clamp6_right.loadFromFile("resources/clamp6_right.png");
	clamp7_right.loadFromFile("resources/clamp7_right.png");
	clamp8_right.loadFromFile("resources/clamp8_right.png");
	clamp9_right.loadFromFile("resources/clamp9_right.png");
	clamp10_right.loadFromFile("resources/clamp10_right.png");
}
