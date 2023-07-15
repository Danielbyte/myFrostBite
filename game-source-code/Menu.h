#pragma once
#ifndef MENU_H
#define MENU_H

#include "SfmlLibrary.h"

class Menu
{
public:
	Menu();
	void setCursorLevel(const int _level); //setting the level of the cursor
	int getCursorLevel() const;
	void update(); //update the level of cursor
	Sprite getCursor() const;
	void setCursorPosition(const vector2f _position);

private:
	int cursorLevel;

	//Different positions cursor can occupy
	vector2f L1, L2, L3, L4;

	Texture cursor_texture;
	Sprite cursor_sprite;
};
#endif // !MENU_H
