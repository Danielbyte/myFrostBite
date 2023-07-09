#ifndef BEAR_H
#define BEAR_H

#include "SfmlLibrary.h"
#include "gameConstants.h"
#include "Player.h"
#include "stopwatch.h"


class Bear : public Stopwatch //Inherit from stop watch baase class
{
	// This class creates an instance of the bear object
public:
	Bear();
	vector2f get_position() const;
	void update_bear(const float deltaTime, Player& player);
	void set_bear_direction(const Direction&);
	Sprite getSprite() const;
	
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
	void animate_bear();
	int counter;
	void increment_counter();
	void reset_counter();
	Sprite bear_sprite;
	void set_to_track_player(Player& player);
};
#endif
