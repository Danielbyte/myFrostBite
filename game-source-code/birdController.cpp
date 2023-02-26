#include "birdController.h"

BirdController::BirdController():
	speed_controller{100.0f}
{
	load_textures();
}

void BirdController::update_birds(vector<shared_ptr<Sprite>>& bird_sprites,
	vector<shared_ptr<Bird>>& bird_objects, const float& deltaTime)
{
	if (!bird_objects.empty())
	{
		auto bird_obj = bird_objects.begin();
		auto bird_sprite = bird_sprites.begin();

		while (bird_obj != bird_objects.end())
		{
			animate(*bird_sprite, *bird_obj);
			auto [left, right] = (*bird_obj)->get_side();

			if (left)
			{
				(*bird_sprite)->move(speed_controller * deltaTime, 0);
				vector2f pos = (*bird_sprite)->getPosition();
				(*bird_obj)->set_position(pos);

				//delete bird if it has travelled past the screen
				auto outOfBounds = windowWidth + (bird_width / 2.0f);
				if (pos.x >= outOfBounds)
				{
					//delete bird object
					bird_objects.erase(bird_obj);
					bird_sprites.erase(bird_sprite);
					return;
				}
			}

			else if (right)
			{
				(*bird_sprite)->move(-speed_controller * deltaTime, 0);
				vector2f pos = (*bird_sprite)->getPosition();
				(*bird_obj)->set_position(pos);

				//delete bird if it has travelled past the screen
				auto outOfBounds = -bird_width / 2.0f;
				if (pos.x <= outOfBounds)
				{
					//delete bird object
					bird_objects.erase(bird_obj);
					bird_sprites.erase(bird_sprite);
					std::cout << "Deleted" << std::endl;
					return;
				}
			}

			++bird_obj;
			++bird_sprite;
		}
	}
}

void BirdController::load_textures()
{
	//load left bird textures
	bird1_left.loadFromFile("resources/bird1_left.png");
	bird2_left.loadFromFile("resources/bird2_left.png");
	bird3_left.loadFromFile("resources/bird3_left.png");
	bird4_left.loadFromFile("resources/bird4_left.png");
	bird5_left.loadFromFile("resources/bird5_left.png");
	bird6_left.loadFromFile("resources/bird6_left.png");

	//load right bird textures
	bird1_right.loadFromFile("resources/bird1_right.png");
	bird2_right.loadFromFile("resources/bird2_right.png");
	bird3_right.loadFromFile("resources/bird3_right.png");
	bird4_right.loadFromFile("resources/bird4_right.png");
	bird5_right.loadFromFile("resources/bird5_right.png");
	bird6_right.loadFromFile("resources/bird6_right.png");
}

void BirdController::animate(shared_ptr<Sprite>& bird_sprite, shared_ptr<Bird>& birdObj)
{
	birdObj->increment_counter();
	auto [left, right] = birdObj->get_side();
	auto counter = birdObj->get_counter();

	if (left)
	{
		if (counter > 0 && counter <= 8)
		{
			bird_sprite->setTexture(bird1_left);
		}
		else if (counter > 8 && counter <= 16)
		{
			bird_sprite->setTexture(bird2_left);
		}
		else if (counter > 16 && counter <= 24)
		{
			bird_sprite->setTexture(bird3_left);
		}
		else if (counter > 24 && counter <= 32)
		{
			bird_sprite->setTexture(bird4_left);
		}
		else if (counter > 32 && counter <= 40)
		{
			bird_sprite->setTexture(bird5_left);
		}

		else if (counter > 40 && counter <= 48)
		{
			bird_sprite->setTexture(bird6_left);
			birdObj->reset_counter();
		}
	}

	else if (right)
	{
		if (counter > 0 && counter <= 8)
		{
			bird_sprite->setTexture(bird1_right);
		}
		else if (counter > 8 && counter <= 16)
		{
			bird_sprite->setTexture(bird2_right);
		}
		else if (counter > 16 && counter <= 24)
		{
			bird_sprite->setTexture(bird3_right);
		}
		else if (counter > 24 && counter <= 32)
		{
			bird_sprite->setTexture(bird4_right);
		}
		else if (counter > 32 && counter <= 40)
		{
			bird_sprite->setTexture(bird5_right);
		}
		else if (counter > 40 && counter <= 48)
		{
			bird_sprite->setTexture(bird6_right);
			birdObj->reset_counter();
		}
	}
}
