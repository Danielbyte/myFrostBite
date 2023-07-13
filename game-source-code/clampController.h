#ifndef CLAMPCONTROLLER_H
#define CLAMPCONTROLLER_H

#include "clamp.h"

enum clamp_cycles {
	clamp_first_cycle = 1,
	clamp_second_cycle = 2,
};

class ClampController
{
public:
	ClampController();
	void update_clamp(vector<shared_ptr<Clamp>>&, const float deltaTime);
	void animate(shared_ptr<Clamp>&);

	//Textures if clamp spawned from left
	Texture clamp1_left, clamp2_left, clamp3_left, clamp4_left, clamp5_left, clamp6_left,
		clamp7_left, clamp8_left, clamp9_left, clamp10_left;

	//Textures if clamp spawned from right
	Texture clamp1_right, clamp2_right, clamp3_right, clamp4_right, clamp5_right, clamp6_right,
		clamp7_right, clamp8_right, clamp9_right, clamp10_right;

	void load_tectures();
	void setMultiPlayerBounds();

private:
	float speed_controller;
	float LOutOfBounds;
	float ROutOfBounds;
	float mLOutOfBounds;
	float mROutOfBounds;
};
#endif
