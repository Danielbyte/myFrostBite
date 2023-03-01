#include "IceBlocks.h"

IceBlocks::IceBlocks():
    ice_speed{1},
    isWhite{true},
    isBlue{false},
    level{NULL}
{
    region = IceRegion::unknown;
}

IceBlocks::IceBlocks(const vector2f& pos_):
    ice_speed{ 1 },
    isWhite{ true },
    isBlue{ false },
    level{ NULL }
{
    region = IceRegion::unknown;
    pos = pos_;
}

void IceBlocks::set_region(const IceRegion& _region)
{
    region = _region;
}

void IceBlocks::set_position(const vector2f& position)
{
   pos = position;
}

IceDirection IceBlocks::get_direction() const
{
    return direction;
}

void IceBlocks::set_direction(const IceDirection& dir)
{
    direction = dir;
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

IceRegion IceBlocks::get_region() const
{
    return region;
}
