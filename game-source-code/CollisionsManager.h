#pragma once
#ifndef COLLISIONSMANAGER_H
#define COLLISIONSMANAGER_H

#include "Collision.h"
#include "Player.h"
#include "IceBlocks.h"
#include "crab.h"
#include "clamp.h"
#include "bird.h"
#include "fish.h"
#include "igloo.h"

class CollisionsManager
{
public:
	CollisionsManager();
	void player_ice_collisions(Player& player, vector<shared_ptr<IceBlocks>>& ice,const float deltaTime,
	shared_ptr<Igloo>& igloo);
	void player_animal_collisions(Player& player, vector<shared_ptr<Crab>>&, vector<shared_ptr<Clamp>>&,
		vector<shared_ptr<Bird>>&, vector<shared_ptr<Fish>>&);
	//void region_collisions(Player& player,vector<shared_ptr<Animal>>& _animal, float width, float height);
	void setPlayerToMoveWithIce(Player& player, const IceDirection& ice_dir, const float& deltaTime);
	void check_player_on_ice_patch(shared_ptr<IceBlocks>& ice_ptr, Player& player);
	void update_other_ice(const IceRegion region, const IceColor color,vector<shared_ptr<IceBlocks>>& ice);
	void reverse_ice_direction(vector<shared_ptr<IceBlocks>>& ice, shared_ptr<IceBlocks>& ice_ptr);

private:
	int NOBI; //Number Of Blue Ice blocks
	Collision collision;
	void set_all_ice_to_white(vector<shared_ptr<IceBlocks>>& ice);
	void set_all_ice_to_blue(vector<shared_ptr<IceBlocks>>& ice);
	void updateOtherIceToChangeDirection(const IceRegion& region, const IceDirection& direction,
		vector<shared_ptr<IceBlocks>>& ice);
	bool playerCollidedWithAnimal;

	template<typename _Animal>
	void region_collisions(Player& player, vector<shared_ptr<_Animal>>& _animal, float _width, float _height,
		bool isFish)
	{
		auto animal_iter = _animal.begin();
		while (animal_iter != _animal.end())
		{
			auto animal_pos = (*animal_iter)->getPosition();
			vector2f player_pos;
			player_pos = player.getPosition();
			auto isCollided = collision.bailey_enemy_collision(animal_pos, _width, _height, player_pos,
				bailey_width, bailey_height);

			if (isCollided)
			{
				playerCollidedWithAnimal = true;

				if (isFish)
				{
					playerCollidedWithAnimal = false;
					_animal.erase(animal_iter);
					return;
				}
			}
			++animal_iter;
		}
	}
};

#endif // !COLLISIONSMANAGER_H


