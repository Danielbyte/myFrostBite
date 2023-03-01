#include "IceBlockController.h"

IceBlockController::IceBlockController()
{
    load_textures();
    OOBBL = -ice_width_offset;
    OOBBR = windowWidth + ice_width_offset;
}

void IceBlockController::update_iceblocks(vector<shared_ptr<IceBlocks>>& ice_objects,
    vector<shared_ptr<Sprite>>& ice_sprites, const float& deltaTime)
{
    auto ice_sprite_iter = ice_sprites.begin();
    auto ice_objects_iter = ice_objects.begin();

    while(ice_sprite_iter != ice_sprites.end())
    {
        auto [isToLeft, isToRight] = (*ice_objects_iter)->get_direction();
        if (isToLeft)
        {
            (*ice_sprite_iter)->move(-45 * deltaTime, 0);
            auto pos_ = (*ice_sprite_iter)->getPosition();
            (*ice_objects_iter)->set_position(pos_);

            if (pos_.x <= OOBBL)
            {
                ice_objects.erase(ice_objects_iter);
                ice_sprites.erase(ice_sprite_iter);
                return;
            }
        }

        if (isToRight)
        {
            (*ice_sprite_iter)->move(45 * deltaTime, 0);
            auto pos_ = (*ice_sprite_iter)->getPosition();
            (*ice_objects_iter)->set_position(pos_);

            if (pos_.x >= OOBBR)
            {
                ice_objects.erase(ice_objects_iter);
                ice_sprites.erase(ice_sprite_iter);
                return;
            }
        }
        ++ice_sprite_iter;
        ++ice_objects_iter;
    }
}

void IceBlockController::update_ice_texture(vector<shared_ptr<Sprite>>& ice_sprites, vector<shared_ptr<IceBlocks>>& ice_objects)
{
    auto iter = ice_sprites.begin();
    auto obj_iter = ice_objects.begin();
    while(iter != ice_sprites.end())
    {
        auto isBlue = (*obj_iter) -> get_if_blue();
        auto isWhite = (*obj_iter) -> get_if_white();
        if (isBlue)
        {
            (*iter) -> setTexture(blue_ice_texture);
        }

        else if (isWhite)
            {
                (*iter) -> setTexture(white_ice_texture);
            }
        ++iter;
        ++obj_iter;
    }
}

void IceBlockController::load_textures()
{
    //Load textures once for optimization
    white_ice_texture.loadFromFile("resources/whiteIce.png");
    blue_ice_texture.loadFromFile("resources/blueice.png");

}
