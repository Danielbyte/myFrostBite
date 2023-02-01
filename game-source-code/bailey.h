#ifndef BAILEY_H
#define BAILEY_H
#include "gameConstants.h"
#include "SfmlLibrary.h"
#include <cstdlib>

class Bailey {
public:
    Bailey();
    void set_bailey_movement(const Direction&, const float&, const bool&, Sprite&,const float&);
    float get_Xpos();
    float get_Ypos();
    bool is_bailey_moving() const;
    float getbailey_speed() const;
    bool get_if_bailey_in_safe_zone();

    int get_bailey_level();

    bool get_is_moving_up() const;
    bool get_is_moving_down() const;
    float get_changing_speed() const;

    bool get_if_bailey_dead() const;
    void set_bailey_to_dead(bool);

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

private:
    void set_bailey_level();
    float changing_speed;
    float distance_between_iceRows;
    float bailey_speed_sideways;
    float bailey_speed_initial;
    float y_position;
    float x_position;
    float upper_boundary;
    float lower_boundary;
    float left_boundary;
    float right_boundary;

    bool safe_zone;
    float safe_zone_boundary;

    //see if bailey is moving or not
    bool is_moving;
    int bailey_level;

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

};
#endif // BAILEY_H
