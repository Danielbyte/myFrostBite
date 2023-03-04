#include "Logic.h"

Logic::Logic():
    is_bailey_moving{false},
    is_igloo_complete{false},
    y_{0.0f},
    plungedInWater{true},
    NOBI{0},
    BaileyCollidedWithSeaAnimal{false}

{
    prev_pos.x = 240.0f; //Initial bailey position
    prev_pos.y = 205.0f; // Initial bailey position
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
        _pos3.y = 469.0f;
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
    ice_block_controller.update_ice_texture(ice_block_sprites, ice_block_objects);
}

bool Logic::bailey_and_ice_collision(shared_ptr<Sprite>& IglooHouseSprite,Sprite& bailey_sprite,
    const float& deltaTime)
{
    auto collided = false;
    auto isBaileyInSafeZone = bailey_object.get_if_bailey_in_safe_zone();
    //if frostbite bailey is not in the safe zone, check collisions with ice
    if (!isBaileyInSafeZone)
    {
        auto iceObj_iter = ice_block_objects.begin();
        while (iceObj_iter != ice_block_objects.end())
        {
            vector2f bailey_pos;
            auto ice_pos = (*iceObj_iter)->get_position();
            bailey_pos.x = bailey_object.get_Xpos();
            bailey_pos.y = bailey_object.get_Ypos();

            auto isCollided = collision.bailey_ice_collision(bailey_pos, ice_pos);
            auto color = (*iceObj_iter)->get_color();
            if (isCollided)
            {
                collided = true;
                if (color == IceColor::White)
                {
                    (*iceObj_iter)->set_color(IceColor::Blue);
                    igloo_object->add_igloo_blocks();
                    igloo_object->update_igloo(IglooHouseSprite);
                    auto ice_size = ice_block_objects.size();
                    if (ice_size > 4)
                    {
                        auto _color = (*iceObj_iter)->get_color();
                        auto region = (*iceObj_iter)->get_region();
                        update_other_ice(region, _color);
                    }
                    ++NOBI;
                }

                if (!is_bailey_moving)
                {
                    auto ice_direction = (*iceObj_iter)->get_direction();
                    //bailey should move with ice if stagnant
                    setBaileyToMoveWithIce(bailey_sprite, ice_direction, deltaTime);

                }
                check_frostbite_on_ice_patch(*iceObj_iter);
            }

            ++iceObj_iter;
        }

        if (NOBI == 4)
        {
            set_all_ice_to_white();
            NOBI = 0;
        }
    }

    auto isIglooComplete = mark_if_igloo_is_complete();
    if (isIglooComplete)
    {
        set_all_ice_batches_to_blue();
    }

    if (plungedInWater) { collided = false; }

    return collided;
}

void Logic::set_all_ice_batches_to_blue()
{
    auto iter = ice_block_objects.begin();
    while(iter != ice_block_objects.end())
    {
        (*iter) -> set_color(IceColor::Blue);
        (*iter) -> set_color(IceColor::Blue);
        ++iter;
    }
}

bool Logic::mark_if_igloo_is_complete()
{
    auto blocks = get_number_of_igloo_blocks();
    if (blocks == 14)
    {
        return true;
    }
    else
        return false;
}

int Logic::get_number_of_igloo_blocks()
{
    auto blocks = igloo_object->get_number_of_igloo_blocks();
    return blocks;
}

void Logic::set_all_ice_to_white()
{
    auto ice_iter = ice_block_objects.begin();
    while (ice_iter != ice_block_objects.end())
    {
        (*ice_iter)->set_color(IceColor::White);
        ++ice_iter;
    }
}

void Logic::update_other_ice(const IceRegion& region, const IceColor& color)
{
    auto obj_iter = ice_block_objects.begin();

    while (obj_iter != ice_block_objects.end())
    {
        auto _region = (*obj_iter)->get_region();
        if (_region == region)
        {
            (*obj_iter)->set_color(color);
        }
        ++obj_iter;
    }
}

void Logic::setBaileyToMoveWithIce(Sprite& bailey_sprite, const IceDirection& ice_dir,
    const float& deltaTime)
{
    switch (ice_dir)
    {
    case IceDirection::L:
        bailey_object.setBaileyToMoveWithIce(Direction::Left, bailey_sprite, deltaTime);
        break;

    case IceDirection::R:
        bailey_object.setBaileyToMoveWithIce(Direction::Right, bailey_sprite, deltaTime);
        break;

    default:
        break;
    }
}

void Logic::reverse_ice_direction(shared_ptr<Sprite>& igloo_sprites)
{
    auto obj_iter = ice_block_objects.begin();
    while (obj_iter != ice_block_objects.end())
    {
        vector2f bailey_pos;
        auto ice_pos = (*obj_iter)->get_position();
        bailey_pos.x = bailey_object.get_Xpos();
        bailey_pos.y = bailey_object.get_Ypos();
        auto isCollided = collision.bailey_ice_collision(bailey_pos, ice_pos);
        auto region = (*obj_iter)->get_region();
     
        if (isCollided)
        {
            IceDirection temp_direction = IceDirection::S;
            auto dir = (*obj_iter)->get_direction();
            if (dir == IceDirection::L)
            {
                (*obj_iter)->set_direction(IceDirection::R);
                igloo_object->subract_igloo_block();
                igloo_object->update_igloo(igloo_sprites);
                temp_direction = IceDirection::R;
            }
             if (dir == IceDirection::R)
            {
                (*obj_iter)->set_direction(IceDirection::L);
                igloo_object->subract_igloo_block();
                igloo_object->update_igloo(igloo_sprites);
                temp_direction = IceDirection::L;
            }
             auto numberOfIceObjects = ice_block_objects.size();
             if (numberOfIceObjects > 4)
             {
                 updateOtherIceToChangeDirection(region, temp_direction);
             }
        }

        ++obj_iter;
    }
}

void Logic::updateOtherIceToChangeDirection(const IceRegion& region, const IceDirection& direction)
{
    auto iter = ice_block_objects.begin();
    while (iter != ice_block_objects.end())
    {
        auto _region = (*iter)->get_region();

        if (_region == region)
        {
            (*iter)->set_direction(direction);
        }
        ++iter;
    }
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

void Logic::freezing_bailey_animation(const float& deltaTime, Sprite& bailey_sprite)
{
    control_bailey.freezing_animation(deltaTime, bailey_sprite);
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

void Logic::baileyCollisionWithSeaCreatureAnimation(const float& deltaTime, Sprite& bailey_sprite)
{
    control_bailey.collision_with_sea_animal(deltaTime, bailey_sprite);
}

void Logic::updateBaileyAndSeaAnimalCollisions(vector<shared_ptr<Sprite>>& crab_sprites,
    vector<shared_ptr<Sprite>>& clamp_sprites, vector<shared_ptr<Sprite>>& bird_sprites,
    vector<shared_ptr<Sprite>>& fish_sprites)
{
    BaileyCollidedWithSeaAnimal = false;
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
            BaileyCollidedWithSeaAnimal = true;
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
            BaileyCollidedWithSeaAnimal = true;
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
            BaileyCollidedWithSeaAnimal = true;
        }
        ++bird_obj_iter;
        ++bird_sprite_iter;
    }
}

bool Logic::getIfCollidedWithSeaAnimal() const
{
    return BaileyCollidedWithSeaAnimal;
}

Logic::~Logic()
{
    //House keeping, free some memory
    ice_block_objects.clear();
    crabs.clear();
    clamps.clear();
    birds.clear();
    fish.clear();
}
