#pragma once
#ifndef ANIMAL_H
#define ANIMAL_H

#include "SfmlLibrary.h"

class Animal
{
public:
	Animal();
	vector2f getPosition() const;
	void setPosition(const vector2f _position);
	std::tuple<bool, bool> getSide() const;

protected:
	bool spawned_left;
	bool spawned_right;
	vector2f position;

private:
	
};

#endif // !ANIMAL_H

