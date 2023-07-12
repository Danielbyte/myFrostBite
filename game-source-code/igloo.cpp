#include "igloo.h"

Igloo::Igloo():
    igloo_blocks{0},
    complete{false}
{
    position.x = 612.0f;
    position.y = 130.0f;
    mPosition.x = 473.0f;
    mPosition.y = position.y;

    load_textures();
    iglooSprite.setOrigin(igloo_width / 2.0f, igloo_height / 2.0f);
    iglooSprite.setPosition(position);
}

void Igloo::mSetPosition()
{
    position = mPosition;
    iglooSprite.setPosition(position);
}

vector2f Igloo::getPosition() const
{
    return position;
}

vector2f Igloo::getDoorPosition() const
{
    return position;
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

Sprite Igloo::getSprite() const
{
    return iglooSprite;
}

void Igloo::updateSprite(Texture& newTexture)
{
    iglooSprite.setTexture(newTexture);
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

void Igloo::update_igloo()
{
    if (igloo_blocks == 0)
    {
        iglooSprite.setTexture(igloo_texture1);
        return;
    }

    else if (igloo_blocks == 1)
    {
        iglooSprite.setTexture(igloo_texture2);
        return;
    }

    else if (igloo_blocks == 2)
    {

        iglooSprite.setTexture(igloo_texture3);
        return;
    }

    else if (igloo_blocks == 3)
    {
        iglooSprite.setTexture(igloo_texture4);
        return;
    }

    else if (igloo_blocks == 4)
    {
        iglooSprite.setTexture(igloo_texture5);
        return;
    }

    else if (igloo_blocks == 5)
    {
        iglooSprite.setTexture(igloo_texture6);
        return;
    }

    else if (igloo_blocks == 6)
    {
        iglooSprite.setTexture(igloo_texture7);
        return;
    }

    else if (igloo_blocks == 7)
    {
        iglooSprite.setTexture(igloo_texture8);
        return;
    }

    else if (igloo_blocks == 8)
    {
        iglooSprite.setTexture(igloo_texture9);
        return;
    }

    else if (igloo_blocks == 9)
    {
        iglooSprite.setTexture(igloo_texture10);
        return;
    }

    else if (igloo_blocks == 10)
    {

        iglooSprite.setTexture(igloo_texture11);
        return;
    }

    else if (igloo_blocks == 11)
    {
        iglooSprite.setTexture(igloo_texture12);
        return;
    }

    else if (igloo_blocks == 12)
    {
        iglooSprite.setTexture(igloo_texture13);
        return;
    }

    else if (igloo_blocks == 13)
    {
        iglooSprite.setTexture(igloo_texture14);
        return;
    }

    else if (igloo_blocks == 14)
    {
        iglooSprite.setTexture(igloo_texture15);
        return;
    }
}

bool Igloo::isComplete()
{
    if (igloo_blocks == 14)
    {
        complete = true;
    }
    else
    {
        complete = false;
    }
    
    return complete;
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



