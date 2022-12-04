#ifndef BAILEY_H
#define BAILEY_H
#include "gameConstants.h"
#include "SfmlLibrary.h"

class Bailey {
public:
    Bailey();
    void set_bailey_movement(Direction, float);
    float get_Xpos();
    float get_Ypos();
    bool is_bailey_moving() const;
    float getbailey_speed() const;
    bool get_if_bailey_in_safe_zone();

    int get_bailey_level();

    bool get_is_moving_up() const;
    bool get_is_moving_down() const;

    void reset_frame_counter1();
    void reset_frame_counter2();
    void increment_frame_counter1();
    void increment_frame_counter2();
    int get_frame_counter1();
    int get_frame_counter2();
    float get_changing_speed() const;

    void reset_frame_counter1_2();
    void reset_frame_counter2_2();
    void increment_frame_counter1_2();
    void increment_frame_counter2_2();
    int get_frame_counter1_2();
    int get_frame_counter2_2();

    bool get_if_bailey_dead() const;
    void set_bailey_to_dead(bool);
    bool get_from_bottom() const;
private:
    void set_bailey_level();
    float changing_speed;
    float bailey_speed;
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

    int frame_counter1;
    int frame_counter2;

    int frame_counter1_2;
    int frame_counter2_2;

    bool is_dead;
    bool from_bottom;
};
#endif // BAILEY_H
