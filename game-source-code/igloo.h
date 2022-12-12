#ifndef IGLOO_H
#define IGLOO_H
#include "gameConstants.h"
#include "SfmlLibrary.h"

class Igloo
{
public:
    Igloo();
    Texture igloo_texture;

    float get_x_position() const;
    float get_y_position() const;
    void build_igloo(vector<shared_ptr<Sprite>>&);
    void add_igloo_blocks();
    int get_number_of_igloo_blocks() const;
    void subract_igloo_block();
    void update_igloo(shared_ptr<Sprite>&, vector<shared_ptr<Sprite>>&);

private:
    float x_position;
    float y_position;
    int igloo_blocks;

};

#endif // IGLOO_H
