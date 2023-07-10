#ifndef ANIMATEPLAYER_H
#define ANIAMATEPLAYER_H

#include "Player.h"

class AnimatePlayer
{
public:
	AnimatePlayer();
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

	//Textures when bailey runs out of time and is frozen.
	Texture freeze1, freeze2, freeze3, freeze4, freeze5, freeze6, freeze7, freeze8, freeze9, freeze10
		, freeze11, freeze12, freeze13, freeze14, freeze15, freeze16;

	//Textures when bailey runs into the igloo house
	Texture enterIgloo1, enterIgloo2, enterIgloo3, enterIgloo4;

	int get_frame() const;
	void animate_player(Player&);
	void killed_by_bear(const float&, Player& player); //when frostbite collides with bear
	void drowning_player(const float deltaTime, Player& player);
	void collision_with_sea_animal(const float&, Player&);
	void freezing_animation(const float&, Sprite&);
	void go_inside_igloo(const float&, Player& player);
	void load_textures();

private:
	void increment_frame();
	void reset_frame();
	int frame_counter;
	bool isBaileyMoving;
	float drowningTimePerFrame; //constant to time the animation of drowning frostbite
	float CWSCTPF;//CWSCTPF->Collission With Sea Creature Time Per Frame
	float freezingFrameTime;
};
#endif

