#ifndef ICEBLOCKS_H
#define ICEBLOCKS_H
#include "SfmlLibrary.h"
#include "gameConstants.h"

class IceBlocks {
public:
    IceBlocks();
    IceBlocks(const vector2f&);
    vector2f get_position() const;

    //change ice block to blue if it has been jumped on
    void set_to_white(bool);
    void set_to_blue(bool);

    //get color of ice
    //string get_ice_block_color() const;

    //get ice_speed
    float get_ice_speed() const;

    void set_position(const vector2f&);
    void set_to_left(const bool&);
    void set_to_right(const bool&);
    std::tuple<bool, bool> get_direction() const;
    bool get_if_blue() const;
    bool get_if_white() const;
    void set_level(int);
    int get_ice_level() const;

    std::tuple<bool, bool, bool, bool> ice_in_regions();
    void SetIceInRegion1(const bool&);
    void SetIceInRegion2(const bool&);
    void SetIceInRegion3(const bool&);
    void SetIceInRegion4(const bool&);

private:
    float ice_speed;
    vector2f pos;
    bool isWhite;
    bool isBlue;
    bool toLeft;
    bool toRight;
    int level;

    //marks if there is ice in different regions
    bool IIR1, IIR2, IIR3, IIR4; //IIR -> Ice In Region
};
#endif // ICEBLOCKS_H
