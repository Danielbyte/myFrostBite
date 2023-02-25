#include "clampController.h"

ClampController::ClampController() {}

void ClampController::update_clamp(vector<shared_ptr<Sprite>>& clamp_sprites,
	vector<shared_ptr<Clamp>>& clampObj)
{
	if (!clampObj.empty())
	{
		auto sprite_ptr = clamp_sprites.begin();
		auto obj_ptr = clampObj.begin();

		while (obj_ptr != clampObj.end())
		{
			++obj_ptr;
			++sprite_ptr;
		}
	}
}
