#ifndef ICEBLOCKCONTROLLER_H
#define ICEBLOCKCONTROLLER_H
#include "IceBlocks.h"

class IceBlockController {
public:
    IceBlockController();
    void update_iceblocks(vector<shared_ptr<IceBlocks>>&, vector<shared_ptr<Sprite>>&, bool&);
    Texture blue_ice_texture;
    Texture white_ice_texture;
    void update_ice_texture(vector<shared_ptr<Sprite>>&, vector<shared_ptr<IceBlocks>>&);

private:
    void load_textures();
} ;
#endif // ICEBLOCKCONTROLLER_H
