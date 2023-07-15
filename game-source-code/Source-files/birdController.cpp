#include "../Header-files/birdController.h"

BirdController::BirdController():
	speed_controller{100.0f},
	LOutOfBounds{819.0f},
	ROutOfBounds{-19.0f},
	mLOutOfBounds{620.473f},
	mROutOfBounds{110.0f}
{
	load_textures();
}

void BirdController::update_birds(vector<shared_ptr<Bird>>& birds, const float deltaTime)
{
	if (!birds.empty())
	{
		auto bird_iter = birds.begin();
		//auto bird_sprite = bird_sprites.begin();

		while (bird_iter != birds.end())
		{
			auto [left, right] = (*bird_iter)->getSide();

			if (left)
			{
				//(*bird_sprite)->move(speed_controller * deltaTime, 0);
				vector2f pos = (*bird_iter)->getPosition();
				pos.x  += speed_controller * deltaTime;
				(*bird_iter)->setPosition(pos);

				//delete bird if it has travelled past the screen
				if (pos.x >= LOutOfBounds)
				{
					//delete bird object
					birds.erase(bird_iter);
					return;
				}
			}

			else if (right)
			{
				vector2f pos = (*bird_iter)->getPosition();
				pos.x -= speed_controller * deltaTime;
				(*bird_iter)->setPosition(pos);

				//delete bird if it has travelled past the screen
				if (pos.x <= ROutOfBounds)
				{
					//delete bird object
					birds.erase(bird_iter);
					return;
				}
			}
			animate(*bird_iter);
			++bird_iter;
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

void BirdController::animate(shared_ptr<Bird>& bird)
{
	bird->increment_counter();
	auto [left, right] = bird->getSide();
	auto counter = bird->get_counter();

	if (left)
	{
		if (counter > 0 && counter <= 8)
		{
			bird->updateSpriteTexture(bird1_left);
			bird->updateSpritePosition();
		}
		else if (counter > 8 && counter <= 16)
		{
			bird->updateSpriteTexture(bird2_left);
			bird->updateSpritePosition();
		}
		else if (counter > 16 && counter <= 24)
		{
			bird->updateSpriteTexture(bird3_left);
			bird->updateSpritePosition();
		}
		else if (counter > 24 && counter <= 32)
		{
			bird->updateSpriteTexture(bird4_left);
			bird->updateSpritePosition();
		}
		else if (counter > 32 && counter <= 40)
		{
			bird->updateSpriteTexture(bird5_left);
			bird->updateSpritePosition();
		}

		else if (counter > 40 && counter <= 48)
		{
			bird->updateSpriteTexture(bird6_left);
			bird->updateSpritePosition();
			bird->reset_counter();
		}
	}

	else if (right)
	{
		if (counter > 0 && counter <= 8)
		{
			bird->updateSpriteTexture(bird1_right);
			bird->updateSpritePosition();
		}
		else if (counter > 8 && counter <= 16)
		{
			bird->updateSpriteTexture(bird2_right);
			bird->updateSpritePosition();
		}
		else if (counter > 16 && counter <= 24)
		{
			bird->updateSpriteTexture(bird3_right);
			bird->updateSpritePosition();
		}
		else if (counter > 24 && counter <= 32)
		{
			bird->updateSpriteTexture(bird4_right);
			bird->updateSpritePosition();
		}
		else if (counter > 32 && counter <= 40)
		{
			bird->updateSpriteTexture(bird5_right);
			bird->updateSpritePosition();
		}
		else if (counter > 40 && counter <= 48)
		{
			bird->updateSpriteTexture(bird6_right);
			bird->updateSpritePosition();
			bird->reset_counter();
		}
	}
}

void BirdController::setMultiPlayerBounds()
{
	LOutOfBounds = mLOutOfBounds;
	ROutOfBounds = mROutOfBounds;
}
