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
	void setBaileyToMoveWithIce(Player& player, const IceDirection& ice_dir, const float& deltaTime);
private:
	int NOBI; //Number Of Blue Ice blocks
	Collision collision;
};

#endif // !COLLISIONSMANAGER_H


