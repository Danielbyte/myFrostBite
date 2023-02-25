#ifndef BIRD_H
#define BIRD_H

#include "gameConstants.h"
#include "SfmlLibrary.h"

class Bird
{
public:
	Bird();
	Bird(const int&, const float&);

	vector2f get_position() const;
	void set_x_position(const float&);


private:
	vector2f pos;
	bool spawned_left;
	bool spawned_right;
};
#endif
