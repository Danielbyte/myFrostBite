#include "fishController.h"

FishController::FishController()
{
	load_textures();
}

void FishController::update_fish(vector<shared_ptr<Sprite>>& fish_sprites,
	vector<shared_ptr<Fish>>& fish_objects, const float& deltaTime)
{

}

void FishController::animate(shared_ptr<Sprite>& sprite_ptr, shared_ptr<Fish>& fishObj)
{

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