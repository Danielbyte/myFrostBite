#include "bailey.h"

Bailey::Bailey():
    distance_between_iceRows{82},
    y_position{199.0f},
    x_position{240.0f},
    lower_boundary{527.0f},
    left_boundary{24.0f},
    right_boundary{776.0f},
    safe_zone{true}, //player initially in safe zone
    safe_zone_boundary{199.0f},
    is_moving{false}, //bailey initially stagnant
    isMovingUp{false},
    isMovingDown{false},
    is_dead{false},
    isMovingRight{false},
    isMovingLeft{false},
    RightKeyPressed{false},
    LeftKeyPressed{false},
    bailey_mass{75},
    gravity{10.0f},
    jumpForce{80.0f},
    left_right_const{180.0f},
    speed{0.0f},
    upJumpingForce{410.0f},
    ice_speed{60.0f},
    speed_attenuater{1.5f},
    upJump_speedAtten{1.0f},
    is_bailey_jumping{false}
{

}

void Bailey::set_bailey_movement(const Direction& dir,
    const bool& keyPressed_, Sprite& bailey_sprite,const float& deltaTime)
{
    RightKeyPressed = false;
    LeftKeyPressed = false;
   if (keyPressed_)
    {
        switch (dir)
        {
        case Direction::Left:
            isMovingUp = false;
            isMovingDown = false;
            bailey_sprite.move(- ice_speed * deltaTime, 0);
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
            bailey_sprite.move(ice_speed * deltaTime, 0);
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
        //default:
            //;
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

void Bailey::move_bailey(const float& deltaTime, Sprite& player_sprite)
{
    RightKeyPressed = false;
    LeftKeyPressed = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        isMovingRight = true;
        isMovingLeft = false;
        player_sprite.move(left_right_const * deltaTime, 0);
        x_position = player_sprite.getPosition().x;
        RightKeyPressed = true;

        if (x_position >= right_boundary)
        {
            x_position = right_boundary;
            player_sprite.setPosition(x_position, y_position);
            if (!safe_zone)
            {
                is_dead = true;
            }
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        isMovingLeft = true;
        isMovingRight = false;

        // move player
        player_sprite.move(-left_right_const * deltaTime, 0);
        //update the x position
        x_position = player_sprite.getPosition().x;
        LeftKeyPressed = true;

        //restrict player within screen
        if (x_position <= left_boundary)
        {
            x_position = left_boundary;
            player_sprite.setPosition(x_position, y_position);

            if (!safe_zone)
            {
                is_dead = true;
            }
        }
    }
}

float Bailey::get_Ypos()
{
    return y_position;
}

bool Bailey::is_bailey_moving() const
{
    return is_moving;
}

bool Bailey::get_if_bailey_in_safe_zone()
{
    if (y_position > safe_zone_boundary) {safe_zone = false;}
    else if (y_position <= safe_zone_boundary) {safe_zone = true;}
    return safe_zone;
}

void Bailey::calibrate(const float& position)
{
    if (position >= 280.0f && position <= 281.0f)
    {
        y_position = 281.0f;
    }

}

bool Bailey::get_is_moving_down() const
{
    return isMovingDown;
}

bool Bailey::get_is_moving_up() const
{
    return isMovingUp;
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
    speed -= gravity * deltaTime * speed_attenuater;
    bailey_sprite.move(0, -speed);
    y_position = bailey_sprite.getPosition().y;//update vertical position
    auto jumped_distance = y_position - start_position;//calculate total distance jumped by frostbite
    is_bailey_jumping = isJumping;

    if (jumped_distance > distance_between_iceRows)
    {
        //frostbite jumps betweent consecutive rows of ice
        y_position = start_position + distance_between_iceRows;
        calibrate(y_position);
        bailey_sprite.setPosition(x_position, y_position);
        isJumping = false;//frostbite has stepped on ice row or drowned
        isJumpingDown = false;
        is_bailey_jumping = false;
    }
}

void Bailey::jump_up(Sprite& bailey_sprite, const float& deltaTime, const float& start_position,
    bool& isJumping, bool& isJumpingUp)
{
    
    if (y_position > safe_zone_boundary)
    {
        speed -= gravity * deltaTime * upJump_speedAtten;
        bailey_sprite.move(0, -speed);
        y_position = bailey_sprite.getPosition().y;
        auto jumped_distance = start_position - y_position;
        is_bailey_jumping = isJumping;

        if (speed < 0 && y_position >= (start_position - distance_between_iceRows))
        {
            y_position = start_position - distance_between_iceRows;
            bailey_sprite.setPosition(x_position, y_position);
            isJumping = false;
            isJumpingUp = false;
            is_bailey_jumping = false;
        }
    }

    else if(y_position <= safe_zone_boundary)
    {
        isJumping = false;
        isJumpingUp = false;
        is_bailey_jumping = false;
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

bool Bailey::isBaileyJumping() const
{
    return is_bailey_jumping;
}
