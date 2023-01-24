#ifndef BAILEYCONTROLLER_H
#define BAILEYCONTROLLER_H

#include "bailey.h"

class BaileyController
{
public:
	BaileyController();
	//~BaileyController();
	Texture bailey_texture1;
	Texture bailey_texture2;
	Texture bailey_texture3;
	Texture bailey_texture4;

	int get_frame() const;
	void update_bailey(vector2f&,bool&, const float&, const float&);
	void animate_bailey(Bailey&, Sprite&);
	void load_textures();

private:
	void increment_frame();
	void reset_frame();
	int frame_counter;
};
#endif

