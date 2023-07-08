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
                        update_other_ice(region, _color);
                    }
                    ++NOBI;
                }

                auto isPlayerMoving = player.IsplayerMoving();
                if (!isPlayerMoving)
                {
                    auto ice_direction = (*ice_iter)->get_direction();
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

void CollisionsManager::setBaileyToMoveWithIce(Player& player, const IceDirection& ice_dir,
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