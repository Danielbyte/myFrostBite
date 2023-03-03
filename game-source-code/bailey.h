#ifndef BAILEY_H
#define BAILEY_H
#include "gameConstants.h"
#include "SfmlLibrary.h"
#include <cstdlib>

enum class BaileyRegion { region1, region2, region3, region4, unknown };

class Bailey {
public:
    Bailey();
    void setBaileyToMoveWithIce(const Direction&, Sprite&, const float&);
    float get_Xpos();
    float get_Ypos();
    bool is_bailey_moving() const;
    bool get_if_bailey_in_safe_zone();

    void setXposition(const float&);

    bool get_is_moving_up() const;
    bool get_is_moving_down() const;

    bool get_if_bailey_dead() const;
    void set_bailey_to_dead(const bool&);

    bool get_if_moving_right() const;
    bool get_if_moving_left() const;

    bool get_if_right_key_pressed() const;
    bool get_if_left_key_pressed() const;

    float get_bailey_mass() const;
    float get_speed() const;
    void set_speed(const float&);
    float get_jump_force() const;
    float get_up_jumping_force() const;

    void jump_down(Sprite&, const float&, const float&, bool&, bool&);
    void jump_up(Sprite&, const float&, const float&, bool&,bool&);

    void move_bailey(const float&, Sprite&);
    bool isBaileyJumping() const;

    float get_left_boundary() const;
    float get_right_boundary() const;

    BaileyRegion get_bailey_region() const;
    void update_bailey_region();
    void setSpeedToZero();
    void turnGravityOff();
    float get_gravity() const;

private:
    void calibrate(const float&);
    float distance_between_iceRows;
    float y_position;
    float x_position;
    float lower_boundary;
    float left_boundary;
    float right_boundary;

    bool safe_zone;
    float safe_zone_boundary;

    //see if bailey is moving or not
    bool is_moving;

    bool isMovingUp;
    bool isMovingDown;

    bool is_dead;
    bool isMovingRight;
    bool isMovingLeft;
    bool RightKeyPressed;
    bool LeftKeyPressed;

    float bailey_mass;
    float gravity;
    float jumpForce;
    float left_right_const;
    float speed;
    float upJumpingForce;
    float ice_speed;
    float speed_attenuater;
    float upJump_speedAtten; //control the speed at which frostbite jumps up
    bool is_bailey_jumping;

    //regions
    BaileyRegion bailey_region;
    float Region1;
    float Region2;
    float Region3;
    float Region4;
};
#endif // BAILEY_H
