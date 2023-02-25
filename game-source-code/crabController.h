#ifndef CRABCONTROLLER_H
#define CRABCONTROLLER_H

#include "crab.h"

class CrabController : public Crab
{
public:
	CrabController();
	void update_crab(vector<shared_ptr<Sprite>>&, vector<shared_ptr<Crab>>&);

	//Crab textures
	Texture crab1, crab2, crab3, crab4, crab5, crab6;

	void load_textures();
	void animate(shared_ptr<Sprite>&, shared_ptr<Crab>&);

private:
};
#endif
