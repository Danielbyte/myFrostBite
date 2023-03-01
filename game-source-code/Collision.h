#ifndef COLLISION_H
#define COLLISION_H
#include "gameConstants.h"
#include "SfmlLibrary.h"
class Collision
{
public:
    Collision();
    bool bailey_ice_collision(const vector2f&,const float&,const float&,const vector2f&,
        const float&,const float&);

    bool entity_collision(const vector2f&, const float&, const float&, const vector2f&,
        const float&, const float&);

    bool bailey_enemy_collision(const vector2f&, const float&, const float&, const vector2f&, 
        const float&,const float&);
};
#endif // COLLISION_H
