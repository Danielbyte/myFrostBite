#include "Logic.h"

Logic::Logic():
    number_of_igloo_blocks{0},
    ice_block_index{0},
    is_bailey_moving{false},
    is_igloo_complete{false},
    y_{0.0f},
    ice_collision_batch1{false},
    ice_collision_batch2{false},
    plungedInWater{true}

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

std::tuple<vector2f,vector2f,vector2f,vector2f> Logic::create_ice_block_objects()
{
    auto noIceBlocks = ice_block_objects.empty();//check if there are no ices at present
    vector2f _pos1;
    vector2f _pos2;
    vector2f _pos3;
    vector2f _pos4;

    if (noIceBlocks)
    {    
        _pos1.x = 550.0f;
        _pos1.y = 305.0f;
        shared_ptr<IceBlocks>obj_1(new IceBlocks(_pos1));
        obj_1->set_region(IceRegion::R1);
        obj_1->set_direction(IceDirection::L);
        ice_block_objects.push_back(obj_1);

        //Create second row of ice
        _pos2.x = 250.0f;
        _pos2.y = 387.0f;
        shared_ptr<IceBlocks>obj_2(new IceBlocks(_pos2));
        obj_2->set_region(IceRegion::R2);
        obj_2->set_direction(IceDirection::R);
        ice_block_objects.push_back(obj_2);

        //create third row of ice
        _pos3.x = 550.0f;
        _pos3.y = 468.0f;
        shared_ptr<IceBlocks>obj_3(new IceBlocks(_pos3));
        obj_3->set_region(IceRegion::R3);
        obj_3->set_direction(IceDirection::L);
        ice_block_objects.push_back(obj_3);

        //create fourth row of ice
        _pos4.x = 250.0f;
        _pos4.y = 551.0f;
        shared_ptr<IceBlocks>obj_4(new IceBlocks(_pos4));
        obj_4->set_region(IceRegion::R4);
        obj_4->set_direction(IceDirection::R);
        ice_block_objects.push_back(obj_4);
    }

    return { _pos1,_pos2,_pos3,_pos4 };
}

void Logic::update_ice(vector<shared_ptr<Sprite>>& ice_block_sprites, const float& deltaTime)
{
    ice_block_controller.update_iceblocks(ice_block_objects, ice_block_sprites, deltaTime);
}

bool Logic::Is_bailey_moving() const
{
    return is_bailey_moving;
}

void Logic::bailey_and_ice_collision(vector<shared_ptr<Sprite>>& Igloo_house_sprites,Sprite& bailey_sprite,
    const float& deltaTime)
{
    ice_collision_batch1 = true;
    /*
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
                
                //frostbite should only move along a patch of ice, otherwise drown
                check_frostbite_on_ice_patch(*ice_iter);
                if (plungedInWater)
                { 
                    ice_collision_batch1 = false;                  
                    return; 
                }

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

                check_frostbite_on_ice_patch(*ice_iter);
                
                if (plungedInWater)
                {
                    ice_collision_batch2 = false;
                    return;
                }
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
    */
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
    /*
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
    */
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
    /*
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
    */
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

    // Bear should track bailey's position after every 1 second 
    if (timePassed >= 2.0f)
    {
        auto bailey_x_position = bailey_object.get_Xpos();
        auto bear_position = bear_object.get_position();
        //get the distance between bear and frostbite
        auto distance_between = abs(bailey_x_position - bear_position.x);
        auto safe_zone = bailey_object.get_if_bailey_in_safe_zone();

        //left and right boundaries
        auto leftBoundary = bailey_object.get_left_boundary();
        auto rightBoundary = bailey_object.get_right_boundary();

        //bear should not move if bailey is at the ends of screen
        if (!safe_zone && distance_between <= 31.0f && 
            (bailey_x_position <= leftBoundary || bailey_x_position >= rightBoundary))
        {
            bear_object.set_bear_direction(Direction::unknown);
        }

        else
        {
            if (bailey_x_position < bear_position.x)
            {
                bear_object.set_bear_direction(Direction::Left);
            }

            else if (bailey_x_position > bear_position.x)
            {
                bear_object.set_bear_direction(Direction::Right);
            }
        }
        
        //restart stop watch
        bear_object.restart_timer();
    }
}

void Logic::frostbite_bear_collisions()
{
    auto bear_position = bear_object.get_position();
    vector2f bailey_position;
    bailey_position.x = bailey_object.get_Xpos();
    bailey_position.y = bailey_object.get_Ypos();

    auto isCollided = collision.entity_collision(bailey_position, bailey_width, bailey_height,
        bear_position, bear_with, bear_height);

    //bailey needs to be in safe zone
    auto baileyInSafeZone = bailey_object.get_if_bailey_in_safe_zone();
    if (isCollided && baileyInSafeZone)
    {
        bailey_object.set_bailey_to_dead(true);
    }
}

void Logic::update_enemies(vector<shared_ptr<Sprite>>& _crabs, vector<shared_ptr<Sprite>>& _clamps,
    vector<shared_ptr<Sprite>>& _birds, vector<shared_ptr<Sprite>>& _fish, const float& deltaTime)
{
    //create enemy every 5 seconds
    auto timeElapsed = enemy.elapsed_time();
  
    if (timeElapsed >= 5)
    {
        auto isEnemyInRegion1 = enemy.enemy_in_region1();
        auto isEnemyInRegion2 = enemy.enemy_in_region2();
        auto isEnemyInRegion3 = enemy.enemy_in_region3();
        auto isEnemyInRegion4 = enemy.enemy_in_region4();
  
        //Create enemies if there are none at respective regions
        if (!isEnemyInRegion1)
        {
            //Create any enemy in region 1
            auto r1Pos = enemy.get_region1();
            enemy.create_enemy(_crabs, _clamps, _birds, _fish, crabs, clamps, birds, fish, r1Pos);
           // enemy.restart_timer();
           // return;
        }

        if (!isEnemyInRegion2)
        {
            //create enemy in region 2
            auto r2Pos = enemy.get_region2();
            enemy.create_enemy(_crabs, _clamps, _birds, _fish, crabs, clamps, birds, fish, r2Pos);
           // enemy.restart_timer();
           // return;
        }

        if (!isEnemyInRegion3)
        {
            //create any enemy in region 3
            auto r3Pos = enemy.get_region3();
            enemy.create_enemy(_crabs, _clamps, _birds, _fish, crabs, clamps, birds, fish, r3Pos);
            //enemy.restart_timer();
            //return;
        }

        if (!isEnemyInRegion4)
        {
            //create any enemy in region 4
            auto r4Pos = enemy.get_region4();
            enemy.create_enemy(_crabs, _clamps, _birds, _fish, crabs, clamps, birds, fish, r4Pos);
            //enemy.restart_timer();
            //return;
        }
        enemy.restart_timer();
    }

    control_crab.update_crab(_crabs, crabs,deltaTime);
    control_clamp.update_clamp(_clamps, clamps, deltaTime);
    control_fish.update_fish(_fish, fish, deltaTime);
    control_bird.update_birds(_birds, birds, deltaTime);

    //update enemy regions
    enemy.update_enemy_regions(crabs, clamps, birds, fish);
}

void Logic::animate_bailey_death(const float& deltaTime, Sprite& bailey_sprite)
{
    control_bailey.bailey_death(deltaTime, bailey_sprite);
}

void Logic::check_frostbite_on_ice_patch(shared_ptr<IceBlocks>& ice_ptr)
{
    auto ice_x_pos = (ice_ptr->get_position()).x - ice_width_offset;
    auto bailey_x_pos = bailey_object.get_Xpos() - bailey_width_offset;
    auto point1_offset = 37.0f;
    auto point1 = ice_x_pos - point1_offset;
    auto point2_offset = 26.0f;
    auto point2 = (ice_x_pos + point2_offset) + ice_patch_width;
    auto EOI_offset = 16.0f; // end of ice offset
    auto end_of_ice = ice_x_pos + ice_width - EOI_offset;
    plungedInWater = true;
    
    if (bailey_x_pos >= point1 && bailey_x_pos <= end_of_ice)
    {
        if (bailey_x_pos >= point1 && ((bailey_x_pos + bailey_width) <= point2))
        {
            plungedInWater = false;
        }

        auto point3_offset = 26.5f;
        auto point3 = point2 - point3_offset;
        auto point4_offset = 50.5f;
        auto point4 = point3 + ice_patch_width+ point4_offset;
        if (bailey_x_pos >= point3 && ((bailey_x_pos + bailey_width) <= point4))
        {
            plungedInWater = false;
        }

        auto point5_offset = 29.8f;
        auto point5 = point4 - point5_offset;
        if (bailey_x_pos >= point5)
        {
            plungedInWater = false;
        }

    }

    if (plungedInWater)
    {
        bailey_object.set_bailey_to_dead(true);
    }
}

void Logic::drowning_bailey_animation(const float& deltaTime,Sprite& bailey_sprite)
{
    control_bailey.drowning_bailey(deltaTime, bailey_sprite);
}

void Logic::updateBaileyAndSeaAnimalCollisioons(vector<shared_ptr<Sprite>>& crab_sprites,
    vector<shared_ptr<Sprite>>& clamp_sprites, vector<shared_ptr<Sprite>>& bird_sprites,
    vector<shared_ptr<Sprite>>& fish_sprites)
{
    //AIR -> Animal In Region
    auto [AIR1, AIR2, AIR3, AIR4] = enemy.get_animals_in_regions();
    auto bailey_region = bailey_object.get_bailey_region();
    switch (bailey_region)
    {
    case BaileyRegion::region1:
        region_collisions(AIR1, crab_sprites, clamp_sprites, bird_sprites, fish_sprites);
        break;
    case BaileyRegion::region2:
        region_collisions(AIR2, crab_sprites, clamp_sprites, bird_sprites, fish_sprites);
        break;
    case BaileyRegion::region3:
        region_collisions(AIR3, crab_sprites, clamp_sprites, bird_sprites, fish_sprites);
        break;
    case BaileyRegion::region4:
        region_collisions(AIR4, crab_sprites, clamp_sprites, bird_sprites, fish_sprites);
        break;
    case BaileyRegion::unknown:
        break;
    default:
        break;
    }
}

void Logic::region_collisions(const Animal& typeOfAnimal, vector<shared_ptr<Sprite>>& crab_sprites,
    vector<shared_ptr<Sprite>>& clamp_sprites, vector<shared_ptr<Sprite>>& bird_sprites,
    vector<shared_ptr<Sprite>>& fish_sprites)
{
    switch (typeOfAnimal)
    {
    case Animal::crabs:
        bailey_crab_collision(crab_sprites);
        break;
    case Animal::clamps:
        bailey_clamp_collision(clamp_sprites);
        break;
    case Animal::birds:
        bailey_bird_collision(bird_sprites);
        break;
    case Animal::fish:
        bailey_fish_collision(fish_sprites);
        break;
    default:
        break;
    }
}

void Logic::bailey_fish_collision(vector<shared_ptr<Sprite>>& fish_sprites)
{
    auto fish_obj_iter = fish.begin();
    auto fish_sprite_iter = fish_sprites.begin();
    while (fish_obj_iter != fish.end())
    {
        auto fish_pos = (*fish_obj_iter)->get_position();
        vector2f bailey_pos;
        bailey_pos.x = bailey_object.get_Xpos();
        bailey_pos.y = bailey_object.get_Ypos();
        auto isCollided = collision.bailey_enemy_collision(fish_pos, fish_width,fish_height,
            bailey_pos, bailey_width, bailey_height);

        if (isCollided)
        {
            
            fish.erase(fish_obj_iter);
            fish_sprites.erase(fish_sprite_iter);
            return;
        }
        ++fish_obj_iter;
        ++fish_sprite_iter;
    }
}

void Logic::bailey_clamp_collision(vector<shared_ptr<Sprite>>& clamp_sprites)
{
    auto clamp_obj_iter = clamps.begin();
    auto clamp_sprite_iter = clamp_sprites.begin();
    while (clamp_obj_iter != clamps.end())
    {
        auto clamp_pos = (*clamp_obj_iter)->get_position();
        vector2f bailey_pos;
        bailey_pos.x = bailey_object.get_Xpos();
        bailey_pos.y = bailey_object.get_Ypos();
        auto isCollided = collision.bailey_enemy_collision(clamp_pos, clamp_width,clamp_height,
            bailey_pos, bailey_width, bailey_height);

        if (isCollided)
        {
        }
        ++clamp_obj_iter;
        ++clamp_sprite_iter;
    }
}

void Logic::bailey_crab_collision(vector<shared_ptr<Sprite>>& crab_sprites)
{
    auto crab_obj_iter = crabs.begin();
    auto crab_sprite_iter = crab_sprites.begin();
    while (crab_obj_iter != crabs.end())
    {
        auto crab_pos = (*crab_obj_iter)->get_position();
        vector2f bailey_pos;
        bailey_pos.x = bailey_object.get_Xpos();
        bailey_pos.y = bailey_object.get_Ypos();
        auto isCollided = collision.bailey_enemy_collision(crab_pos, crab_width, crab_height,
            bailey_pos,bailey_width, bailey_height);

        if (isCollided)
        {
        }
        ++crab_obj_iter;
        ++crab_sprite_iter;
    }
}

void Logic::bailey_bird_collision(vector<shared_ptr<Sprite>>& bird_sprites)
{
    auto bird_obj_iter = birds.begin();
    auto bird_sprite_iter = bird_sprites.begin();
    while (bird_obj_iter != birds.end())
    {
        auto bird_pos = (*bird_obj_iter)->get_position();
        vector2f bailey_pos;
        bailey_pos.x = bailey_object.get_Xpos();
        bailey_pos.y = bailey_object.get_Ypos();
        auto isCollided = collision.bailey_enemy_collision(bird_pos, bird_width,crab_height,
            bailey_pos,bailey_width, bailey_height);

        if (isCollided)
        {
        }
        ++bird_obj_iter;
        ++bird_sprite_iter;
    }
}

Logic::~Logic()
{
    //House keeping, free some memory
    ice_block_objects.clear();
    igloo_object.clear();
    crabs.clear();
    clamps.clear();
    birds.clear();
    fish.clear();
}
