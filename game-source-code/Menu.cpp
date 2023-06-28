#include "Menu.h"

Menu::Menu():
	cursorLevel{1}
{
	//initialize cursor levels
	L1.x = 206.0f;;
	L1.y = 222.0f;

	L2.x = 215.0f;
	L2.y = 279.0f;

	L3.x = 273.0f;
	L3.y = 336.0f;

	L4.x = 294.0f;
	L4.y = 393.0f;

	cursor_texture.loadFromFile("resources/cursor.png");
	cursor_sprite.setTexture(cursor_texture);
	cursor_sprite.setPosition(L1); //Cursor is initially at single player mode
	vector2f cursor_size;
	cursor_size.x = 32.0f;
	cursor_size.y = 32.0f;
	cursor_sprite.setOrigin(cursor_size / 2.0f);
}

void Menu::setCursorLevel(const int level)
{
	cursorLevel = level;
}

int Menu::getCursorLevel() const
{
	return cursorLevel;
}

void Menu::update()
{
	switch (cursorLevel)
	{
	case 1:
		cursor_sprite.setPosition(L1);
		break;

	case 2:
		cursor_sprite.setPosition(L2);
		break;

	case 3:
		cursor_sprite.setPosition(L3);
		break;

	case 4:
		cursor_sprite.setPosition(L4);
		break;

	default:
		break;
	}
}

Sprite Menu::getCursor() const
{
	return cursor_sprite;
}
