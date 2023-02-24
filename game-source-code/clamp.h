#ifndef CLAMP_H
#define CLAMP_H

#include "gameConstants.h"
#include "SfmlLibrary.h"

class Clamp
{
public:
	Clamp() {}
	Clamp(const int&, const float&);
	void set_x_position(const float& _x);
	vector2f get_position() const;

private:
	vector2f pos;
};
#endif
