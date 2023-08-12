#ifndef BIRDCONTROLLER_H
#define BIRDCONTROLLER_H

#include "bird.h"

class BirdController
{
public:
	BirdController();

	//Bird Textures
	//Textures when bird spawned on the left
	Texture bird1_left, bird2_left, bird3_left, bird4_left, bird5_left, bird6_left;
	//Textures when bird spawned on the right
	Texture bird1_right, bird2_right, bird3_right, bird4_right, bird5_right, bird6_right;
	void load_textures();

	void update_birds(vector<shared_ptr<Bird>>&, const float deltaTime);
	void animate(shared_ptr<Bird>&);
	void setMultiPlayerBounds();

private:
	float speed_controller;
	float LOutOfBounds;
	float ROutOfBounds;
	float mLOutOfBounds;
	float mROutOfBounds;
};
#endif
