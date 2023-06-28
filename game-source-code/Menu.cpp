#include "Menu.h"

Menu::Menu():
	cursorLevel{1}
{}

void Menu::setCursorLevel(const int level)
{
	cursorLevel = level;
}

int Menu::getCursorLevel() const
{
	return cursorLevel;
}
