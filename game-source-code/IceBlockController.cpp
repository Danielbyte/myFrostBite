#include "IceBlockController.h"

IceBlockController::IceBlockController()
{
    load_textures();
}

void IceBlockController::update_iceblocks(vector<shared_ptr<IceBlocks>>& ice_objects,vector<shared_ptr<Sprite>>& ice_sprites,
        bool& can_create_new_batch, const float& deltaTime)
{
    auto ice_sprite_iter = ice_sprites.begin();
    auto ice_objects_iter = ice_objects.begin();

    
    while(ice_sprite_iter != ice_sprites.end())
    {

        auto to_left = (*ice_objects_iter) -> get_if_left();
        if (to_left)
        {
            (*ice_sprite_iter) -> move(deltaTime*50.0f,0);
            //pos_.x += 0.7f;
            auto pos_ = (*ice_sprite_iter)->getPosition();
            //(*ice_sprite_iter) -> setPosition(pos_);
            (*ice_objects_iter) -> set_position(pos_);
            if (pos_.x >= 960.0f)
            {
                std::cout << "deleted!" << std::endl;
               // if (pos_.x == 960.0f)
               // {
                    std::cout << "deleted!" << std::endl;
                    ice_objects.erase(ice_objects_iter);
                    ice_sprites.erase(ice_sprite_iter);
                    return;
               // }
                //create new batch of ice
                can_create_new_batch = true;
            }
            else
            {
                //Don't create a new batch of ice
                can_create_new_batch = false;
            }
        }
        else
        {
            (*ice_sprite_iter)->move(-deltaTime * 50.0f, 0);
            auto pos_ = (*ice_sprite_iter) -> getPosition();
            (*ice_objects_iter) -> set_position(pos_);

            if (pos_.x = 160.0f || pos_.x == -160.0f)
            {
                if (pos_.x == -160)
                {
                    std::cout << "Deleted" << std::endl;
                    ice_objects.erase(ice_objects_iter);
                    ice_sprites.erase(ice_sprite_iter);
                    return;
                }
                can_create_new_batch = true;
            }
            else
            {
                can_create_new_batch = false;
            }
        }

        //Update color of ice block texture
        update_ice_texture(ice_sprites,ice_objects);

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
