#ifndef ICEBLOCKCONTROLLER_H
#define ICEBLOCKCONTROLLER_H
#include "IceBlocks.h"

class IceBlockController {
public:
    IceBlockController();
    void update_iceblocks(vector<shared_ptr<IceBlocks>>&, vector<shared_ptr<Sprite>>&,const float&);
    Texture blue_ice_texture;
    Texture white_ice_texture;
    void update_ice_texture(vector<shared_ptr<Sprite>>&, vector<shared_ptr<IceBlocks>>&);

    //Function to create ice in genera
    void create_new_ice(const IceDirection&, const IceRegion&,vector<shared_ptr<Sprite>>&,
        vector<shared_ptr<IceBlocks>>&);

    //create ice in specific region
    void create_ice_R1(vector<shared_ptr<Sprite>>&, vector<shared_ptr<IceBlocks>>&,
        const IceDirection&, const IceRegion&);
    void create_ice_R2(vector<shared_ptr<Sprite>>&, vector<shared_ptr<IceBlocks>>&,
        const IceDirection&, const IceRegion&);
    void create_ice_R3(vector<shared_ptr<Sprite>>&, vector<shared_ptr<IceBlocks>>&,
        const IceDirection&, const IceRegion&);
    void create_ice_R4(vector<shared_ptr<Sprite>>&, vector<shared_ptr<IceBlocks>>&,
        const IceDirection&, const IceRegion&);

private:
    void load_textures();
    float OOBBL; //OOBL->Out Of Bounds Boundary Left
    float OOBBR; //OOBR->Out Of Bounds Boundary Right
} ;
#endif // ICEBLOCKCONTROLLER_H
