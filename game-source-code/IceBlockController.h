#ifndef ICEBLOCKCONTROLLER_H
#define ICEBLOCKCONTROLLER_H
#include "IceBlocks.h"

class IceBlockController {
public:
    IceBlockController();
    void update_iceblocks(vector<shared_ptr<IceBlocks>>&,const float deltaTime);
    Texture blue_ice_texture;
    Texture white_ice_texture;
    void update_ice_texture(vector<shared_ptr<IceBlocks>>&);

    //Function to create ice in genera
    void create_new_ice(const IceDirection&, const IceRegion&, const IceColor&);

    //create ice in specific region
    void create_ice_R1(const IceDirection&, const IceRegion&, const IceColor&);
    void create_ice_R2(const IceDirection&, const IceRegion&,const IceColor&);
    void create_ice_R3(const IceDirection&, const IceRegion&,const IceColor&);
    void create_ice_R4(const IceDirection&, const IceRegion&,const IceColor&);

    //Check if you already have ice present in region
    void check_regions(const vector<shared_ptr<IceBlocks>>&);
    void set_position(const IceDirection&, vector2f&, const float&);

private:
    void load_textures();
    float OOBBL; //OOBL->Out Of Bounds Boundary Left
    float OOBBR; //OOBR->Out Of Bounds Boundary Right
    queue<shared_ptr<IceBlocks>>new_ice;

    //RXP -> Region X Full
    bool R1F, R2F, R3F, R4F; //mark region already has two ice
} ;
#endif // ICEBLOCKCONTROLLER_H
