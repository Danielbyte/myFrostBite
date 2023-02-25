#ifndef CLAMP_H
#define CLAMP_H

#include "gameConstants.h"
#include "SfmlLibrary.h"

class Clamp
{
public:
	Clamp();
	Clamp(const int&, const float&);
	void set_x_position(const float& _x);
	vector2f get_position() const;
	std::tuple<bool, bool> get_side();

	void increment_counter();
	void reset_counter();
	int get_counter() const;

	void reset_cycle();
	void increment_cycle();
	int get_cycle() const;

private:
	vector2f pos;

	//animation of clamp entity
	int counter;
	int cycle;

	//mark initial side of clamp object
	bool spawned_left;
	bool spawned_right;
};
#endif
