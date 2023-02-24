#ifndef FISH_H
#define FISH_H

#include "gameConstants.h"
#include "SfmlLibrary.h"

class Fish
{
public:
	Fish(){}
	Fish(const int&, const float&);
	vector2f get_position() const;
	void set_x_position(const float&);
private:
	vector2f pos;
};
#endif

