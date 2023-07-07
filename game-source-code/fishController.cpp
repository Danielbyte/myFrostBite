#include "fishController.h"

FishController::FishController():
	speed_controller{90.0f}
{
	load_textures();
}

void FishController::update_fish(vector<shared_ptr<Fish>>& fish, const float deltaTime)
{
	if (!fish.empty())
	{
		auto fish_iter = fish.begin();
		//auto fish_sprite = fish_sprites.begin();

		while (fish_iter != fish.end())
		{
			auto [left, right] = (*fish_iter)->getSide();

			if (left)
			{
				//(*fish_sprite)->move(speed_controller * deltaTime, 0);
				vector2f pos = (*fish_iter)->getPosition();
				pos.x += speed_controller * deltaTime;
				(*fish_iter)->setPosition(pos);

				auto outOfBounds = windowWidth + (fish_width / 2.0f);
				if (pos.x >= outOfBounds)
				{
					fish.erase(fish_iter);
					return;
				}
			}

			else if (right)
			{
				//(*fish_sprite)->move(-speed_controller * deltaTime, 0);
				vector2f pos = (*fish_iter)->getPosition();
				pos.x -= speed_controller * deltaTime;
				(*fish_iter)->setPosition(pos);

				auto outOfBounds = -fish_width / 2.0f;
				if (pos.x <= outOfBounds)
				{
					fish.erase(fish_iter);
					return;
				}
			}
			animate(*fish_iter);
			++fish_iter;
		}
	}
}

void FishController::animate(shared_ptr<Fish>& fish)
{
	fish->increment_counter();
	auto [left, right] = fish->getSide();
	auto counter = fish->get_counter();

	if (left)
	{
		if (counter > 0 && counter <= 8)
		{
			fish->updateSpriteTexture(fish1_left);
			fish->updateSpritePosition();
		}
		else if (counter > 8 && counter <= 16)
		{
			fish->updateSpriteTexture(fish2_left);
			fish->updateSpritePosition();
		}
		else if (counter > 16 && counter <= 24)
		{
			fish->updateSpriteTexture(fish3_left);
			fish->updateSpritePosition();
		}
		else if (counter > 24 && counter <= 32)
		{
			fish->updateSpriteTexture(fish4_left);
			fish->updateSpritePosition();
		}
		else if (counter > 32 && counter <= 40)
		{
			fish->updateSpriteTexture(fish5_left);
			fish->updateSpritePosition();
			fish->reset_counter();
		}
	}

	else if (right)
	{
		if (counter > 0 && counter <= 8)
		{
			fish->updateSpriteTexture(fish1_right);
			fish->updateSpritePosition();
		}
		else if (counter > 8 && counter <= 16)
		{
			fish->updateSpriteTexture(fish2_right);
			fish->updateSpritePosition();
		}
		else if (counter > 16 && counter <= 24)
		{
			fish->updateSpriteTexture(fish3_right);
			fish->updateSpritePosition();
		}
		else if (counter > 24 && counter <= 32)
		{
			fish->updateSpriteTexture(fish4_right);
			fish->updateSpritePosition();
		}
		else if (counter > 32 && counter <= 40)
		{
			fish->updateSpriteTexture(fish5_right);
			fish->updateSpritePosition();
			fish->reset_counter();
		}
	}
}

void FishController::load_textures()
{
	//load texture for fish spawned on the left
	fish1_left.loadFromFile("resources/fish1_left.png");
	fish2_left.loadFromFile("resources/fish2_left.png");
	fish3_left.loadFromFile("resources/fish3_left.png");
	fish4_left.loadFromFile("resources/fish4_left.png");
	fish5_left.loadFromFile("resources/fish5_left.png");

	//load texture for fish spawned on the right
	fish1_right.loadFromFile("resources/fish1_right.png");
	fish2_right.loadFromFile("resources/fish2_right.png");
	fish3_right.loadFromFile("resources/fish3_right.png");
	fish4_right.loadFromFile("resources/fish4_right.png");
	fish5_right.loadFromFile("resources/fish5_right.png");

}