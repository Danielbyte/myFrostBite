#ifndef ICEBLOCKS_H
#define ICEBLOCKS_H
#include "SfmlLibrary.h"
#include "gameConstants.h"

enum class IceRegion { R1, R2, R3, R4, unknown }; //Regions of ice
enum class IceDirection { L, R }; //L->left, R->right

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
    void set_direction(const IceDirection&);
    IceDirection get_direction() const;
    bool get_if_blue() const;
    bool get_if_white() const;
    void set_level(int);
    int get_ice_level() const;

    IceRegion get_region() const;
    void set_region(const IceRegion&);

private:
    float ice_speed;
    vector2f pos;
    bool isWhite;
    bool isBlue;
    int level;

    //marks if there is ice in different regions
    IceRegion region;

    //marks the directionof ice
    IceDirection direction;
};
#endif // ICEBLOCKS_H
