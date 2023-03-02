#include "igloo.h"

Igloo::Igloo():
    x_position{612.0f},
    y_position{130.0f},
    igloo_blocks{0}
{
    load_textures();
}

float Igloo::get_x_position() const
{
    return x_position;
}

float Igloo::get_y_position() const
{
    return y_position;
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

void Igloo::update_igloo(shared_ptr<Sprite>& igloo_sprite)
{
    if (igloo_blocks == 0)
    {
        igloo_sprite->setTexture(igloo_texture1);
        igloo_sprite->setPosition(x_position, y_position);
        return;
    }

    else if (igloo_blocks == 1)
    {
        igloo_sprite->setTexture(igloo_texture2);
        igloo_sprite->setPosition(x_position, y_position);
        return;
    }

    else if (igloo_blocks == 2)
    {

        igloo_sprite -> setTexture(igloo_texture3);
        igloo_sprite->setPosition(x_position, y_position);
        return;
    }

    else if (igloo_blocks == 3)
    {
        igloo_sprite -> setTexture(igloo_texture4);
        igloo_sprite->setPosition(x_position, y_position);
        return;
    }

    else if (igloo_blocks == 4)
    {
        igloo_sprite -> setTexture(igloo_texture5);
        igloo_sprite->setPosition(x_position, y_position);
        return;
    }

    else if (igloo_blocks == 5)
    {
        igloo_sprite->setTexture(igloo_texture6);
        igloo_sprite->setPosition(x_position, y_position);
        return;
    }

    else if (igloo_blocks == 6)
    {
        igloo_sprite -> setTexture(igloo_texture7);
        igloo_sprite->setPosition(x_position, y_position);
        return;
    }

    else if (igloo_blocks == 7)
    {
        igloo_sprite -> setTexture(igloo_texture8);
        igloo_sprite->setPosition(x_position, y_position);
        return;
    }

    else if (igloo_blocks == 8)
    {
        igloo_sprite -> setTexture(igloo_texture9);
        igloo_sprite->setPosition(x_position, y_position);
        return;
    }

    else if (igloo_blocks == 9)
    {
        igloo_sprite -> setTexture(igloo_texture10);
        igloo_sprite->setPosition(x_position, y_position);
        return;
    }

    else if (igloo_blocks == 10)
    {

        igloo_sprite -> setTexture(igloo_texture11);
        igloo_sprite->setPosition(x_position, y_position);
        return;
    }

    else if (igloo_blocks == 11)
    {
        igloo_sprite -> setTexture(igloo_texture12);
        igloo_sprite->setPosition(x_position, y_position);
        return;
    }

    else if (igloo_blocks == 12)
    {
        igloo_sprite -> setTexture(igloo_texture13);
        igloo_sprite->setPosition(x_position, y_position);
        return;
    }

    else if (igloo_blocks == 13)
    {
        igloo_sprite -> setTexture(igloo_texture14);
        igloo_sprite->setPosition(x_position, y_position);
        return;
    }

    else if (igloo_blocks == 14)
    {
        igloo_sprite -> setTexture(igloo_texture15);
        igloo_sprite->setPosition(x_position, y_position);
        return;
    }
}

void Igloo::load_textures()
{
    //load textures only once
    igloo_texture1.loadFromFile("resources/igloo0.png");
    igloo_texture2.loadFromFile("resources/igloo1.png");
    igloo_texture3.loadFromFile("resources/igloo2.png");
    igloo_texture4.loadFromFile("resources/igloo3.png");
    igloo_texture5.loadFromFile("resources/igloo4.png");
    igloo_texture6.loadFromFile("resources/igloo5.png");
    igloo_texture7.loadFromFile("resources/igloo6.png");
    igloo_texture8.loadFromFile("resources/igloo7.png");
    igloo_texture9.loadFromFile("resources/igloo8.png");
    igloo_texture10.loadFromFile("resources/igloo9.png");
    igloo_texture11.loadFromFile("resources/igloo10.png");
    igloo_texture12.loadFromFile("resources/igloo11.png");
    igloo_texture13.loadFromFile("resources/igloo12.png");
    igloo_texture14.loadFromFile("resources/igloo13.png");
    igloo_texture15.loadFromFile("resources/igloo14.png");
}



