#ifndef ANIMATEPLAYER_H
#define ANIAMATEPLAYER_H

#include "OverWorld.h"
#include "bear.h"

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
	void killed_by_bear(Player&, vector<shared_ptr<Crab>>&, vector<shared_ptr<Clamp>>&,
		vector<shared_ptr<Bird>>&, shared_ptr<Bear>&, vector<shared_ptr<IceBlocks>>&, bool& createIce); //when frostbite collides with bear

	void drowning_player(Player&, vector<shared_ptr<Crab>>&, vector<shared_ptr<Clamp>>&,
		vector<shared_ptr<Bird>>&, shared_ptr<Bear>&, vector<shared_ptr<IceBlocks>>&, bool& createIce);

	void collision_with_sea_animal(Player&, vector<shared_ptr<Crab>>&, vector<shared_ptr<Clamp>>&,
		vector<shared_ptr<Bird>>&, shared_ptr<Bear>&, vector<shared_ptr<IceBlocks>>&, bool& createIce);

	void freezing_animation(Player&, vector<shared_ptr<Crab>>&, vector<shared_ptr<Clamp>>&,
		vector<shared_ptr<Bird>>&, shared_ptr<Bear>&, vector<shared_ptr<IceBlocks>>&, bool& createIce,
		OverWorld& _overworld);

	void go_inside_igloo(Player& player, shared_ptr<Igloo>& _igloo);

	void load_textures();

	void animateAndSetState(Player&, vector<shared_ptr<Crab>>&, vector<shared_ptr<Clamp>>&,
		vector<shared_ptr<Bird>>&, shared_ptr<Bear>&, vector<shared_ptr<IceBlocks>>&, bool& createIce,
		OverWorld& _overworld, shared_ptr<Igloo>& igloo);

private:
	void increment_frame();
	void reset_frame();
	int frame_counter;
	bool isBaileyMoving;
	float drowningTimePerFrame; //constant to time the animation of drowning frostbite
	float CWSCTPF;//CWSCTPF->Collission With Sea Creature Time Per Frame
	float freezingFrameTime;
	float standardAnimDur;
	float freezeAnimDur;
	void movePlayerTowardsDoor(Player& player, shared_ptr<Igloo>& _igloo);
};
#endif

