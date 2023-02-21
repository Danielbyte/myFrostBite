#include "Collision.h"

Collision::Collision() {};

bool Collision::bailey_ice_collision(const vector2f& Entity1Pos,const float& Entity1Width,
    const float& Entity1Height,const vector2f& Entity2Pos,
    const float& Entity2Width,const  float& Entity2Height)
{
    auto left_1 = Entity1Pos.x;
    auto right_1 = left_1 + Entity1Width;
    auto top1 = Entity1Pos.y;
    auto bottom1 = top1 + Entity1Height;

    auto left_2 = Entity2Pos.x;
    auto right_2 = left_2 + Entity2Width;
    auto top2 = Entity2Pos.y;
  
    if(right_1>left_2 && left_1<right_2 && bottom1 == top2+ice_height_offset)
    {
        return true;
    } else {
        return false;
    }
}

bool Collision::entity_collision(const vector2f& Entity1Pos, const float& Entity1Width,
    const float& Entity1Height, const vector2f& Entity2Pos,
    const float& Entity2Width, const  float& Entity2Height)
{
    auto left1 = Entity1Pos.x;
    auto right1 = left1 + Entity1Width;
    auto top1 = Entity1Pos.y;
    auto bottom1 = top1 + Entity1Height;

    auto left2 = Entity2Pos.x;
    auto right2 = left2 + Entity2Width;
    auto top2 = Entity2Pos.y;
    auto bottom2 = top2 + Entity2Height;

    if ((right1 >= left2 && left1 <= right2) && (bottom1 >= top2 && top1 <= bottom2))
    {
        return true;
    }
    else
    {
        return false;
    }
}
