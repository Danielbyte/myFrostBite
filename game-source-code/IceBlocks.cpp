#include "IceBlocks.h"

IceBlocks::IceBlocks():
    ice_speed{1},
    isWhite{true},
    isBlue{false},
    isLeft{false},
    level{NULL}
    {}

void IceBlocks::set_position(vector2f position) {
pos = position;
return;
}

void IceBlocks::set_if_left(bool ifLeft) {
isLeft = ifLeft;
}

bool IceBlocks::get_if_left() const {
return isLeft;
}

vector2f IceBlocks::get_position() const
{
    return pos;
}

void IceBlocks::set_level(int level_)
{
    level = level_;
}

float IceBlocks::get_ice_speed() const
{
    return ice_speed;
}

int IceBlocks::get_ice_level() const
{
    return level;
}

void IceBlocks::set_to_blue(bool ifBlue) {
isBlue = ifBlue;
}

bool IceBlocks::get_if_blue() const
{
    return isBlue;
}

void IceBlocks::set_to_white(bool ifWhite)
{
    isWhite = ifWhite;
}

bool IceBlocks::get_if_white() const
{
    return isWhite;
}
