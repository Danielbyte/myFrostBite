#ifndef BAILEYCONTROLLER_H
#define BAILEYCONTROLLER_H

#include "bailey.h"

class BaileyController
{
public:
	BaileyController();
	//~BaileyController();
	Texture bailey_texture;
	int get_frame() const;
	void update_bailey(vector2f&,bool&, const float&, const float&);
	void animate_bailey(Bailey&, Sprite&);

private:
	void increment_frame();
	void reset_frame();
	int frame_counter;
};
#endif

