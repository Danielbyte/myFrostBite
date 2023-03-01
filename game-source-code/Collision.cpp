#include "Collision.h"

Collision::Collision() {};

bool Collision::bailey_ice_collision(const vector2f& baileyPos,const vector2f& icePos)
{
    auto bottom1 = baileyPos.y + bailey_height_offset;
    auto left1 = baileyPos.x - bailey_width_offset;
    auto right1 = left1 + bailey_width;

    auto ice_pos = icePos.y;
    auto left2 = icePos.x - ice_width_offset;
    auto right2 = left2 + ice_width;
  
    if((bottom1 == ice_pos) && (right1 >= left2) && (left1 <= right2))
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
    auto left1 = Entity1Pos.x - (Entity1Width/2.0f);
    auto right1 = left1 + Entity1Width;
    auto top1 = Entity1Pos.y - (Entity1Height/2.0f);
    auto bottom1 = top1 + Entity1Height;

    auto left2 = Entity2Pos.x - (Entity2Width/2.0f);
    auto right2 = left2 + Entity2Width;
    auto top2 = Entity2Pos.y - (Entity2Height/2.0f);
    auto bottom2 = top2 + Entity2Height;

    if ( right1 > left2 && left1 < right2 && bottom1 > top2 && top1 < bottom2)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Collision::bailey_enemy_collision(const vector2f& E1_pos, const float& E1_width,
    const float& E1_height, const vector2f& E2_pos, const float& E2_width, const float& E2_height)
{
    //vertical borders of of first entity
    auto LHS1 = E1_pos.x - (E1_width / 2.0f);
    auto RHS1 = E1_pos.x + (E1_width / 2.0f);
    auto top1 = E1_pos.y - (E1_height / 2.0f);
    auto bottom1 = E1_pos.y + (E1_height / 2.0f);

    //vertical borders of second entity
    auto LHS2 = E2_pos.x - (E2_width / 2.0f);
    auto RHS2 = E2_pos.x + (E2_width / 2.0f);
    auto top2 = E2_pos.y - (E2_height / 2.0f);
    auto bottom2 = E2_pos.y + (E2_height / 2.0f);

    //collision detect
    if (RHS1 >= LHS2 && LHS1 <= RHS2 && bottom1 > top2 && top1 < top2)
    {
        return true;
    }

    else
    {
        return false;
    }

}
