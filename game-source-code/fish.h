#ifndef FISH_H
#define FISH_H

#include "gameConstants.h"
#include "SfmlLibrary.h"


class Fish
{
public:
	Fish();
	Fish(const int&, const float&);
	vector2f get_position() const;
	void set_x_position(const float&);
	std::tuple<bool, bool>get_side();
	void set_position(const vector2f&);

	void increment_counter();
	void reset_counter();
	int get_counter() const;

private:
	vector2f pos;
	bool spawned_left;
	bool spawned_right;
	int counter;
};
#endif

