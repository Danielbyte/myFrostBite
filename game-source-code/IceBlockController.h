#ifndef ICEBLOCKCONTROLLER_H
#define ICEBLOCKCONTROLLER_H
#include "IceBlocks.h"
#include <queue>

class IceBlockController {
public:
    IceBlockController();
    void update_iceblocks(vector<shared_ptr<IceBlocks>>&, vector<shared_ptr<Sprite>>&,const float&);
    Texture blue_ice_texture;
    Texture white_ice_texture;
    void update_ice_texture(vector<shared_ptr<Sprite>>&, vector<shared_ptr<IceBlocks>>&);

    //Function to create ice in genera
    void create_new_ice(const IceDirection&, const IceRegion&, const IceColor&);

    //create ice in specific region
    void create_ice_R1(const IceDirection&, const IceRegion&, const IceColor&);
    void create_ice_R2(const IceDirection&, const IceRegion&, const IceColor&);
    void create_ice_R3(const IceDirection&, const IceRegion&, const IceColor&);
    void create_ice_R4(const IceDirection&, const IceRegion&, const IceColor&);

private:
    void load_textures();
    float OOBBL; //OOBL->Out Of Bounds Boundary Left
    float OOBBR; //OOBR->Out Of Bounds Boundary Right
    std::queue<shared_ptr<IceBlocks>>new_ice_objects;
    std::queue<shared_ptr<Sprite>>new_ice_sprites;
} ;
#endif // ICEBLOCKCONTROLLER_H
