/*#ifndef LOGIC_H
#define LOGIC_H
#include <tuple>
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

   //Igloo logic
   shared_ptr<Igloo>igloo_object = std::make_shared<Igloo>(Igloo());
   int get_number_of_igloo_blocks();
   bool mark_if_igloo_is_complete();
   
   //Ice logic
   std::tuple<vector2f, vector2f, vector2f, vector2f> create_ice_block_objects();
   void update_ice(vector<shared_ptr<Sprite>>&, const float&);
   vector <shared_ptr<IceBlocks>>ice_block_objects;
   void reverse_ice_direction(shared_ptr<Sprite>&);
   
   //Frostbite bailey logic
   Bailey bailey_object;
   bool bailey_and_ice_collision(shared_ptr<Sprite>&, Sprite&, const float&);
   void update_bailey_jumps(Sprite&, bool&, const float&, bool&, bool&);
   void check_frostbite_on_ice_patch(shared_ptr<IceBlocks>&);
   void update_bailey(Sprite&);

   //Bear logic
   Bear bear_object;
   void update_bear(Sprite&, const float&);
   void bear_track_bailey(Sprite&);
   void frostbite_bear_collisions();

   //Sea animals logic
   Enemy enemy;
   void update_enemies(vector<shared_ptr<Sprite>>&, vector<shared_ptr<Sprite>>&,
       vector<shared_ptr<Sprite>>&, vector<shared_ptr<Sprite>>&, const float&);

   //frostbite baileyinteraction with sea animals
   void updateBaileyAndSeaAnimalCollisions(vector<shared_ptr<Sprite>>&, vector<shared_ptr<Sprite>>&,
       vector<shared_ptr<Sprite>>&, vector<shared_ptr<Sprite>>&);
   void region_collisions(const Animal&, vector<shared_ptr<Sprite>>&, vector<shared_ptr<Sprite>>&,
       vector<shared_ptr<Sprite>>&, vector<shared_ptr<Sprite>>&);
   void bailey_fish_collision(vector<shared_ptr<Sprite>>&);
   void bailey_bird_collision(vector<shared_ptr<Sprite>>&);
   void bailey_clamp_collision(vector<shared_ptr<Sprite>>&);
   void bailey_crab_collision(vector<shared_ptr<Sprite>>&);
   bool getIfCollidedWithSeaAnimal() const;

   //Animations
   void baileyCollisionWithSeaCreatureAnimation(const float&, Sprite&);
   void drowning_bailey_animation(const float&, Sprite&);
   void animate_bailey_death(const float&, Sprite&);
   void freezing_bailey_animation(const float&, Sprite&);
   void go_inside_igloo(const float&, Sprite&);

private:
    //Ice block private functions and variables
    void updateOtherIceToChangeDirection(const IceRegion&, const IceDirection&);
    void update_other_ice(const IceRegion&, const IceColor&);
    IceBlockController ice_block_controller;
    void set_all_ice_batches_to_blue();
    void set_all_ice_to_white();
    bool is_igloo_complete;
    int NOBI; //Number Of Blue Ice

    //Frostbite bear private functions and variables
    void setBaileyToMoveWithIce(Sprite&, const IceDirection&, const float&);
    BaileyController control_bailey;
    bool is_bailey_moving;
    bool plungedInWater; //monitors if bailey has plunged on water
    vector2f prev_pos;
    float y_;

    //vectors of sea enemies
    vector <shared_ptr<Crab>> crabs;
    vector <shared_ptr<Clamp>> clamps;
    vector <shared_ptr<Bird>> birds;
    vector <shared_ptr<Fish>> fish;

    //control sea entities
    CrabController control_crab;
    ClampController control_clamp;
    FishController control_fish;
    BirdController control_bird;

    //Collisions
    bool BaileyCollidedWithSeaAnimal;
    Collision collision;
};
#endif // LOGIC_H
*/