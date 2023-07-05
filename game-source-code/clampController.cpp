#include "clampController.h"

ClampController::ClampController():
	speed_controller{100.0f}
{
	load_tectures();
}

void ClampController::update_clamp(vector<shared_ptr<Clamp>>& clamps, const float deltaTime)
{
	if (!clamps.empty())
	{
		auto clamp_iter = clamps.begin();

		while (clamp_iter != clamps.end())
		{
			//animate(*sprite_ptr, *obj_ptr);
			auto cycle = (*clamp_iter)->get_cycle();

			if (cycle == clamp_first_cycle) //move clamp for first cycle, else stationary
			{
				auto [left, right] = (*clamp_iter)->getSide();

				if (left) //clamp was spawned on the left
				{
					//(*sprite_ptr)->move(deltaTime * speed_controller, 0);
					vector2f pos = (*clamp_iter)->getPosition();
					pos.x += speed_controller * deltaTime;
					(*clamp_iter)->setPosition(pos);

					auto outOfBounds = windowWidth + (clamp_width / 2.0f);
					if (pos.x >= outOfBounds)
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

					auto outOfBounds = -clamp_width / 2.0f;
					if (pos.x <= outOfBounds)
					{
						clamps.erase(clamp_iter);
						return;
					}
				}
			}
			++clamp_iter;
		}
	}
}

void ClampController::animate(shared_ptr<Sprite>& _sprite, shared_ptr<Clamp>& _obj)
{
	_obj->increment_counter();
	auto counter = _obj->get_counter();
	auto [left, right] = _obj->getSide();

	if (left)
	{
		if (counter > 0 && counter <= 10)
		{
			_sprite->setTexture(clamp1_left);
		}
		else if (counter > 10 && counter <= 20)
		{
			_sprite->setTexture(clamp2_left);
		}
		else if (counter > 20 && counter <= 30)
		{
			_sprite->setTexture(clamp3_left);
		}
		else if (counter > 30 && counter <= 40)
		{
			_sprite->setTexture(clamp4_left);
		}
		else if (counter > 40 && counter <= 50)
		{
			_sprite->setTexture(clamp5_left);
		}
		else if (counter > 50 && counter <= 60)
		{
			_sprite->setTexture(clamp6_left);
		}
		else if (counter > 60 && counter <= 70)
		{
			_sprite->setTexture(clamp7_left);
		}
		else if (counter > 70 && counter <= 80)
		{
			_sprite->setTexture(clamp8_left);
		}
		else if (counter > 80 && counter <= 90)
		{
			_sprite->setTexture(clamp9_left);
		}
		else if (counter > 90 && counter <= 100)
		{
			_sprite->setTexture(clamp10_left);
			_obj->reset_counter();
			_obj->increment_cycle();
			auto cycle = _obj->get_cycle();
			if (cycle > clamp_second_cycle)
			{
				//past the last cycle of the movement pattern
				_obj->reset_cycle();//start over again
			}
		}
	}

	else if (right)
	{
		if (counter > 0 && counter <= 10)
		{
			_sprite->setTexture(clamp1_right);
		}
		else if (counter > 10 && counter <= 20)
		{
			_sprite->setTexture(clamp2_right);
		}
		else if (counter > 20 && counter <= 30)
		{
			_sprite->setTexture(clamp3_right);
		}
		else if (counter > 30 && counter <= 40)
		{
			_sprite->setTexture(clamp4_right);
		}
		else if (counter > 40 && counter <= 50)
		{
			_sprite->setTexture(clamp5_right);
		}
		else if (counter > 50 && counter <= 60)
		{
			_sprite->setTexture(clamp6_right);
		}
		else if (counter > 60 && counter <= 70)
		{
			_sprite->setTexture(clamp7_right);
		}
		else if (counter > 70 && counter <= 80)
		{
			_sprite->setTexture(clamp8_right);
		}
		else if (counter > 80 && counter <= 90)
		{
			_sprite->setTexture(clamp9_right);
		}
		else if (counter > 90 && counter <= 100)
		{
			_sprite->setTexture(clamp10_right);
			_obj->reset_counter();
			_obj->increment_cycle();
			auto cycle = _obj->get_cycle();
			if (cycle > clamp_second_cycle)
			{
				//past the last cycle of the movement pattern
				_obj->reset_cycle();//start over again
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
