#ifndef FISH_H
#define FISH_H

#include "gameConstants.h"
#include "Animal.h"


class Fish :public Animal
{
public:
	Fish();
	Fish(const int&, const float&);

	void set_x_position(const float&);
	void increment_counter();
	void reset_counter();
	int get_counter() const;

private:
	int counter;
};
#endif

