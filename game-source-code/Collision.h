#ifndef COLLISION_H
#define COLLISION_H
#include "gameConstants.h"
#include "SfmlLibrary.h"
class Collision
{
public:
    Collision();
    bool bailey_ice_collision(vector2f,float,float,vector2f,float,float);
};
#endif // COLLISION_H
