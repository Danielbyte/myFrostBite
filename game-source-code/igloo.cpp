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
    /*if (igloo_blocks == 0)
    {
        auto igloo_iterator = std::make_shared<Sprite>(Sprite());
        igloo_texture.loadFromFile("resources/igloo0.png");
        igloo_iterator -> setOrigin(igloo_width/2.0f, igloo_height/2.0f);
        igloo_iterator -> setTexture(igloo_texture);
        igloo_iterator -> setPosition(x_position,y_position);
        igloo_sprites.push_back(igloo_iterator);
        return;
    }*/

    if (igloo_blocks == 1)
    {
        auto igloo_iterator = std::make_shared<Sprite>(Sprite());
        igloo_texture.loadFromFile("resources/igloo1.png");
        igloo_iterator -> setOrigin(igloo_width/2.0f, igloo_height/2.0f);
        igloo_iterator -> setTexture(igloo_texture);
        igloo_iterator -> setPosition(x_position,y_position);
        igloo_sprites.push_back(igloo_iterator);
        return;
    }

    else if (igloo_blocks == 2)
    {
        std::cout << "Blocks " << igloo_blocks << std::endl;
        auto igloo_iterator = std::make_shared<Sprite>(Sprite());
        igloo_texture.loadFromFile("resources/igloo2.png");
        igloo_iterator -> setOrigin(igloo_width/2.0f, igloo_height/2.0f);
        igloo_iterator -> setTexture(igloo_texture);
        igloo_iterator -> setPosition(x_position,y_position);
        igloo_sprites.push_back(igloo_iterator);
        return;
    }

    else if (igloo_blocks == 3)
    {
        auto igloo_iterator = std::make_shared<Sprite>(Sprite());
        igloo_texture.loadFromFile("resources/igloo3.png");
        igloo_iterator -> setOrigin(igloo_width/2.0f, igloo_height/2.0f);
        igloo_iterator -> setTexture(igloo_texture);
        igloo_iterator -> setPosition(x_position,y_position);
        igloo_sprites.push_back(igloo_iterator);
        return;
    }

    else if (igloo_blocks == 4)
    {
        auto igloo_iterator = std::make_shared<Sprite>(Sprite());
        igloo_texture.loadFromFile("resources/igloo4.png");
        igloo_iterator -> setOrigin(igloo_width/2.0f, igloo_height/2.0f);
        igloo_iterator -> setTexture(igloo_texture);
        igloo_iterator -> setPosition(x_position,y_position);
        igloo_sprites.push_back(igloo_iterator);
        return;
    }

    else if (igloo_blocks == 5)
    {
        auto igloo_iterator = std::make_shared<Sprite>(Sprite());
        igloo_texture.loadFromFile("resources/igloo5.png");
        igloo_iterator -> setOrigin(igloo_width/2.0f, igloo_height/2.0f);
        igloo_iterator -> setTexture(igloo_texture);
        igloo_iterator -> setPosition(x_position,y_position);
        igloo_sprites.push_back(igloo_iterator);
        return;
    }

    else if (igloo_blocks == 6)
    {
        auto igloo_iterator = std::make_shared<Sprite>(Sprite());
        igloo_texture.loadFromFile("resources/igloo6.png");
        igloo_iterator -> setOrigin(igloo_width/2.0f, igloo_height/2.0f);
        igloo_iterator -> setTexture(igloo_texture);
        igloo_iterator -> setPosition(x_position,y_position);
        igloo_sprites.push_back(igloo_iterator);
        return;
    }

    else if (igloo_blocks == 7)
    {
        auto igloo_iterator = std::make_shared<Sprite>(Sprite());
        igloo_texture.loadFromFile("resources/igloo7.png");
        igloo_iterator -> setOrigin(igloo_width/2.0f, igloo_height/2.0f);
        igloo_iterator -> setTexture(igloo_texture);
        igloo_iterator -> setPosition(x_position,y_position);
        igloo_sprites.push_back(igloo_iterator);
        return;
    }

    else if (igloo_blocks == 8)
    {
        auto igloo_iterator = std::make_shared<Sprite>(Sprite());
        igloo_texture.loadFromFile("resources/igloo8.png");
        igloo_iterator -> setOrigin(igloo_width/2.0f, igloo_height/2.0f);
        igloo_iterator -> setTexture(igloo_texture);
        igloo_iterator -> setPosition(x_position,y_position);
        igloo_sprites.push_back(igloo_iterator);
        return;
    }

    else if (igloo_blocks == 9)
    {
        auto igloo_iterator = std::make_shared<Sprite>(Sprite());
        igloo_texture.loadFromFile("resources/igloo9.png");
        igloo_iterator -> setOrigin(igloo_width/2.0f, igloo_height/2.0f);
        igloo_iterator -> setTexture(igloo_texture);
        igloo_iterator -> setPosition(x_position,y_position);
        igloo_sprites.push_back(igloo_iterator);
        return;
    }

    else if (igloo_blocks == 10)
    {
        auto igloo_iterator = std::make_shared<Sprite>(Sprite());
        igloo_texture.loadFromFile("resources/igloo10.png");
        igloo_iterator -> setOrigin(igloo_width/2.0f, igloo_height/2.0f);
        igloo_iterator -> setTexture(igloo_texture);
        igloo_iterator -> setPosition(x_position,y_position);
        igloo_sprites.push_back(igloo_iterator);
        return;
    }

    else if (igloo_blocks == 11)
    {
        auto igloo_iterator = std::make_shared<Sprite>(Sprite());
        igloo_texture.loadFromFile("resources/igloo11.png");
        igloo_iterator -> setOrigin(igloo_width/2.0f, igloo_height/2.0f);
        igloo_iterator -> setTexture(igloo_texture);
        igloo_iterator -> setPosition(x_position,y_position);
        igloo_sprites.push_back(igloo_iterator);
        return;
    }

    else if (igloo_blocks == 12)
    {
        auto igloo_iterator = std::make_shared<Sprite>(Sprite());
        igloo_texture.loadFromFile("resources/igloo12.png");
        igloo_iterator -> setOrigin(igloo_width/2.0f, igloo_height/2.0f);
        igloo_iterator -> setTexture(igloo_texture);
        igloo_iterator -> setPosition(x_position,y_position);
        igloo_sprites.push_back(igloo_iterator);
        return;
    }

    else if (igloo_blocks == 13)
    {
        auto igloo_iterator = std::make_shared<Sprite>(Sprite());
        igloo_texture.loadFromFile("resources/igloo13.png");
        igloo_iterator -> setOrigin(igloo_width/2.0f, igloo_height/2.0f);
        igloo_iterator -> setTexture(igloo_texture);
        igloo_iterator -> setPosition(x_position,y_position);
        igloo_sprites.push_back(igloo_iterator);
        return;
    }

    else if (igloo_blocks == 14)
    {
        auto igloo_iterator = std::make_shared<Sprite>(Sprite());
        igloo_texture.loadFromFile("resources/igloo14.png");
        igloo_iterator -> setOrigin(igloo_width/2.0f, igloo_height/2.0f);
        igloo_iterator -> setTexture(igloo_texture);
        igloo_iterator -> setPosition(x_position,y_position);
        igloo_sprites.push_back(igloo_iterator);
        return;
    }
}

void Igloo::add_igloo_blocks()
{
    ++igloo_blocks;

    //If igloo is complete, keep bricks capped at 14.
    if (igloo_blocks >= 14)
    {
        igloo_blocks = 14;
    }
}

void Igloo::subract_igloo_block()
{
    if (igloo_blocks > 0)
    {
        igloo_blocks -= 1;
    }
}

int Igloo::get_number_of_igloo_blocks() const
{
    return igloo_blocks;
}



