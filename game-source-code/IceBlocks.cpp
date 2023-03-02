#include "IceBlocks.h"

IceBlocks::IceBlocks():
    ice_speed{1},
    level{NULL}
{
    region = IceRegion::unknown;
    direction = IceDirection::S;
    color = IceColor::White;
}

IceBlocks::IceBlocks(const vector2f& pos_):
    ice_speed{ 1 },
    level{ NULL }
{
    region = IceRegion::unknown;
    pos = pos_;
    direction = IceDirection::S;
    color = IceColor::White;
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

void IceBlocks::set_color(const IceColor& _color)
{
    color = _color;
}


IceColor IceBlocks::get_color() const
{
    return color;
}

IceRegion IceBlocks::get_region() const
{
    return region;
}
