#include "bailey.h"

Bailey::Bailey():
    changing_speed{0},
    distance_between_iceRows{82},
    bailey_speed_sideways{3},
    bailey_speed_initial{76},
    y_position{199.0f},
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
    is_dead{false},
    isMovingRight{false},
    isMovingLeft{false},
    RightKeyPressed{false},
    LeftKeyPressed{false},
    bailey_mass{75},
    gravity{9.8f},
    jumpForce{100.0f},
    left_right_const{200.0f},
    speed{0.0f},
    upJumpingForce{400}
{

}

void Bailey::set_bailey_movement(const Direction& dir, const float& side_speed,
    const bool& keyPressed_, Sprite& bailey_sprite,const float& deltaTime)
{
    RightKeyPressed = false;
    LeftKeyPressed = false;
   if (keyPressed_)
    {
        switch (dir)
        {
      /*  case Direction::Up:
            isMovingUp = true;
            isMovingDown = false;

            if (safe_zone)
            {
               // y_position -= bailey_speed_initial;
                set_bailey_level();
                changing_speed = bailey_speed_initial;
                if (y_position <= safe_zone_boundary)
                {
                    y_position = safe_zone_boundary;
                    set_bailey_level();
                    safe_zone = true;
                }

                else if (y_position > safe_zone_boundary)
                {
                    safe_zone = false;
                }
            }
            else
            {
                y_position -= distance_between_iceRows;
                set_bailey_level();
                changing_speed = distance_between_iceRows;
                if (y_position <= safe_zone_boundary)
                {
                    y_position = safe_zone_boundary;
                    set_bailey_level();
                    safe_zone = true;
                }
            }

            if (y_position <= upper_boundary)
            {
                y_position = upper_boundary;
                set_bailey_level();
            }
            break;

        case Direction::Down:
            isMovingDown = true;
            isMovingUp = false;
         
            if (y_position > safe_zone_boundary)
            {
                safe_zone = false;
            }

            if (safe_zone)
            {
               // y_position += bailey_speed_initial;
                set_bailey_level();
               // changing_speed = bailey_speed_initial;
            }
            else
            {
               // y_position += bailey_speed;
               // changing_speed = bailey_speed;
                set_bailey_level();
            }
            if (y_position >= lower_boundary)
            {
                y_position = lower_boundary;
                set_bailey_level();
            }
            break;
*/
        case Direction::Left:
            isMovingUp = false;
            isMovingDown = false;
            isMovingRight = false;
            isMovingLeft = true;
            LeftKeyPressed = keyPressed_;
            bailey_sprite.move(-left_right_const * deltaTime, 0);
            //update frostbite's horizontal direction
            x_position = bailey_sprite.getPosition().x;

            //Restrict frostbite to left screen border
            if (x_position <= left_boundary)
            {
                x_position = left_boundary;
                bailey_sprite.setPosition(x_position,y_position);
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
            RightKeyPressed = keyPressed_;
            bailey_sprite.move(left_right_const * deltaTime, 0);
            x_position = bailey_sprite.getPosition().x;
            if (x_position >= right_boundary)
            {
                x_position = right_boundary;
                bailey_sprite.setPosition(x_position, y_position);
                if (!safe_zone)
                {
                    is_dead = true;
                }

            }

            break;
        default:
            ;
        }
    }
}

bool Bailey::get_if_right_key_pressed() const
{
    return RightKeyPressed;
}

bool Bailey::get_if_left_key_pressed() const
{
    return LeftKeyPressed;
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

bool Bailey::get_if_moving_left() const
{
    return isMovingLeft;
}

bool Bailey::get_if_moving_right() const
{
    return isMovingRight;
}

float Bailey::get_bailey_mass() const
{
    return bailey_mass;
}

void Bailey::jump_down(Sprite& bailey_sprite,const float& deltaTime, const float& start_position, 
    bool& isJumping, bool& isJumpingDown)
{
    speed -= gravity * deltaTime;
    bailey_sprite.move(0, -speed);
    y_position = bailey_sprite.getPosition().y;//update vertical position
    auto jumped_distance = y_position - start_position;//calculate total distance jumped by frostbite
   
    if (jumped_distance > distance_between_iceRows)
    {
        //frostbite jumps betweent consecutive rows of ice
        y_position = start_position + distance_between_iceRows;
        x_position = bailey_sprite.getPosition().x;
        bailey_sprite.setPosition(x_position, y_position);
        isJumping = false;//frostbite has stepped on ice row or drowned
        isJumpingDown = false;
    }
}

void Bailey::jump_up(Sprite& bailey_sprite, const float& deltaTime, const float& start_position,
    bool& isJumping, bool& isJumpingUp)
{
    speed -= gravity * deltaTime;
    bailey_sprite.move(0, -speed);
    y_position = bailey_sprite.getPosition().y;
    auto jumped_distance = start_position - y_position;
    if (jumped_distance > distance_between_iceRows)
    {
        y_position = start_position - distance_between_iceRows;
        bailey_sprite.setPosition(x_position, y_position);
        isJumping = false;
        isJumpingUp = false;
    }
}

void Bailey::set_speed(const float& speed_)
{
    speed = speed_;
}

float Bailey::get_speed() const
{
    return speed;
}

float Bailey::get_jump_force() const
{
    return jumpForce;
}

float Bailey::get_up_jumping_force() const
{
    return upJumpingForce;
}
