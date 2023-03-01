#include "IceBlocks.h"

IceBlocks::IceBlocks():
    ice_speed{1},
    isWhite{true},
    isBlue{false},
    toLeft{false},
    toRight{false},
    level{NULL},
    IIR1{false},
    IIR2{false},
    IIR3{false},
    IIR4{false}
    {}

IceBlocks::IceBlocks(const vector2f& pos_):
    ice_speed{ 1 },
    isWhite{ true },
    isBlue{ false },
    toLeft{ false },
    toRight{ false },
    level{ NULL },
    IIR1{ false },
    IIR2{ false },
    IIR3{ false },
    IIR4{ false }
{
    pos = pos_;
}

void IceBlocks::SetIceInRegion1(const bool& isIce)
{
    IIR1 = isIce;
}

void IceBlocks::SetIceInRegion2(const bool& isIce)
{
    IIR2 = isIce;
}
void IceBlocks::SetIceInRegion3(const bool& isIce)
{
    IIR3 = isIce;
}
void IceBlocks::SetIceInRegion4(const bool& isIce)
{
    IIR4 = isIce;
}

void IceBlocks::set_position(const vector2f& position)
{
   pos = position;
}

void IceBlocks::set_to_left(const bool& ifLeft) 
{
   toLeft = ifLeft;
}

void IceBlocks::set_to_right(const bool& ifRight)
{
    toRight = ifRight;
}

std::tuple<bool, bool> IceBlocks::get_direction() const
{
    return { toLeft, toRight };
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
