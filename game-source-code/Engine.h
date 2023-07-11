#pragma once
#ifndef ENGINE_H
#define ENGINE_H

#include "SfmlLibrary.h"
#include "Menu.h"
#include "Player1.h"
#include "Player2.h"
#include "gameConstants.h"
#include "OverWorld.h"
#include "stopwatch.h"
#include "clampController.h"
#include "birdController.h"
#include "crabController.h"
#include "fishController.h"
#include "IceBlockController.h"
#include "AnimatePlayer.h"
#include "CollisionsManager.h"
#include "igloo.h"
#include "bear.h"

class Engine
{
public:
	Engine();
	void run(); //start game play

private:
	Menu menu;
	Player1 player1;
	Player2 player2;
	OverWorld overworld;
	Stopwatch overworld_watch;
	BirdController control_birds;
	CrabController control_crabs;
	ClampController control_clamps;
	FishController control_fish;
	IceBlockController control_ice;
	AnimatePlayer animate;
	CollisionsManager manage_collisions;

	bool needToSpawn; //flag if need to spawn players
	

	//initialize single and multiplayer objects
	
	bool splitScreen; //for multiplayer mode
	bool inMainMenu;
	bool isPlaying;
	sf::View MainmenuView; //view for main game menu

	shared_ptr<sf::RenderWindow> window = shared_ptr<RenderWindow>(new sf::RenderWindow(VideoMode
	(windowWidth, windowHeight), "FrostBite", sf::Style::Default)); //normal game window

	//main views for game play
	sf::View singlePlayerView; // view for single player mode
	sf::View leftView; // view for left side in multiplayer
	sf::View rightView; //view for right side in multiplayer mode;

	//views for the background
	sf::View singlePlayerBG_View; // single player background
	sf::View LeftViewB; // background of left window
	sf::View RightViewB; //background of right window 
	void handleInput(); //handle input from player/s (function defined in Input.cpp)
	void update(const float _time); //update game entities (in multiplayer or single | defined in Update.cpp)
	void update_over_world(const float deltaTime);
	void display_manager(); //Front End (Manages the front end logic)
	void draw(vector<shared_ptr<Crab>>&, vector<shared_ptr<Clamp>>&, vector<shared_ptr<Bird>>&, 
		vector<shared_ptr<Fish>>&, shared_ptr<Igloo>&, shared_ptr<Bear>&, vector<shared_ptr<IceBlocks>>&,
		Player& player, OverWorld& _overworld);

	void LoadTextures();
	void SetSprites();

	Texture menu_texture;
	Sprite menu_sprite;

	Texture background_texture;
	Sprite background_sprite;

	Texture game_over_texture;
	Sprite game_over_sprite;

	Texture line_texture;
	Sprite line_sprite;

	//vectors of animals
	vector <shared_ptr<Crab>> crabs;
	vector <shared_ptr<Clamp>> clamps;
	vector <shared_ptr<Bird>> birds;
	vector <shared_ptr<Fish>> fish;
	shared_ptr<Bear>bear = std::make_shared<Bear>(Bear());

	//Iceblocks
	vector <shared_ptr<IceBlocks>> iceblocks;
	bool canCreateIce;

	//Igloo object
	shared_ptr<Igloo>igloo_house = std::make_shared<Igloo>(Igloo());

	//template function to draw all animals in the game over world
	template<typename _Animal>
	void draw_overWorld(const vector<shared_ptr<_Animal>>& _animals)
	{
		if (!_animals.empty())
		{
			for (auto& _animal : _animals)
			{
				window->draw(_animal->getSprite());
			}
		}
	}
};

#endif // !ENGINE_H

