#pragma once
#ifndef ENGINE_H
#define ENGINE_H

#include "SfmlLibrary.h"
#include "Menu.h"
#include "Player1.h"
#include "gameConstants.h"


class Engine
{
public:
	Engine();
	void run(); //start game play

private:
	Menu menu;
	Player1 player1;

	bool needToSpawn; //flag if need to spawn players
	

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

	//views for the background
	sf::View singlePlayerBG_View; // single player background
	sf::View LeftViewB; // background of left window
	sf::View RightViewB; //background of right window 

	void MenuInput(); //handle input from main menu (function defined in Input.cpp)
	void update(const float _time); //update game entities (in multiplayer or single | defined in Update.cpp)
	void draw(); //draw game characters

	void LoadTextures();
	void SetSprites();

	Texture menu_texture;
	Sprite menu_sprite;

	Texture background_texture;
	Sprite background_sprite;

	Texture line_texture;
	Sprite line_sprite;
};

#endif // !ENGINE_H

