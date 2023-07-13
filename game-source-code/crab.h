#ifndef CRAB_H
#define CRAB_H

#include "gameConstants.h"
#include "Animal.h"

class Crab : public Animal
{
public:
	//default constructor
	Crab();
	//construct a crab object with parameters
	Crab(const int side, const float region, bool isMultiplayer);
	void set_x_position(const float&);

	//for animating crabs
	void reset_counter();
	void increment_counter();
	int get_counter() const;
	void increment_cycle();
	int get_cycle() const;
	void reset_cycle();

private:
	int counter;
	int cycle;
	float rightP;
	float leftP;
	float mRightP;
	float mLeftP;
};
#endif
