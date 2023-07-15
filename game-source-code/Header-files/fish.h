#ifndef FISH_H
#define FISH_H

#include "gameConstants.h"
#include "Animal.h"


class Fish :public Animal
{
public:
	Fish();
	Fish(const int side, const float region, bool isMultiPlayer);

	void set_x_position(const float&);
	void increment_counter();
	void reset_counter();
	int get_counter() const;

private:
	int counter;
	float RinitPosition;
	float LinitPosition;
	float mRInitPosition;
	float mLInitPosition;
};
#endif

