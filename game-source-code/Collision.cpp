#include "Collision.h"

Collision::Collision() {};

bool Collision::bailey_ice_collision(vector2f Entity1Pos,float Entity1Width, float Entity1Height,
                                 vector2f Entity2Pos,float Entity2Width, float Entity2Height)
{
    auto left_1 = Entity1Pos.x;
    auto right_1 = left_1 + Entity1Width;
    auto top1 = Entity1Pos.y;
    auto bottom1 = top1 + Entity1Height;

    auto left_2 = Entity2Pos.x;
    auto right_2 = left_2 + Entity2Width;
    auto top2 = Entity2Pos.y;
    //auto bottom2 = top2+Entity2Width;
 //bottom1 > top2 && ((left_1>=left_2 && left_1 <= right_2) || (right_1>= left_2 && right_1 <= right_2))
    if(right_1>left_2 && left_1<right_2 && bottom1 == top2+ice_height_offset /*&& top1<bottom2*/)
    {
        return true;
    } else {
        return false;
    }
}
