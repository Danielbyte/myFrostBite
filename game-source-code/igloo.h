#ifndef IGLOO_H
#define IGLOO_H
#include "gameConstants.h"
#include "SfmlLibrary.h"

class Igloo
{
public:
    Igloo();

    //Iglooo textures
    Texture igloo_texture1;
    Texture igloo_texture2;
    Texture igloo_texture3;
    Texture igloo_texture4;
    Texture igloo_texture5;
    Texture igloo_texture6;
    Texture igloo_texture7;
    Texture igloo_texture8;
    Texture igloo_texture9;
    Texture igloo_texture10;
    Texture igloo_texture11;
    Texture igloo_texture12;
    Texture igloo_texture13;
    Texture igloo_texture14;
    Texture igloo_texture15;

    float get_x_position() const;
    float get_y_position() const;
    void add_igloo_blocks();
    int get_number_of_igloo_blocks() const;
    void subract_igloo_block();
    void update_igloo(shared_ptr<Sprite>&);

private:
    float x_position;
    float y_position;
    int igloo_blocks;

    void load_textures();

};

#endif // IGLOO_H
