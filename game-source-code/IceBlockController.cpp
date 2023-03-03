#include "IceBlockController.h"

IceBlockController::IceBlockController():
    R1F{false},
    R2F{false},
    R3F{false},
    R4F{false}
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
    auto numberOfIceObjects = ice_objects.size();
    //std::cout << "Number of objects: " <<numberOfIceObjects<< std::endl;
    while(ice_sprite_iter != ice_sprites.end())
    {
        auto direction = (*ice_objects_iter)->get_direction();
        if (direction == IceDirection::L)
        {
            (*ice_sprite_iter)->move(-45 * deltaTime, 0);
            auto pos_ = (*ice_sprite_iter)->getPosition();
            (*ice_objects_iter)->set_position(pos_);
            
            if (pos_.x <= ice_width_offset && numberOfIceObjects < 8)
            {
                R1F = false;
                R2F = false;
                R3F = false;
                R4F = false;
                //crate a new ice and store it in a queue
                auto region = (*ice_objects_iter)->get_region();
                auto color = (*ice_objects_iter)->get_color();
                check_regions(ice_objects);
                create_new_ice(direction, region,color);
            }

            if (pos_.x <= OOBBL)
            {
                auto region = (*ice_objects_iter)->get_region();
                //if (region == IceRegion::R1) { std::cout << "Region1 deleted: " << std::endl; }
                ice_objects.erase(ice_objects_iter);
                ice_sprites.erase(ice_sprite_iter);
            }
            else
            {
                ++ice_sprite_iter;
                ++ice_objects_iter;
            }
        }

        else if (direction == IceDirection::R)
        {
             (*ice_sprite_iter)->move(45 * deltaTime, 0);
             vector2f pos_ = (*ice_sprite_iter)->getPosition();
             (*ice_objects_iter)->set_position(pos_);
             auto rg = (*ice_objects_iter)->get_region();
             //if (rg == IceRegion::R1) { std::cout << "Position1: "<<pos_.x << std::endl; }
             
            if (pos_.x >= (windowWidth - ice_width_offset) && numberOfIceObjects < 8)
            {
                auto region = (*ice_objects_iter)->get_region();
                R1F = false;
                R2F = false;
                R3F = false;
                R4F = false;

                //crate a new ice and store it in a que
                auto color = (*ice_objects_iter)->get_color();
                check_regions(ice_objects);
                create_new_ice(direction, region,color);
            }

            if (pos_.x >= OOBBR)
            {
                ice_objects.erase(ice_objects_iter);
                ice_sprites.erase(ice_sprite_iter);
            }

            else
            {
                ++ice_sprite_iter;
                ++ice_objects_iter;
            }
        }

    }

    if (!new_ice_objects.empty()) //update ice objects with newly created ice objects
    {
        while (!new_ice_objects.empty())
        {
            ice_objects.push_back(new_ice_objects.front());
            ice_sprites.push_back(new_ice_sprites.front());
            //delete ice objects after they have been updated
            new_ice_sprites.pop();
            new_ice_objects.pop();
        }
    }
}

void IceBlockController::create_new_ice(const IceDirection& direction,const IceRegion& region,
    const IceColor& color)
{
        switch (region)
        {
        case IceRegion::R1:
            //create ice in region 1
            if(!R1F){ create_ice_R1(direction, region, color); }
            break;

        case IceRegion::R2:
            if(!R2F){ create_ice_R2(direction, region, color); }
            break;

        case IceRegion::R3:
            if(!R3F){ create_ice_R3(direction, region, color); }
            break;

        case IceRegion::R4:
            if(!R4F){ create_ice_R4(direction, region, color); }
            break;

        default:
            break;
        }
}

void IceBlockController::create_ice_R1(const IceDirection& direction, const IceRegion& region,
    const IceColor& color)
{
    vector2f _pos;
    auto y_pos = 305.0f;
    set_position(direction, _pos, y_pos);
    shared_ptr<IceBlocks>ice_obj(new IceBlocks(_pos));
    ice_obj->set_region(region);
    ice_obj->set_direction(direction);
    ice_obj->set_color(color);
    new_ice_objects.push(ice_obj);

    auto ice_sprite = std::make_shared<Sprite>(Sprite());
    ice_sprite->setOrigin(ice_width / 2.0f, ice_height / 2.0f);
    ice_sprite->setTexture(white_ice_texture);
    ice_sprite->setPosition(_pos);
    new_ice_sprites.push(ice_sprite);
}

void IceBlockController::create_ice_R2(const IceDirection& direction, const IceRegion& region,
    const IceColor& color)
{
    vector2f _pos;
    auto y_pos = 387.0f;
    set_position(direction, _pos, y_pos);
    shared_ptr<IceBlocks>ice_obj(new IceBlocks(_pos));
    ice_obj->set_region(region);
    ice_obj->set_direction(direction);
    ice_obj->set_color(color);
    new_ice_objects.push(ice_obj);

    auto ice_sprite = std::make_shared<Sprite>(Sprite());
    ice_sprite->setOrigin(ice_width / 2.0f, ice_height / 2.0f);
    ice_sprite->setTexture(white_ice_texture);
    ice_sprite->setPosition(_pos);
    new_ice_sprites.push(ice_sprite);
}

void IceBlockController::create_ice_R3(const IceDirection& direction,const IceRegion& region,
    const IceColor& color)
{
    vector2f _pos;
    auto y_pos = 469.0f;
    set_position(direction, _pos, y_pos);
    shared_ptr<IceBlocks>ice_obj(new IceBlocks(_pos));
    ice_obj->set_region(region);
    ice_obj->set_direction(direction);
    ice_obj->set_color(color);
    new_ice_objects.push(ice_obj);

    auto ice_sprite = std::make_shared<Sprite>(Sprite());
    ice_sprite->setOrigin(ice_width / 2.0f, ice_height / 2.0f);
    ice_sprite->setTexture(white_ice_texture);
    ice_sprite->setPosition(_pos);
    new_ice_sprites.push(ice_sprite);
}

void IceBlockController::create_ice_R4(const IceDirection& direction,const IceRegion& region,
    const IceColor& color)
{
    vector2f _pos;
    auto y_pos = 551.0f;
    set_position(direction, _pos, y_pos);
    shared_ptr<IceBlocks>ice_obj(new IceBlocks(_pos));
    ice_obj->set_region(region);
    ice_obj->set_direction(direction);
    ice_obj->set_color(color);
    new_ice_objects.push(ice_obj);

    auto ice_sprite = std::make_shared<Sprite>(Sprite());
    ice_sprite->setOrigin(ice_width / 2.0f, ice_height / 2.0f);
    ice_sprite->setTexture(white_ice_texture);
    ice_sprite->setPosition(_pos);
    new_ice_sprites.push(ice_sprite);
}

void IceBlockController::update_ice_texture(vector<shared_ptr<Sprite>>& ice_sprites, 
    vector<shared_ptr<IceBlocks>>& ice_objects)
{
    auto iter = ice_sprites.begin();
    auto obj_iter= ice_objects.begin();
    while(obj_iter != ice_objects.end())
    {
        auto color = (*obj_iter)->get_color();
        if (color == IceColor::Blue)
        {
            (*iter) -> setTexture(blue_ice_texture);
        }
        
        else if (color == IceColor::White)
        {
                (*iter) -> setTexture(white_ice_texture);
        }

        ++obj_iter;
        ++iter;
    }
}

void IceBlockController::set_position(const IceDirection& direction, vector2f& _pos,const float& y)
{
    switch (direction)
    {
    case IceDirection::L:
        _pos.x = OOBBR;
        _pos.y = y;
        break;
    case IceDirection::R:
        _pos.x = OOBBL;
        _pos.y = y;
        break;
    default:
        break;
    }
}

void IceBlockController::check_regions(const vector<shared_ptr<IceBlocks>>& ice_objects)
{
    int counter1 = 0, counter2 = 0, counter3 = 0, counter4 = 0;
    auto iter = ice_objects.begin();
    while (iter != ice_objects.end())
    {
        auto region = (*iter)->get_region();
        switch (region)
        {
        case IceRegion::R1:
            ++counter1;
            break;
        case IceRegion::R2:
            ++counter2;
            break;
        case IceRegion::R3:
            ++counter3;
            break;
        case IceRegion::R4:
            ++counter4;
            break;
        case IceRegion::unknown:
            break;
        default:
            break;
        }
        ++iter;
    }

    if (counter1 == 2) { R1F = true; }
    if (counter2 == 2) { R2F = true; }
    if (counter3 == 2) { R3F = true; }
    if (counter4 == 2) { R4F = true; }
}

void IceBlockController::load_textures()
{
    //Load textures once for optimization
    white_ice_texture.loadFromFile("resources/whiteIce.png");
    blue_ice_texture.loadFromFile("resources/blueice.png");

}
