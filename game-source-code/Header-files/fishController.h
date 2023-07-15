#ifndef FISHCONTROLLER_H
#define FISHCONTROLLER_H

#include "fish.h"

class FishController
{
public:
	FishController();
	void update_fish(vector<shared_ptr<Fish>>&, const float deltaTime);
	void animate(shared_ptr<Fish>&);

	Texture fish1_left, fish2_left, fish3_left, fish4_left, fish5_left;
	Texture fish1_right, fish2_right, fish3_right, fish4_right, fish5_right;
	void load_textures();
	void setMultiplayerBounds();

private:
	float speed_controller;
	float LoutOfBounds;
	float RoutOfBounds;
	float mLOutOfBounds; //multiplayer boundary
	float mROutOfBounds;
};
#endif
