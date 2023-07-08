#include "CollisionsManager.h"

CollisionsManager::CollisionsManager():
    NOBI{0}
{}

void CollisionsManager::player_ice_collisions(Player& player, vector<shared_ptr<IceBlocks>>& ice,
    const float deltaTime)
{
    auto collided = false;
    auto playerInSafeZone = player.isPlayerInSafeZone();
    //if frostbite bailey is not in the safe zone, check collisions with ice
    if (!playerInSafeZone)
    {
        auto ice_iter = ice.begin();
        while (ice_iter != ice.end())
        {
            vector2f player_pos;
            auto ice_pos = (*ice_iter)->get_position();
            player_pos = player.getPosition();

            auto isCollided = collision.bailey_ice_collision(player_pos, ice_pos);
            auto color = (*ice_iter)->get_color();
            if (isCollided)
            {
                collided = true;
                if (color == IceColor::White)
                {
                    (*ice_iter)->set_color(IceColor::Blue);
                    //igloo_object->add_igloo_blocks();
                    //igloo_object->update_igloo(IglooHouseSprite);
                    auto ice_size = ice.size();
                    if (ice_size > 4)
                    {
                        auto _color = (*ice_iter)->get_color();
                        auto region = (*ice_iter)->get_region();
                        update_other_ice(region, _color, ice);
                    }
                    ++NOBI;
                }

                auto isPlayerMoving = player.IsplayerMoving();
                if (!isPlayerMoving)
                {
                    auto ice_direction = (*ice_iter)->get_direction();
                    //bailey should move with ice if stagnant
                    setPlayerToMoveWithIce(player, ice_direction, deltaTime);

                }
                check_player_on_ice_patch(*ice_iter, player);
            }

            ++ice_iter;
        }

        if (NOBI == 4)
        {
            set_all_ice_to_white(ice);
            NOBI = 0;
        }
    }

    /*auto isIglooComplete = mark_if_igloo_is_complete();
    if (isIglooComplete)
    {
        set_all_ice_batches_to_blue();
    }*/
}

void CollisionsManager::setPlayerToMoveWithIce(Player& player, const IceDirection& ice_dir,
    const float& deltaTime)
{
    switch (ice_dir)
    {
    case IceDirection::L:
        player.setPlayerToMoveWithIce(Direction::Left, deltaTime);
        break;

    case IceDirection::R:
        player.setPlayerToMoveWithIce(Direction::Right, deltaTime);
        break;

    default:
        break;
    }
}

void CollisionsManager::check_player_on_ice_patch(shared_ptr<IceBlocks>& ice_ptr, Player& player)
{
    auto ice_x_pos = (ice_ptr->get_position()).x - ice_width_offset;
    auto bailey_x_pos = player.getPosition().x - bailey_width_offset;
    auto point1_offset = 37.0f;
    auto point1 = ice_x_pos - point1_offset;
    auto point2_offset = 26.0f;
    auto point2 = (ice_x_pos + point2_offset) + ice_patch_width;
    auto EOI_offset = 16.0f; // end of ice offset
    auto end_of_ice = ice_x_pos + ice_width - EOI_offset;
    player.playerShouldDrown(true);

    if (bailey_x_pos >= point1 && bailey_x_pos <= end_of_ice)
    {
        if (bailey_x_pos >= point1 && ((bailey_x_pos + bailey_width) <= point2))
        {
            player.playerShouldDrown(false);
        }

        auto point3_offset = 26.5f;
        auto point3 = point2 - point3_offset;
        auto point4_offset = 50.5f;
        auto point4 = point3 + ice_patch_width + point4_offset;
        if (bailey_x_pos >= point3 && ((bailey_x_pos + bailey_width) <= point4))
        {
            player.playerShouldDrown(false);
        }

        auto point5_offset = 29.8f;
        auto point5 = point4 - point5_offset;
        if (bailey_x_pos >= point5)
        {
            player.playerShouldDrown(false);
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