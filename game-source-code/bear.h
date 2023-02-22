#ifndef BEAR_H
#define BEAR_H

#include "SfmlLibrary.h"
#include "gameConstants.h"
#include "bailey.h"
#include "stopwatch.h"


class Bear : public Stopwatch //Inherit from stop watch baase class
{
	// This class creates an instance of the bear object
public:
	Bear();
	vector2f get_position() const;
	void update_bear(Sprite&, const float&);
	void set_bear_direction(const Direction&);
	
	//Textures
	Texture bear_left1;
	Texture bear_left2;
	Texture bear_left3;
	Texture bear_right1;
	Texture bear_right2;
	Texture bear_right3;

private:
	vector2f bear_position;
	Direction bear_direction;
	void load_textures();
	float bear_speed;
	void animate_bear(Sprite&);
	int counter;
	void increment_counter();
	void reset_counter();
};
#endif
