#include "bailey.h"

Bailey::Bailey():
    changing_speed{0},
    bailey_speed{82},
    bailey_speed_sideways{2},
    bailey_speed_initial{76},
    y_position{205.0f},
    x_position{240.0f},
    upper_boundary{24.0f},
    lower_boundary{527.0f},
    left_boundary{24.0f},
    right_boundary{776.0f},
    safe_zone{true}, //player initially in safe zone
    safe_zone_boundary{205},
    is_moving{false}, //bailey initially stagnant
    bailey_level{5},
    isMovingUp{false},
    isMovingDown{false},
    frame_counter1{0},
    frame_counter2{0},
    frame_counter1_2{0},
    frame_counter2_2{0},
    is_dead{false},
    from_bottom{false},
    isMovingRight{false},
    isMovingLeft{false}
{

}

void Bailey::set_bailey_movement(Direction dir, float side_speed)
{
    switch(dir)
    {
    case Direction::Up:
        isMovingUp = true;
        isMovingDown = false;
        //std::cout<< "Moving up" <<std::endl;
        if (safe_zone)
        {
            y_position -= bailey_speed_initial;
            set_bailey_level();
            changing_speed = bailey_speed_initial;
            if (y_position <= safe_zone_boundary)
            {
                y_position = safe_zone_boundary;
                set_bailey_level();
                //std::cout << y_position << std::endl;
                safe_zone = true;
                //std::cout << "Level"<<bailey_level << std::endl;
            }

            else if(y_position > safe_zone_boundary)
            {
                safe_zone = false;
                //--bailey_level;
                //std::cout << "Level"<<bailey_level << std::endl;
            }
        }
        else
        {
            y_position -= bailey_speed;
            set_bailey_level();
            changing_speed = bailey_speed;
            if (y_position <= safe_zone_boundary)
            {
                y_position = safe_zone_boundary;
                set_bailey_level();
                safe_zone = true;
                // bailey_level = 0;
                // std::cout << "Level"<<bailey_level << std::endl;
            }
            // std::cout <<y_position <<std::endl;
        }

        if (y_position <= upper_boundary)
        {
            y_position = upper_boundary;
            set_bailey_level();
        }
        //std::cout << "Level"<<bailey_level << std::endl;
        //std::cout << y_position << std::endl;
        break;

    case Direction::Down:
        isMovingDown = true;
        isMovingUp = false;
        // std::cout<< "Moving Down" <<std::endl;
        if (y_position > safe_zone_boundary)
        {
            safe_zone = false;
        }

        if (safe_zone)
        {
            y_position += bailey_speed_initial;
            set_bailey_level();
            changing_speed = bailey_speed_initial;
            // bailey_level = 0;
            //std::cout << "Level"<<bailey_level << std::endl;
        }
        else
        {
            y_position += bailey_speed;
            changing_speed = bailey_speed;
            set_bailey_level();
            //++bailey_level;
            //std::cout << "Level"<<bailey_level << std::endl;
        }
        if (y_position >= lower_boundary)
        {
            y_position = lower_boundary;
            set_bailey_level();
        }
        break;

    case Direction::Left:
        isMovingUp = false;
        isMovingDown = false;
        isMovingRight = false;
        isMovingLeft = true;
        x_position -= side_speed;
        if(x_position <= left_boundary)
        {
            x_position = left_boundary;
            if (!safe_zone)
            {
                is_dead = true;
            }

        }
        break;


    case Direction::Right:
        isMovingUp = false;
        isMovingDown = false;
        isMovingRight = true;
        isMovingLeft = false;
        x_position += side_speed;
        if (x_position >= right_boundary)
        {
            x_position = right_boundary;
            if(!safe_zone)
            {
                is_dead = true;
            }

        }

        break;
    default:
        ;
    }
}

float Bailey::get_Xpos()
{
    return x_position;
}

float Bailey::get_Ypos()
{
    return y_position;
}

bool Bailey::is_bailey_moving() const
{
    return is_moving;
}

float Bailey::getbailey_speed() const
{
    return bailey_speed_sideways;
}

bool Bailey::get_if_bailey_in_safe_zone()
{
    if (y_position > safe_zone_boundary) {safe_zone = false;}
    else if (y_position <= safe_zone_boundary) {safe_zone = true;}
    return safe_zone;
}

void Bailey::set_bailey_level()
{
    if (y_position == 281)
    {
        bailey_level = 0;
    }

    if (y_position == 363)
    {
        bailey_level = 1;
    }

    if (y_position == 445)
    {
        bailey_level = 2;
    }

    if (y_position == 527)
    {
        bailey_level = 3;
        from_bottom = true;
    }
    if (y_position == safe_zone_boundary)
    {
        bailey_level = 5;
    }
}

int Bailey::get_bailey_level()
{
    set_bailey_level();
    return bailey_level;
}

bool Bailey::get_is_moving_down() const
{
    return isMovingDown;
}

bool Bailey::get_is_moving_up() const
{
    return isMovingUp;
}

void Bailey::reset_frame_counter1()
{
    frame_counter1 = 0;
}
void Bailey::reset_frame_counter2()
{
    frame_counter2 = 0;
}
void Bailey::increment_frame_counter1()
{
    ++frame_counter1;
}
void Bailey::increment_frame_counter2()
{
    ++frame_counter2;
}
int Bailey::get_frame_counter1()
{
    return frame_counter1;
}
int Bailey::get_frame_counter2()
{
    return frame_counter2;
}

void Bailey::reset_frame_counter1_2()
{
    frame_counter1_2 = 0;
}
void Bailey::reset_frame_counter2_2()
{
    frame_counter2_2 = 0;
}
void Bailey::increment_frame_counter1_2()
{
    ++frame_counter1_2;
}
void Bailey::increment_frame_counter2_2()
{
    ++frame_counter2_2;
}
int Bailey::get_frame_counter1_2()
{
    return frame_counter1_2;
}
int Bailey::get_frame_counter2_2()
{
    return frame_counter2_2;
}


float Bailey::get_changing_speed() const
{
    return changing_speed;
}

bool Bailey::get_if_bailey_dead()const
{
    return is_dead;
}

void Bailey::set_bailey_to_dead(bool status)
{
    is_dead = status;
}

bool Bailey::get_from_bottom() const
{
    return from_bottom;
}

bool Bailey::get_if_moving_left() const
{
    return isMovingLeft;
}

bool Bailey::get_if_moving_right() const
{
    return isMovingRight;
}
