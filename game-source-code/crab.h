#ifndef CRAB_H
#define CRAB_H

#include "SfmlLibrary.h"
#include "gameConstants.h"

class Crab
{
public:
	//default constructor
	Crab() {}
	//construct a crab object with parameters
	Crab(const int&, const float&);
	vector2f get_position() const;
	void set_x_position(const float&);

	//for animating crabs
	void reset_counter();
	void increment_counter();
	int get_counter() const;
	void increment_cycle();
	int get_cycle() const;
	void reset_cycle();

private:
	vector2f pos;
	int counter;
	int cycle;
};
#endif
