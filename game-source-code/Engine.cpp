#include "Engine.h"

Engine::Engine():
	splitScreen{false},
	inMainMenu{true}, // game initially in main menu display
	isPlaying{false} //game initially in not in game play mode
{

	window.create(VideoMode(windowWidth, windowHeight), "FrostBite", sf::Style::Default);

	//Initialise main menu view
	MainmenuView.reset(FloatRect(0, 0, windowWidth, windowHeight));

	//Initialise fullsreen viw for single player mode
	singlePlayerView.setSize(windowWidth,windowHeight);

	//Initialize split screen views
	leftView.setViewport(FloatRect(0, 0, 0.5f, 1.0f));
	rightView.setViewport(FloatRect(0.5f, 0, 0.5f, 1.0f));

	LoadTextures();
	SetSprites();
}

void Engine::run()
{
	Clock clock;
	inMainMenu = true;

	while (window.isOpen())
	{
		auto dt = clock.restart();
		auto dtAsSeconds = dt.asSeconds();
		MenuInput();
		//update(dtAsSeconds);
		draw();
	}
}

void Engine::LoadTextures()
{
	backgound_texture.loadFromFile("resources/menuscreen.png");
}

void Engine::SetSprites()
{
	background_sprite.setTexture(backgound_texture);
}