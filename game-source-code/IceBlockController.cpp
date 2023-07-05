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

void IceBlockController::update_iceblocks(vector<shared_ptr<IceBlocks>>& ice,const float deltaTime)
{
    //auto ice_sprite_iter = ice_sprites.begin();
    auto ice_iter = ice.begin();
    auto numberOfIceObjects = ice.size();
    //std::cout << "Number of objects: " <<numberOfIceObjects<< std::endl;
    while(ice_iter != ice.end())
    {
        auto direction = (*ice_iter)->get_direction();
        if (direction == IceDirection::L)
        {
            auto pos_ = (*ice_iter)->get_position();
            pos_.x -= 45 * deltaTime;
            (*ice_iter)->set_position(pos_);
            
            if (pos_.x <= ice_width_offset && numberOfIceObjects < 8)
            {
                R1F = false;
                R2F = false;
                R3F = false;
                R4F = false;
                //crate a new ice and store it in a queue
                auto region = (*ice_iter)->get_region();
                auto color = (*ice_iter)->get_color();
                check_regions(ice);
                create_new_ice(direction, region,color);
            }

            if (pos_.x <= OOBBL)
            {
                ice.erase(ice_iter);
            }
            else
            {
                ++ice_iter;
            }
        }

        else if (direction == IceDirection::R)
        {
             vector2f pos_ = (*ice_iter)->get_position();
             pos_.x += 45 * deltaTime;
             (*ice_iter)->set_position(pos_);
 
            if (pos_.x >= (windowWidth - ice_width_offset) && numberOfIceObjects < 8)
            {
                auto region = (*ice_iter)->get_region();
                R1F = false;
                R2F = false;
                R3F = false;
                R4F = false;

                //crate a new ice and store it in a que
                auto color = (*ice_iter)->get_color();
                check_regions(ice);
                create_new_ice(direction, region,color);
            }

            if (pos_.x >= OOBBR)
            {
                ice.erase(ice_iter);
            }

            else
            {
                ++ice_iter;
            }
        }

    }

    if (!new_ice.empty()) //update ice objects with newly created ice objects
    {
        while (!new_ice.empty())
        {
            ice.push_back(new_ice.front());
            //delete ice objects after they have been updated
            new_ice.pop();
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
    new_ice.push(ice_obj);
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
    new_ice.push(ice_obj);
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
    new_ice.push(ice_obj);
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
    new_ice.push(ice_obj);
}

void IceBlockController::update_ice_texture(vector<shared_ptr<IceBlocks>>& ice)
{
    auto ice_iter= ice.begin();
    while(ice_iter != ice.end())
    {
        auto color = (*ice_iter)->get_color();
        if (color == IceColor::Blue)
        {
            (*ice_iter)->updateIceSprite(blue_ice_texture);
            (*ice_iter)->updateSpritePosition();
        }
        
        else if (color == IceColor::White)
        {
                (*ice_iter)->updateIceSprite(white_ice_texture);
                (*ice_iter)->updateSpritePosition();
        }
        ++ice_iter;
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
