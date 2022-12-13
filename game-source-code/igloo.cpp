#include "igloo.h"

Igloo::Igloo():
    x_position{612.0f},
    y_position{147.0f},
    igloo_blocks{0}
{}

float Igloo::get_x_position() const
{
    return x_position;
}

float Igloo::get_y_position() const
{
    return y_position;
}

void Igloo::build_igloo(vector<shared_ptr<Sprite>>& igloo_sprites)
{
    auto ptr = igloo_sprites.begin();
    update_igloo(*ptr,igloo_sprites);
}

void Igloo::add_igloo_blocks()
{
    //If igloo is complete, keep bricks capped at 14.
    if (igloo_blocks < 14)
    {
        ++igloo_blocks;
    }
    else
    {
        igloo_blocks = 14;
    }
}

void Igloo::subract_igloo_block()
{
     igloo_blocks -= 1;

     //reset igloo blocks if they are less than zero
    if (igloo_blocks < 0)
    {
        igloo_blocks = 0;
    }
}

int Igloo::get_number_of_igloo_blocks() const
{
    return igloo_blocks;
}

void Igloo::update_igloo(shared_ptr<Sprite>& ptr, vector<shared_ptr<Sprite>>& igloo_sprite)
{
    if (igloo_blocks == 0)
    {
        igloo_texture.loadFromFile("resources/igloo0.png");
        ptr->setOrigin(igloo_width / 2.0f, igloo_height / 2.0f);
        ptr->setTexture(igloo_texture);
        ptr->setPosition(x_position, y_position);
        igloo_sprite.push_back(ptr);
        return;
    }

    else if (igloo_blocks == 1)
    {
        auto ptr1 = igloo_sprite.begin();
        igloo_texture.loadFromFile("resources/igloo1.png");
        ptr -> setOrigin(igloo_width / 2.0f, igloo_height / 2.0f);
        ptr ->setTexture(igloo_texture);
        ptr -> setPosition(x_position, y_position);
        igloo_sprite.push_back(ptr);
        return;
    }

    else if (igloo_blocks == 2)
    {
        igloo_texture.loadFromFile("resources/igloo2.png");
        ptr -> setOrigin(igloo_width / 2.0f, igloo_height / 2.0f);
        ptr -> setTexture(igloo_texture);
        ptr -> setPosition(x_position, y_position);
        return;
    }

    else if (igloo_blocks == 3)
    {
        igloo_texture.loadFromFile("resources/igloo3.png");
        ptr -> setOrigin(igloo_width / 2.0f, igloo_height / 2.0f);
        ptr -> setTexture(igloo_texture);
        ptr -> setPosition(x_position, y_position);
        return;
    }

    else if (igloo_blocks == 4)
    {
        igloo_texture.loadFromFile("resources/igloo4.png");
        ptr -> setOrigin(igloo_width / 2.0f, igloo_height / 2.0f);
        ptr -> setTexture(igloo_texture);
        ptr -> setPosition(x_position, y_position);
        return;
    }

    else if (igloo_blocks == 5)
    {
        igloo_texture.loadFromFile("resources/igloo5.png");
        ptr -> setOrigin(igloo_width / 2.0f, igloo_height / 2.0f);
        ptr -> setTexture(igloo_texture);
        ptr -> setPosition(x_position, y_position);
        return;
    }

    else if (igloo_blocks == 6)
    {
        igloo_texture.loadFromFile("resources/igloo6.png");
        ptr -> setOrigin(igloo_width / 2.0f, igloo_height / 2.0f);
        ptr -> setTexture(igloo_texture);
        ptr -> setPosition(x_position, y_position);
        return;
    }

    else if (igloo_blocks == 7)
    {
        igloo_texture.loadFromFile("resources/igloo7.png");
        ptr -> setOrigin(igloo_width / 2.0f, igloo_height / 2.0f);
        ptr -> setTexture(igloo_texture);
        ptr -> setPosition(x_position, y_position);
        return;
    }

    else if (igloo_blocks == 8)
    {
        igloo_texture.loadFromFile("resources/igloo8.png");
        ptr -> setOrigin(igloo_width / 2.0f, igloo_height / 2.0f);
        ptr -> setTexture(igloo_texture);
        ptr -> setPosition(x_position, y_position);
        return;
    }

    else if (igloo_blocks == 9)
    {
        igloo_texture.loadFromFile("resources/igloo9.png");
        ptr -> setOrigin(igloo_width / 2.0f, igloo_height / 2.0f);
        ptr -> setTexture(igloo_texture);
        ptr -> setPosition(x_position, y_position);
        return;
    }

    else if (igloo_blocks == 10)
    {
        igloo_texture.loadFromFile("resources/igloo10.png");
        ptr -> setOrigin(igloo_width / 2.0f, igloo_height / 2.0f);
        ptr -> setTexture(igloo_texture);
        ptr -> setPosition(x_position, y_position);
        return;
    }

    else if (igloo_blocks == 11)
    {
        igloo_texture.loadFromFile("resources/igloo11.png");
        ptr -> setOrigin(igloo_width / 2.0f, igloo_height / 2.0f);
        ptr -> setTexture(igloo_texture);
        ptr -> setPosition(x_position, y_position);
        return;
    }

    else if (igloo_blocks == 12)
    {
        igloo_texture.loadFromFile("resources/igloo12.png");
        ptr -> setOrigin(igloo_width / 2.0f, igloo_height / 2.0f);
        ptr -> setTexture(igloo_texture);
        ptr -> setPosition(x_position, y_position);
        return;
    }

    else if (igloo_blocks == 13)
    {
        igloo_texture.loadFromFile("resources/igloo13.png");
        ptr -> setOrigin(igloo_width / 2.0f, igloo_height / 2.0f);
        ptr -> setTexture(igloo_texture);
        ptr -> setPosition(x_position, y_position);
        return;
    }

    else if (igloo_blocks == 14)
    {
        igloo_texture.loadFromFile("resources/igloo14.png");
        ptr -> setOrigin(igloo_width / 2.0f, igloo_height / 2.0f);
        ptr -> setTexture(igloo_texture);
        ptr -> setPosition(x_position, y_position);
        return;
    }
}



