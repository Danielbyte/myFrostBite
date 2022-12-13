#ifndef LOGIC_H
#define LOGIC_H
#include "SfmlLibrary.h"
#include "bailey.h"
#include "IceBlockController.h"
#include "Collision.h"
#include "igloo.h"


class Logic {
public:
    Logic();
   ~Logic();

   //Bailey logic
   Bailey bailey_object;
   void update_bailey(Sprite&);

   //Ice block logic
   //void create_ice_blocks(vector<shared_ptr<Sprite>>&);
   void update_ice(vector<shared_ptr<Sprite>>&, bool&, int);
   vector <shared_ptr<IceBlocks>>ice_block_objects1;
   vector <shared_ptr<IceBlocks>>ice_block_objects2;
   void create_ice_block_objects(vector<shared_ptr<Sprite>>&, int);
   bool Is_bailey_moving() const;

   void bailey_and_ice_collision(vector<shared_ptr<Sprite>>&);
   void bailey_and_water_collision1(bool&);
   void bailey_and_water_collision2(bool&);

   void update_igloo(vector<shared_ptr<Sprite>>&);
   bool mark_if_igloo_is_complete();

   void reverse_ice_direction(vector<shared_ptr<Sprite>>&);

   vector<shared_ptr<Igloo>>igloo_object;
   void build_igloo();
   vector2f get_igloo_position();

   int get_number_of_igloo_blocks();

private:
    int number_of_igloo_blocks;
    int ice_block_index;
    IceBlockController ice_block_controller;
    vector2f pos;

    bool is_bailey_moving;
    vector2f prev_pos;

    Collision collision;

    void check_for_blues(vector<shared_ptr<IceBlocks>>Iceblocks);
    void check_for_blues_on_other_ice_batch(vector<shared_ptr<IceBlocks>>, vector<shared_ptr<IceBlocks>>);

    void set_all_ice_batches_to_blue(vector<shared_ptr<IceBlocks>>&);
    bool is_igloo_complete;
    vector2f position;
};
#endif // LOGIC_H
