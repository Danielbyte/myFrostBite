#ifndef ICEBLOCKS_H
#define ICEBLOCKS_H
#include "SfmlLibrary.h"
#include "gameConstants.h"

class IceBlocks {
public:
    IceBlocks();
    //Set ice block movements
    void move_left();
    void move_right();
    //get ice block movements
    vector2f get_position() const;

    //change ice block to blue if it has been jumped on
    void set_to_white(bool);
    void set_to_blue(bool);

    //get color of ice
    string get_ice_block_color() const;

    //get ice_speed
    float get_ice_speed() const;

    void set_position(vector2f);
    void set_if_left(bool);
    bool get_if_left() const;
    bool get_if_blue() const;
    bool get_if_white() const;
    void set_level(int);
    int get_ice_level() const;

private:
    float ice_speed;
    vector2f pos;
    bool isWhite;
    bool isBlue;
    bool isLeft;
    int level;
};
#endif // ICEBLOCKS_H
