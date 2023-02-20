#include "Logic.h"

Logic::Logic():
    number_of_igloo_blocks{0},
    ice_block_index{0},
    is_bailey_moving{false},
    is_igloo_complete{false},
    y_{0.0f},
    ice_collision_batch1{false},
    ice_collision_batch2{false}

{
    prev_pos.x = 240.0f; //Initial bailey position
    prev_pos.y = 205.0f; // Initial bailey position
    build_igloo();
}

void Logic::update_bailey_jumps(Sprite& bailey_sprite,bool& isJumping,const float& deltaTime,
    bool& isJumpingUp, bool& isJumpingDown)
{
    if (!isJumping)
    {
        y_ = bailey_object.get_Ypos();
    }

    if (isJumping && isJumpingDown)
    {
        bailey_object.jump_down(bailey_sprite, deltaTime,y_,isJumping,isJumpingDown);
        bailey_object.move_bailey(deltaTime, bailey_sprite);
    }

    if (isJumping && isJumpingUp)
    {
        bailey_object.jump_up(bailey_sprite, deltaTime, y_, isJumping, isJumpingUp);
        bailey_object.move_bailey(deltaTime, bailey_sprite);
    }
}

void Logic::update_bailey(Sprite& bailey_sprite)
{
    auto x = bailey_object.get_Xpos();
    auto y = bailey_object.get_Ypos();
    control_bailey.update_bailey(prev_pos, is_bailey_moving, x, y);
    control_bailey.animate_bailey(bailey_object, bailey_sprite);
}

void Logic::create_ice_block_objects(vector<shared_ptr<Sprite>>& ice_sprites,const int& vector_)
{
    auto ice_sprite_iter = ice_sprites.begin();
    while (ice_sprite_iter != ice_sprites.end())
    {
        if (ice_block_index == 0 || ice_block_index == 2)
        {
            shared_ptr<IceBlocks>ice_object_ptr(new IceBlocks);
            pos = (*ice_sprite_iter) ->getPosition();
            //ice_object_ptr -> set_position(pos);
            set_ice_direction(vector_, ice_block_index, ice_object_ptr,(*ice_sprite_iter));
            ice_object_ptr -> set_level(ice_block_index);
            if(vector_ == 1)
            {
                ice_block_objects1.push_back(ice_object_ptr);
            }
            else if (vector_ == 2)
            {
                ice_block_objects2.push_back(ice_object_ptr);
            }
        }
        else if (ice_block_index == 1 || ice_block_index == 3)
        {
            shared_ptr<IceBlocks>ice_object_ptr(new IceBlocks);
            pos = (*ice_sprite_iter) ->getPosition();
            //ice_object_ptr -> set_position(pos);
            //call the get direction function here
            set_ice_direction(vector_, ice_block_index, ice_object_ptr,(*ice_sprite_iter));
            ice_object_ptr -> set_level(ice_block_index);
            if (vector_ == 1)
            {
                ice_block_objects1.push_back(ice_object_ptr);
            }
            else if (vector_ == 2)
            {
                ice_block_objects2.push_back(ice_object_ptr);
            }
        }
        //std::cout << ice_block_index <<std::endl;
        ++ice_block_index;
        ++ice_sprite_iter;
    }

    if ((!ice_block_objects2.empty()) && vector_ == 1)
    {
        check_for_blues_on_other_ice_batch(ice_block_objects2, ice_block_objects1);
    }

    if ((!ice_block_objects1.empty()) && vector_ == 2)
    {
        check_for_blues_on_other_ice_batch(ice_block_objects1, ice_block_objects2);
    }

    ice_block_index = 0;
}

void Logic::update_ice(vector<shared_ptr<Sprite>>& ice_blocks, bool& can_create_new_batch, int vector_)
{
    if (vector_ == 1)
    {
        ice_block_controller.update_iceblocks(ice_block_objects1, ice_blocks, can_create_new_batch);
    }
    if (vector_ == 2)
    {
        ice_block_controller.update_iceblocks(ice_block_objects2, ice_blocks, can_create_new_batch);
    }
}

bool Logic::Is_bailey_moving() const
{
    return is_bailey_moving;
}

void Logic::bailey_and_ice_collision(vector<shared_ptr<Sprite>>& Igloo_house_sprites,Sprite& bailey_sprite,
    const float& deltaTime)
{
    ice_collision_batch1 = false;
    ice_collision_batch2 = false;

    if (!ice_block_objects1.empty())
    {
        auto collision_counter = 0;
        vector2f ice_position;
        vector2f bailey_position;
        auto ice_iter = ice_block_objects1.begin();
        while(ice_iter != ice_block_objects1.end())
        {

            bailey_position.x = bailey_object.get_Xpos() - bailey_width_offset;
            bailey_position.y = bailey_object.get_Ypos() - bailey_height_offset;
            //std::cout << "Y position:" << bailey_position.y << std::endl;
            ice_position.x =((*ice_iter) -> get_position()).x - ice_width_offset;
            ice_position.y =((*ice_iter) -> get_position()).y - ice_height_offset;

            //check if frostbite successfully stepped on first batch of ice
            auto isCollided = collision.bailey_ice_collision(bailey_position, bailey_width, bailey_height,
                ice_position, ice_width, ice_height);
            if (collision_counter == 0 && isCollided)
            {
                ice_collision_batch1 = isCollided;
                ++collision_counter;
            }
            if (isCollided)
            {
                //call build igloo function here
                auto isWhite = (*ice_iter) -> get_if_white();
                if (isWhite)
                {
                    auto igloo_ptr = igloo_object.begin();
                    (*igloo_ptr) -> add_igloo_blocks();
                    update_igloo(Igloo_house_sprites);

                }
                (*ice_iter) -> set_to_blue(true);
                (*ice_iter) -> set_to_white(false);
                //std::cout << "Ice position: " << ice_position.y << "should turn blue" << std::endl;
            }

            if (isCollided && !is_bailey_moving)
            {
                auto ice_moving_left = (*ice_iter) -> get_if_left();
                if (!ice_moving_left)
                {
                    //auto new_bailey_speed = (*ice_iter) -> get_ice_speed();
                    bailey_object.set_bailey_movement(Direction::Left,true,bailey_sprite,
                        deltaTime);
                }
                else
                {
                   // auto new_bailey_speed = (*ice_iter) -> get_ice_speed();
                    bailey_object.set_bailey_movement(Direction::Right,true,bailey_sprite,
                        deltaTime);
                }

            }
            auto ptr = igloo_object.begin();
            number_of_igloo_blocks = (*ptr)->get_number_of_igloo_blocks();
            if (number_of_igloo_blocks == 14)
            {
                //just set blocks of ice to blue
                set_all_ice_batches_to_blue(ice_block_objects1);
            }

            if (number_of_igloo_blocks < 14)
            {
                check_for_blues(ice_block_objects1);
            }
            ++ice_iter;
        }
    }

    //We want to check if the other vector of ice has a blue.
    //If it has a blue, change row in respective batch to blue.
    //Check if it is not empty first
    if(!ice_block_objects2.empty())
    {
        check_for_blues_on_other_ice_batch(ice_block_objects1,ice_block_objects2);
        //check_for_blues_on_other_ice_batch(ice_block_objects2,ice_block_objects1);
    }

    auto ptr = igloo_object.begin();
    number_of_igloo_blocks = (*ptr)->get_number_of_igloo_blocks();

    if(number_of_igloo_blocks < 14)
    {
        check_for_blues(ice_block_objects1);
    }

    if (!ice_block_objects2.empty())
    {
        auto collission_counter = 0;
        vector2f ice_position;
        vector2f bailey_position;
        auto ice_iter = ice_block_objects2.begin();
        while(ice_iter != ice_block_objects2.end())
        {

            bailey_position.x = bailey_object.get_Xpos() - bailey_width_offset;
            bailey_position.y = bailey_object.get_Ypos() - bailey_height_offset;

            ice_position.x =((*ice_iter) -> get_position()).x - ice_width_offset;
            ice_position.y =((*ice_iter) -> get_position()).y - ice_height_offset;

            //check if frostbite suceessfully stepped on second batch of ice
            auto isCollided = collision.bailey_ice_collision(bailey_position, bailey_width, bailey_height,
                ice_position, ice_width, ice_height);
            if (collission_counter == 0 && isCollided)
            {
                ice_collision_batch2 = isCollided;
                ++collission_counter;
            }

            if(isCollided)
            {
                //call the build igloo function here
                auto isWhite = (*ice_iter) -> get_if_white();
                if (isWhite)
                {
                    auto igloo_ptr = igloo_object.begin();
                    (*igloo_ptr) -> add_igloo_blocks();
                    update_igloo(Igloo_house_sprites);
                }

                (*ice_iter) -> set_to_blue(true);
                (*ice_iter) -> set_to_white(false);
            }

            if (isCollided && !is_bailey_moving)
            {
                auto ice_moving_left = (*ice_iter) -> get_if_left();
                if (!ice_moving_left)
                {
                   // auto new_bailey_speed = (*ice_iter) -> get_ice_speed();
                    bailey_object.set_bailey_movement(Direction::Left,true,bailey_sprite,
                        deltaTime);
                }
                else
                {
                    //auto new_bailey_speed = (*ice_iter) -> get_ice_speed();
                    bailey_object.set_bailey_movement(Direction::Right,true,bailey_sprite,
                        deltaTime);
                }

            }
            
            if (number_of_igloo_blocks == 14)
            {
                //just set blocks of ice to blue
                set_all_ice_batches_to_blue(ice_block_objects2);
            }

            if(number_of_igloo_blocks < 14)
            {
                check_for_blues(ice_block_objects2);
            }
            ++ice_iter;
        }

    }

    //We want to check if the other vector of ice has a blue.
    //If it has a blue, change row in respective batch to blue.
    if(!ice_block_objects1.empty())
    {
        check_for_blues_on_other_ice_batch(ice_block_objects2,ice_block_objects1);
        //check_for_blues_on_other_ice_batch(ice_block_objects1,ice_block_objects2);
    }

    if(number_of_igloo_blocks < 14)
    {
        check_for_blues(ice_block_objects2);
    }
}

void Logic::update_igloo(vector<shared_ptr<Sprite>>& Igloo_sprites)
{
    auto igloo_ptr = igloo_object.begin();
    (*igloo_ptr)-> build_igloo(Igloo_sprites);
}

void Logic::check_for_blues(vector<shared_ptr<IceBlocks>>Iceblocks)
{
    auto blue_marker = 0;
    auto iter = Iceblocks.begin();
    while(iter != Iceblocks.end())
    {
        auto isBlue = (*iter) -> get_if_blue();
        if (isBlue)
        {
            ++blue_marker;
        }

        ++iter;
    }

    if (blue_marker == 4)
    {
        auto iter2 = Iceblocks.begin();
        while(iter2 != Iceblocks.end())
        {
            //std::cout << "Set "<< blue_marker<< std::endl;
            (*iter2) -> set_to_white(true);
            (*iter2) -> set_to_blue(false);
            ++iter2;
        }
    }
}

void Logic::check_for_blues_on_other_ice_batch(vector<shared_ptr<IceBlocks>> current_ice_block_obj,
        vector<shared_ptr<IceBlocks>> other_ice_batch)
{
    auto iter = current_ice_block_obj.begin();
    while (iter != current_ice_block_obj.end())
    {
        auto blue = (*iter) -> get_if_blue();
        auto white = (*iter) -> get_if_white();
        if (blue)
        {
            //want to get the level of this ice row
            //then change every row of the batch to blue
            auto current_ice_level = (*iter) -> get_ice_level();

            //On same row of ice, change entire row to blue
            auto other_ice = other_ice_batch.begin();
            while(other_ice != other_ice_batch.end())
            {
                auto ice_level2 = (*other_ice) -> get_ice_level();
                if (ice_level2 == current_ice_level)
                {
                    (*other_ice) -> set_to_blue(true);
                    (*other_ice) -> set_to_white(false);
                }
                ++other_ice;
            }
        }

        else if (white)
        {
            auto current_ice_level = (*iter) -> get_ice_level();
            auto other_ice = other_ice_batch.begin();
            while(other_ice != other_ice_batch.end())
            {
                auto ice_level2 = (*other_ice) -> get_ice_level();
                if (ice_level2 == current_ice_level)
                {
                    (*other_ice) -> set_to_white(true);
                    (*other_ice) -> set_to_blue(false);

                }
                ++other_ice;
            }
        }
        ++iter;
    }
}

void Logic::set_all_ice_batches_to_blue(vector<shared_ptr<IceBlocks>>& ice_blocks)
{
    auto iter = ice_blocks.begin();
    while(iter != ice_blocks.end())
    {
        (*iter) -> set_to_white(false);
        (*iter) -> set_to_blue(true);
        ++iter;
    }
}

bool Logic::mark_if_igloo_is_complete()
{
    auto at_door = bailey_object.get_Xpos();
    if (number_of_igloo_blocks == 14 && (at_door >= 610.0f))
    {
        return true;
    }
    else
        return false;
}

void Logic::reverse_ice_direction(vector<shared_ptr<Sprite>>& igloo_sprites)
{
    if(!ice_block_objects1.empty())
    {
        vector2f ice_position;
        vector2f bailey_position;
        auto ice_iter = ice_block_objects1.begin();
        while(ice_iter != ice_block_objects1.end())
        {
            bailey_position.x = bailey_object.get_Xpos() - bailey_width_offset;
            bailey_position.y = bailey_object.get_Ypos() - bailey_height_offset;

            ice_position.x =((*ice_iter) -> get_position()).x - ice_width_offset;
            ice_position.y =((*ice_iter) -> get_position()).y - ice_height_offset;

            auto is_collided = collision.bailey_ice_collision(bailey_position,bailey_width,bailey_height,
                               ice_position,ice_width,ice_height);

            if (is_collided)
            {
                auto moving_left = (*ice_iter) -> get_if_left();
                if (moving_left)
                {
                    auto igloo_ptr = igloo_object.begin();
                    (*igloo_ptr) -> subract_igloo_block();
                    (*ice_iter) -> set_if_left(false);
                    update_igloo(igloo_sprites);
                }
                else
                {
                    auto igloo_ptr = igloo_object.begin();
                    (*igloo_ptr) -> subract_igloo_block();
                    (*ice_iter) -> set_if_left(true);
                    update_igloo(igloo_sprites);
                }
            }

            ++ice_iter;
        }

    }

    if(!ice_block_objects2.empty())
    {
        vector2f ice_position;
        vector2f bailey_position;
        auto ice_iter = ice_block_objects2.begin();
        while(ice_iter != ice_block_objects2.end())
        {
            bailey_position.x = bailey_object.get_Xpos() - bailey_width_offset;
            bailey_position.y = bailey_object.get_Ypos() - bailey_height_offset;

            ice_position.x =((*ice_iter) -> get_position()).x - ice_width_offset;
            ice_position.y =((*ice_iter) -> get_position()).y - ice_height_offset;

            auto is_collided = collision.bailey_ice_collision(bailey_position,bailey_width,bailey_height,
                               ice_position,ice_width,ice_height);

            if (is_collided)
            {
                auto moving_left = (*ice_iter) -> get_if_left();
                if (moving_left)
                {
                    (*ice_iter) -> set_if_left(false);
                    auto igloo_ptr = igloo_object.begin();
                    (*igloo_ptr) -> subract_igloo_block();
                    update_igloo(igloo_sprites);
                }
                else
                {
                    (*ice_iter) -> set_if_left(true);
                    auto igloo_ptr = igloo_object.begin();
                    (*igloo_ptr) -> subract_igloo_block();
                    update_igloo(igloo_sprites);
                }
            }

            ++ice_iter;
        }

    }
}

void Logic::build_igloo()
{
    auto igloo_object_ptr = std::make_shared<Igloo>();
    position.x = igloo_object_ptr -> get_x_position();
    position.y = igloo_object_ptr->get_y_position();
    igloo_object.push_back(igloo_object_ptr);
}

vector2f Logic::get_igloo_position()
{
    return position;
}

int Logic::get_number_of_igloo_blocks()
{
    auto igloo_ptr = igloo_object.begin();
    number_of_igloo_blocks = (*igloo_ptr) -> get_number_of_igloo_blocks();
    return number_of_igloo_blocks;
}

void Logic::set_ice_direction(const int& vector_, const int& ice_level, shared_ptr<IceBlocks>& ptr,
    shared_ptr<Sprite>& ptr2)
{
    if (vector_ == 1)
    {
        if (!ice_block_objects2.empty())
        {
            auto obj2_ptr = ice_block_objects2.begin();
            while (obj2_ptr != ice_block_objects2.end())
            {
                auto level = (*obj2_ptr)->get_ice_level();
                if (level == ice_level)
                {
                    auto direction = (*obj2_ptr)->get_if_left();
                    if (direction)
                    {
                        vector2f position = ptr2->getPosition();
                        position.x = -160.0f;
                        ptr2->setPosition(position);
                        ptr->set_position(position);
                    }
                    else
                    {
                        vector2f position = ptr2->getPosition();
                        position.x = 960.0f;
                        ptr2->setPosition(position);
                        ptr->set_position(position);
                    }

                    ptr->set_if_left(direction);
                    break;
                }
                ++obj2_ptr;
            }
        }
        else if ((ice_level == 1 || ice_level == 3) && (ice_block_objects2.empty()))
        {
            //Have to set to default
            ptr->set_if_left(true);
        }
    }

    else if (vector_ == 2)
    {
        if (!ice_block_objects1.empty())
        {
            auto obj1_ptr = ice_block_objects1.begin();
            while (obj1_ptr != ice_block_objects1.end())
            {
                auto level = (*obj1_ptr)->get_ice_level();
                if (level == ice_level)
                {
                    auto direction = (*obj1_ptr)->get_if_left();
                    if (direction)
                    {
                        vector2f position = ptr2->getPosition();
                        position.x = -160.0f;
                        ptr2->setPosition(position);
                        ptr->set_position(position);
                    }
                    else
                    {
                        vector2f position = ptr2->getPosition();
                        position.x = 960.0f;
                        ptr2->setPosition(position);
                        ptr->set_position(position);
                    }
                    ptr->set_if_left(direction);
                    break;
                }
                ++obj1_ptr;
            }
        }

        else if ((ice_level == 0 ||ice_level == 2) && (ice_block_objects1.empty()))
        {
            ptr->set_if_left(true);
        }
    }
}

//This tuple function returns variable that mark if frostbite successfully stepped on ice
std::tuple<bool,bool> Logic::get_collisions()
{
    return { ice_collision_batch1,ice_collision_batch2};
}

void Logic::update_bear(Sprite& bear_sprite,const float& deltaTime)
{
    bear_track_bailey(bear_sprite);
    bear_object.update_bear(bear_sprite, deltaTime);
}

void Logic::bear_track_bailey(Sprite& bear_sprite)
{
    auto timePassed = bear_object.elapsed_time();

    // Bear should track bailey's position after every 3 seconds 
    if (timePassed >= 3)
    {
        std::cout << "Time is: " << timePassed << "track!" << std::endl;
        //restart stop watch
        bear_object.restart_timer();
    }
}

Logic::~Logic()
{
    ice_block_objects1.clear();
    ice_block_objects2.clear();
    igloo_object.clear();
}
