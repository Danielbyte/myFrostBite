#pragma once
#ifndef MENU_H
#define MENU_H

class Menu
{
public:
	Menu();
	void setCursorLevel(const int _level); //setting the level of the cursor
	int getCursorLevel() const;

private:
	int cursorLevel;

};
#endif // !MENU_H
