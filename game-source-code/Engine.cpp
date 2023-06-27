#include "Engine.h"

Engine::Engine():
	splitScreen{false},
	inMainMenu{true} // game initially in main menu display
{
	vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	window.create(VideoMode(resolution.x, resolution.y), "FrostBite", sf::Style::Fullscreen);

	//Initialise main menu view
	MainmenuView.reset(FloatRect(0, 0, resolution.x, resolution.y));

	//Initialise fullsreen viw for single player mode
	singlePlayerView.setSize(resolution);

	//Initialize split screen views
	leftView.setViewport(FloatRect(0, 0, 0.5f, 1.0f));
	rightView.setViewport(FloatRect(0.5f, 0, 0.5f, 1.0f));
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
		update(dtAsSeconds);
		draw();
	}
}