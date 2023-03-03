#ifndef BAILEYCONTROLLER_H
#define BAILEYCONTROLLER_H

#include "bailey.h"

class BaileyController
{
public:
	BaileyController();
	//~BaileyController();
	Texture bailey_texture1;
	Texture bailey_texture2;
	Texture bailey_texture3;
	Texture bailey_texture4;
	Texture bailey_texture5;
	Texture bailey_texture6;

	//Textures for when bailey dies due to bear
	Texture death1_bailey, death2_bailey, death3_bailey, death4_bailey, death5_bailey, death6_bailey,
		death7_bailey, death8_bailey, death9_bailey, death10_bailey, death11_bailey, death12_bailey,
		death13_bailey, death14_bailey;

	//Textures when bailey drowns
	Texture drown1, drown2, drown3, drown4, drown5, drown6, drown7, drown8, drown9, drown10, drown11,
		drown12, drown13, drown14, drown15, drown16, drown17;

	//Textures when bailey collides with sea animal
	Texture die1, die2, die3, die4, die5, die6;

	int get_frame() const;
	void update_bailey(vector2f&,bool&, const float&, const float&);
	void animate_bailey(Bailey&, Sprite&);
	void bailey_death(const float&, Sprite&); //when frostbite collides with bear
	void drowning_bailey(const float&, Sprite&);
	void collision_with_sea_animal(const float&, Sprite&);
	void load_textures();

private:
	void increment_frame();
	void reset_frame();
	int frame_counter;
	bool isBaileyMoving;
	float drowningTimePerFrame; //constant to time the animation of drowning frostbite
	float CWSCTPF;//CWSCTPF->Collission With Sea Creature Time Per Frame
};
#endif

