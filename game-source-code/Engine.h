#pragma once
#ifndef ENGINE_H
#define ENGINE_H

#include "SfmlLibrary.h"
#include "Menu.h"
#include "gameConstants.h"


class Engine
{
public:
	Engine();
	void run(); //start game play

private:
	Menu menu;

	//initialize single and multiplayer objects
	
	bool splitScreen; //for multiplayer mode
	bool inMainMenu;
	bool isPlaying;
	sf::View MainmenuView; //view for main game menu

	RenderWindow window; //normal game window

	//main views for game play
	sf::View singlePlayerView; // view for single player mode
	sf::View leftView; // view for left side in multiplayer
	sf::View rightView; //view for right side in multiplayer mode; 

	void MenuInput(); //handle input from main menu (function defined in Input.cpp)
	void update(float _time); //update game entities (in multiplayer or single | defined in Update.cpp)
	void draw(); //draw game characters

	void LoadTextures();
	void SetSprites();

	Texture backgound_texture;
	Sprite background_sprite;
};

#endif // !ENGINE_H

