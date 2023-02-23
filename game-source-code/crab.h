#ifndef CRAB_H
#define CRAB_H

#include "SfmlLibrary.h"
#include "gameConstants.h"

class Crab
{
public:
	//default constructor
	Crab(){}
	//construct a crab object with parameters
	Crab(const int&, const float&);
	vector2f get_position() const;
	void set_x_position(const float&);

private:
	vector2f pos;
};
#endif
