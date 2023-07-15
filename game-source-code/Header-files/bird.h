#ifndef BIRD_H
#define BIRD_H

#include "gameConstants.h"
#include "SfmlLibrary.h"
#include "Animal.h"

class Bird : public Animal
{
public:
	Bird();
	Bird(const int side, const float region, bool isMultiplayer);

	void set_x_position(const float&);
	
	void increment_counter();
	void reset_counter();
	int get_counter() const;

private:
	int counter;
	float rightP;
	float leftP;
	float mRightP;
	float mLeftP;
};
#endif
