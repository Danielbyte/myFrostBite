#ifndef CLAMP_H
#define CLAMP_H

#include "gameConstants.h"
#include "SfmlLibrary.h"
#include "Animal.h"

class Clamp : public Animal
{
public:
	Clamp();
	Clamp(const int side, const float region, bool isMultiPlayer);
	void set_x_position(const float& _x);

	void increment_counter();
	void reset_counter();
	int get_counter() const;

	void reset_cycle();
	void increment_cycle();
	int get_cycle() const;

private:
	//animation of clamp entity
	int counter;
	int cycle;
	float rightP;
	float leftP;
	float mRightP;
	float mLeftP;
};
#endif
