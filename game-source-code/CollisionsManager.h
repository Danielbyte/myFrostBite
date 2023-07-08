#pragma once
#ifndef COLLISIONSMANAGER_H
#define COLLISIONSMANAGER_H

#include "Collision.h"
#include "Player.h"
#include "IceBlocks.h"

class CollisionsManager
{
public:
	CollisionsManager();
	void player_ice_collisions(Player& player, vector<shared_ptr<IceBlocks>>& ice,const float deltaTime);
	void setPlayerToMoveWithIce(Player& player, const IceDirection& ice_dir, const float& deltaTime);
	void check_player_on_ice_patch(shared_ptr<IceBlocks>& ice_ptr, Player& player);
	void update_other_ice(const IceRegion region, const IceColor color, vector<shared_ptr<IceBlocks>>& ice);
private:
	int NOBI; //Number Of Blue Ice blocks
	Collision collision;
	void set_all_ice_to_white(vector<shared_ptr<IceBlocks>>& ice);
};

#endif // !COLLISIONSMANAGER_H


