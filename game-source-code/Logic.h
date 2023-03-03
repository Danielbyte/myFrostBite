#ifndef LOGIC_H
#define LOGIC_H
#include <tuple>
#include "SfmlLibrary.h"
#include "bailey.h"
#include "IceBlockController.h"
#include "Collision.h"
#include "igloo.h"
#include "BaileyController.h"
#include "bear.h"
#include "enemy.h"
#include "crab.h"
#include "clamp.h"
#include "bird.h"
#include "fish.h"
#include "crabController.h"
#include "clampController.h"
#include "fishController.h"
#include "birdController.h"

class Logic {
public:
    Logic();
   ~Logic();

   //Bailey logic
   Bailey bailey_object;
   void update_bailey_jumps(Sprite&, bool&, const float&,bool&,bool&);
   void update_bailey(Sprite&);

   //Ice block logic
   //void create_ice_blocks(vector<shared_ptr<Sprite>>&);
   void update_ice(vector<shared_ptr<Sprite>>&, const float&);
   vector <shared_ptr<IceBlocks>>ice_block_objects;

   std::tuple<vector2f,vector2f,vector2f,vector2f> create_ice_block_objects();
   bool Is_bailey_moving() const;

   void bailey_and_ice_collision(shared_ptr<Sprite>&,Sprite&,const float&);

   bool mark_if_igloo_is_complete();

   void reverse_ice_direction(shared_ptr<Sprite>&);

   shared_ptr<Igloo>igloo_object = std::make_shared<Igloo>(Igloo());
   vector2f get_igloo_position();

   int get_number_of_igloo_blocks();

   Texture bailey_texture;

   //Bear
   Bear bear_object;
   void update_bear(Sprite&, const float&);
   void bear_track_bailey(Sprite&);
   void frostbite_bear_collisions();

   //Other Enemies
   Enemy enemy;
   void update_enemies(vector<shared_ptr<Sprite>>&, vector<shared_ptr<Sprite>>&,
       vector<shared_ptr<Sprite>>&, vector<shared_ptr<Sprite>>&, const float&);

   void animate_bailey_death(const float&,Sprite&);

   void check_frostbite_on_ice_patch(shared_ptr<IceBlocks>&);
   void drowning_bailey_animation(const float&,Sprite&);

   //frostbite bailey with sea animals
   void updateBaileyAndSeaAnimalCollisioons(vector<shared_ptr<Sprite>>&, vector<shared_ptr<Sprite>>&,
       vector<shared_ptr<Sprite>>&, vector<shared_ptr<Sprite>>&);
   void bailey_fish_collision(vector<shared_ptr<Sprite>>&);
   void bailey_bird_collision(vector<shared_ptr<Sprite>>&);
   void bailey_clamp_collision(vector<shared_ptr<Sprite>>&);
   void bailey_crab_collision(vector<shared_ptr<Sprite>>&);

   void region_collisions(const Animal&, vector<shared_ptr<Sprite>>&, vector<shared_ptr<Sprite>>&,
       vector<shared_ptr<Sprite>>&, vector<shared_ptr<Sprite>>&);

private:
    int ice_block_index;
    IceBlockController ice_block_controller;
    vector2f pos;

    bool is_bailey_moving;
    vector2f prev_pos;

    Collision collision;

    void set_all_ice_batches_to_blue();
    bool is_igloo_complete;
    vector2f position;
    float y_;


    BaileyController control_bailey;

    bool ice_collision_batch1;
    bool ice_collision_batch2;

    //vectors of enemies
    vector <shared_ptr<Crab>> crabs;
    vector <shared_ptr<Clamp>> clamps;
    vector <shared_ptr<Bird>> birds;
    vector <shared_ptr<Fish>> fish;

    //control sea entities
    CrabController control_crab;
    ClampController control_clamp;
    FishController control_fish;
    BirdController control_bird;

    bool plungedInWater; //monitors if bailey has plunged on water

    int NOBI; //Number Of Blue Ice
    void set_all_ice_to_white();
    void update_other_ice(const IceRegion&, const IceColor&);
    void updateOtherIceToChangeDirection(const IceRegion&, const IceDirection&);

    void setBaileyToMoveWithIce(Sprite&, const IceDirection&, const float&);
};
#endif // LOGIC_H
