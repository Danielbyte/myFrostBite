#include "../Header-files/CollisionsManager.h"

CollisionsManager::CollisionsManager():
    NOBI{0},
    playerCollidedWithAnimal{false}
{}

void CollisionsManager::player_ice_collisions(shared_ptr<Player>& player, vector<shared_ptr<IceBlocks>>& ice,
    const float deltaTime, shared_ptr<Igloo>& igloo)
{
    if (player->getState() != PlayerState::Alive)
    {
        return;
    }

    auto collided = false;
    auto playerInSafeZone = player->isPlayerInSafeZone();
    //if frostbite bailey is not in the safe zone, check collisions with ice
    if (!playerInSafeZone)
    {
        auto ice_iter = ice.begin();
        while (ice_iter != ice.end())
        {
            vector2f player_pos;
            auto ice_pos = (*ice_iter)->get_position();
            player_pos = player->getPosition();

            auto isCollided = collision.bailey_ice_collision(player_pos, ice_pos);
            auto color = (*ice_iter)->get_color();
            if (isCollided)
            {
                collided = true;
                if (color == IceColor::White)
                {
                    (*ice_iter)->set_color(IceColor::Blue);
                    igloo->add_igloo_blocks();
                    auto ice_size = ice.size();
                    if (ice_size > 4)
                    {
                        auto _color = (*ice_iter)->get_color();
                        auto region = (*ice_iter)->get_region();
                        update_other_ice(region, _color, ice);
                    }
                    player->incrementBlueIce();
                }

                auto isPlayerMoving = player->IsplayerMoving();
                if (!isPlayerMoving)
                {
                    auto ice_direction = (*ice_iter)->get_direction();
                    //bailey should move with ice if stagnant
                    setPlayerToMoveWithIce(player, ice_direction, deltaTime);

                }
                check_player_on_ice_patch(*ice_iter, player);
                if (player->getState() != PlayerState::Drowning && color == IceColor::White)
                {
                    manage_score.updatePlayerScore(player, "ice");
                }

                //reverse ice direction if player decides to
                auto reverse = player->isReverseBtnPressed();
                auto numberOfIglooBlocks = igloo->get_number_of_igloo_blocks();
                if (reverse && (numberOfIglooBlocks > 0 && numberOfIglooBlocks < 14))
                {
                    reverse_ice_direction(ice, *ice_iter);
                    player->resetReverseBtnPress();
                    igloo->subract_igloo_block();
                }

                numberOfIglooBlocks = igloo->get_number_of_igloo_blocks();
                if (numberOfIglooBlocks == 0)
                {
                    player->resetReverseBtnPress();
                }
            }
            ++ice_iter;
        }

        NOBI = player->NumberOfBlueIceSteepedOn();
        if (NOBI == 4)
        {
            set_all_ice_to_white(ice);
            player->resetBlueIce();
        }
    }

    auto isJumping = player->isPlayerJumping();
   if (!collided && !playerInSafeZone && !isJumping) 
   {
       player->setState(PlayerState::Drowning);
   }

   if (player->getState() == PlayerState::Drowning)
   {
       player->subractLive();
       player->restartWatch();
   }

    auto isIglooComplete = igloo->isComplete();
    if (isIglooComplete)
    {
        set_all_ice_to_blue(ice);
    }
}

void CollisionsManager::setPlayerToMoveWithIce(shared_ptr<Player>& player, const IceDirection& ice_dir,
    const float& deltaTime)
{
    switch (ice_dir)
    {
    case IceDirection::L:
        player->setPlayerToMoveWithIce(Direction::Left, deltaTime);
        break;

    case IceDirection::R:
        player->setPlayerToMoveWithIce(Direction::Right, deltaTime);
        break;

    default:
        break;
    }
}

void CollisionsManager::check_player_on_ice_patch(shared_ptr<IceBlocks>& ice_ptr, shared_ptr<Player>& player)
{
    auto ice_x_pos = (ice_ptr->get_position()).x - ice_width_offset;
    auto bailey_x_pos = player->getPosition().x - bailey_width_offset;
    auto point1_offset = 37.0f;
    auto point1 = ice_x_pos - point1_offset;
    auto point2_offset = 26.0f;
    auto point2 = (ice_x_pos + point2_offset) + ice_patch_width;
    auto EOI_offset = 16.0f; // end of ice offset
    auto end_of_ice = ice_x_pos + ice_width - EOI_offset;
    player->setState(PlayerState::Drowning);

    if (bailey_x_pos >= point1 && bailey_x_pos <= end_of_ice)
    {
        if (bailey_x_pos >= point1 && ((bailey_x_pos + bailey_width) <= point2))
        {
            player->setState(PlayerState::Alive);
        }

        auto point3_offset = 26.5f;
        auto point3 = point2 - point3_offset;
        auto point4_offset = 50.5f;
        auto point4 = point3 + ice_patch_width + point4_offset;
        if (bailey_x_pos >= point3 && ((bailey_x_pos + bailey_width) <= point4))
        {
            player->setState(PlayerState::Alive);
        }

        auto point5_offset = 29.8f;
        auto point5 = point4 - point5_offset;
        if (bailey_x_pos >= point5)
        {
            player->setState(PlayerState::Alive);
        }

    }
}

void CollisionsManager::update_other_ice(const IceRegion region, const IceColor color,
    vector<shared_ptr<IceBlocks>>& ice)
{
    auto ice_iter = ice.begin();

    while (ice_iter != ice.end())
    {
        auto _region = (*ice_iter)->get_region();
        if (_region == region)
        {
            (*ice_iter)->set_color(color);
        }
        ++ice_iter;
    }
}

void CollisionsManager::set_all_ice_to_white(vector<shared_ptr<IceBlocks>>& ice)
{
    auto ice_iter = ice.begin();
    while (ice_iter != ice.end())
    {
        (*ice_iter)->set_color(IceColor::White);
        ++ice_iter;
    }
}

void CollisionsManager::set_all_ice_to_blue(vector<shared_ptr<IceBlocks>>& ice)
{
    auto iter = ice.begin();
    while (iter != ice.end())
    {
        (*iter)->set_color(IceColor::Blue);
        (*iter)->set_color(IceColor::Blue);
        ++iter;
    }
}

void CollisionsManager::reverse_ice_direction(vector<shared_ptr<IceBlocks>>& ice,shared_ptr<IceBlocks>& ice_ptr)
{
            auto region = ice_ptr->get_region();
            IceDirection temp_direction = IceDirection::S;
            auto dir = ice_ptr->get_direction();

            if (dir == IceDirection::L)
            {
                ice_ptr->set_direction(IceDirection::R);
                //igloo_object->subract_igloo_block();
                //igloo_object->update_igloo(igloo_sprites);
                temp_direction = IceDirection::R;
            }
            if (dir == IceDirection::R)
            {
                ice_ptr->set_direction(IceDirection::L);
                // igloo_object->subract_igloo_block();
                // igloo_object->update_igloo(igloo_sprites);
                temp_direction = IceDirection::L;
            }

            auto numberOfIce = ice.size();
            if (numberOfIce > 4)
            {
                updateOtherIceToChangeDirection(region, temp_direction, ice);
            }      
}

void CollisionsManager::updateOtherIceToChangeDirection(const IceRegion& region, const IceDirection& direction,
    vector<shared_ptr<IceBlocks>>& ice)
{
    auto iter = ice.begin();
    while (iter != ice.end())
    {
        auto _region = (*iter)->get_region();

        if (_region == region)
        {
            (*iter)->set_direction(direction);
        }
        ++iter;
    }
}

void CollisionsManager::player_animal_collisions(shared_ptr<Player>& player, vector<shared_ptr<Crab>>& _crabs,
    vector<shared_ptr<Clamp>>& _clamps, vector<shared_ptr<Bird>>& _birds,vector<shared_ptr<Fish>>& _fish)
{
    if (player->getState() != PlayerState::Alive)
    {
        return;
    }

    playerCollidedWithAnimal = false;
    auto isFish = false;
    region_collisions(player, _crabs, crab_width, crab_height, isFish);
    region_collisions(player, _clamps, crab_width, crab_height, isFish);
    region_collisions(player, _birds, bird_width, bird_height, isFish);
    isFish = true;
    region_collisions(player, _fish, fish_width, fish_height, isFish);

    if (playerCollidedWithAnimal)
    {
        player->setState(PlayerState::AttackedBySeaAnimal);
        player->subractLive();
        if (player->getState() != PlayerState::Dead)
        {
            player->restartWatch();
        }
    }
}

void CollisionsManager::player_bear_collisions(shared_ptr<Bear>& bear, shared_ptr<Player>& player)
{
    if (player->getState() != PlayerState::Alive)
    {
        return;
    }

    auto bear_position = bear->get_position();
    vector2f player_position = player->getPosition();


    auto isCollided = collision.entity_collision(player_position, bailey_width, bailey_height,
        bear_position, bear_with, bear_height);

    //bailey needs to be in safe zone
    auto baileyInSafeZone = player->isPlayerInSafeZone();
    if (isCollided && baileyInSafeZone)
    {
        player->setState(PlayerState::AttackedByBear);
        player->subractLive();
        if (player->getState() != PlayerState::Dead)
        {
            player->restartWatch();
        }
    }
}