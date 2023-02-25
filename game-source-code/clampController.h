#ifndef CLAMPCONTROLLER_H
#define CLAMPCONTROLLER_H

#include "clamp.h"

enum cycles {
	first_cycle = 1,
	second_cycle = 2,
};

class ClampController
{
public:
	ClampController();
	void update_clamp(vector<shared_ptr<Sprite>>&, vector<shared_ptr<Clamp>>&);
	void animate(shared_ptr<Sprite>&, shared_ptr<Clamp>&);
private:
};
#endif
