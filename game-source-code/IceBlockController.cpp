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
        auto direction = (*ice_objects_iter)->get_direction();
        if (direction == IceDirection::L)
        {
            (*ice_sprite_iter)->move(-45 * deltaTime, 0);
            auto pos_ = (*ice_sprite_iter)->getPosition();
            (*ice_objects_iter)->set_position(pos_);

            if (pos_.x <= OOBBL)
            {
                //InRX -> In Region X
                auto region = (*ice_objects_iter)->get_region();
                ice_objects.erase(ice_objects_iter);
                ice_sprites.erase(ice_sprite_iter);
                //create new ice batch
                create_new_ice(direction, region, ice_sprites, ice_objects);
                return;
            }
        }

        if (direction == IceDirection::R)
        {
            (*ice_sprite_iter)->move(45 * deltaTime, 0);
            auto pos_ = (*ice_sprite_iter)->getPosition();
            (*ice_objects_iter)->set_position(pos_);

            if (pos_.x >= OOBBR)
            {
                ice_objects.erase(ice_objects_iter);
                ice_sprites.erase(ice_sprite_iter);
                //crate a new ice batch
                return;
            }
        }
        ++ice_sprite_iter;
        ++ice_objects_iter;
    }
}

void IceBlockController::create_new_ice(const IceDirection& direction,const IceRegion& region,
    vector<shared_ptr<Sprite>>& ice_sprites, vector <shared_ptr<IceBlocks>>& ice_objects)
{
    if (direction == IceDirection::L)
    {
        switch (region)
        {
        case IceRegion::R1:
            //create ice in region 1
            create_ice_R1(ice_sprites,ice_objects,direction,region);
            break;
        default:
            break;
        }
    }
}

void IceBlockController::create_ice_R1(vector<shared_ptr<Sprite>>& ice_sprites,
    vector<shared_ptr<IceBlocks>>& ice_objects, const IceDirection& direction, 
    const IceRegion& region)
{
    vector2f _pos;
    _pos.x = 960.0f;
    _pos.y = 305.0f;
    shared_ptr<IceBlocks>ice_obj(new IceBlocks(_pos));
    ice_obj->set_region(region);
    ice_obj->set_direction(direction);
    ice_objects.push_back(ice_obj);

    auto ice_sprite = std::make_shared<Sprite>(Sprite());
    ice_sprite->setOrigin(ice_width / 2.0f, ice_height / 2.0f);
    ice_sprite->setTexture(white_ice_texture);
    ice_sprite->setPosition(_pos);
    ice_sprites.push_back(ice_sprite);
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
