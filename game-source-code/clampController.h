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
	void update_clamp(vector<shared_ptr<Sprite>>&, vector<shared_ptr<Clamp>>&, const float&);
	void animate(shared_ptr<Sprite>&, shared_ptr<Clamp>&);

	Texture clamp1_left, clamp2_left, clamp3_left, clamp4_left, clamp5_left, clamp6_left,
		clamp7_left, clamp8_left, clamp9_left, clamp10_left;
	void load_tectures();

private:
	float speed_controller;
};
#endif
