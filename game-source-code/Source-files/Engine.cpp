#include "../Header-files/Engine.h"

Engine::Engine():
	needToSpawn{true},
	splitScreen{false},
	inMainMenu{true}, // game initially in main menu display
	isPlaying{false}, //game initially in not in game play mode
	inInstructionsMenu{false},
	canCreateIce{false},
	canCreateIce2{false},
	standard_dt{0.016761f},
	reInitialise{false},
	quit{false}
{
	window->setVerticalSyncEnabled(true);
	window->setFramerateLimit(60);

	//Initialise main menu view
	MainmenuView.reset(FloatRect(0, 0, windowWidth, windowHeight));

	//Initialise fullsreen viw for single player mode
	singlePlayerView.reset(FloatRect(0, 0, windowWidth,windowHeight));

	//Initialize split screen views
	leftView.setViewport(FloatRect(0, 0, 0.5f, 1.0f));
	leftView.setSize(windowWidth / 2.0f, windowHeight);
	leftView.setCenter(windowWidth / 2.0f, windowHeight / 2.0f);
	

	LeftViewB.setViewport(FloatRect(0, 0, 0.5f, 1.0f));
	LeftViewB.setSize(windowWidth / 2.0f, windowHeight);
	LeftViewB.setCenter(windowWidth / 2.0f, windowHeight / 2.0f);


	rightView.setViewport(FloatRect(0.5f, 0, 0.5f, 1.0f));
	rightView.setSize(windowWidth / 2.0f, windowHeight);
	rightView.setCenter(windowWidth / 2.0f, windowHeight / 2.0f);

	RightViewB.setViewport(FloatRect(0.5f, 0, 0.5f, 1.0f));
	RightViewB.setSize(windowWidth / 2.0f, windowHeight);
	RightViewB.setCenter(windowWidth / 2.0f, windowHeight / 2.0f);

	LoadTextures();
	SetSprites();

	backPos.x = 660.0f;
	backPos.y = 472.0f;
}

void Engine::run()
{
	Clock clock;
	inMainMenu = true;

	while (window->isOpen())
	{
		auto dt = clock.restart();
		auto dtAsSeconds = dt.asSeconds();
		//Handle input
		handleInput();
		//Update game
		update(dtAsSeconds);
		//Draw game entities
		display_manager(dtAsSeconds);
	}
}

void Engine::LoadTextures()
{
	menu_texture.loadFromFile("resources/menuscreen.png");
	background_texture.loadFromFile("resources/background.png");
	line_texture.loadFromFile("resources/line.png");
	game_over_texture.loadFromFile("resources/gameover.png");
	victory_texture.loadFromFile("resources/victory.png");
	instructions_texture.loadFromFile("resources/instructions.png");
}

void Engine::SetSprites()
{
	menu_sprite.setTexture(menu_texture);
	background_sprite.setTexture(background_texture);
	game_over_sprite.setTexture(game_over_texture);
	victory_sprite.setTexture(victory_texture);
	instructions_sprite.setTexture(instructions_texture);

	line_sprite.setTexture(line_texture);
	line_sprite.setPosition(600.0f, 300.0f);
	line_sprite.setOrigin(0.5f, windowHeight / 2.0f);
}

void Engine::resetGame()
{
	crabs.clear();
	crabs2.clear();
	clamps.clear();
	clamps2.clear();
	birds.clear();
	birds2.clear();
	fish.clear();
	fish2.clear();
	iceblocks.clear();
	iceblocks2.clear();

	needToSpawn = true;
	splitScreen = false;
	inMainMenu = true;
	isPlaying = false; 
	inInstructionsMenu = false;
	canCreateIce = false;
	canCreateIce2 = false;
	standard_dt = 0.016761f;
	reInitialise = false;
	quit = false;

	bear2.reset(new Bear());
	bear.reset(new Bear());
	igloo_house.reset(new Igloo());
	igloo_house2.reset(new Igloo());
	overworld.resetOverWorld();
	overworld2.resetOverWorld();
}

Engine::~Engine()
{
	//some house keeping
	crabs.clear();
	crabs2.clear();
	clamps.clear();
	clamps2.clear();
	birds.clear();
	birds2.clear();
	fish.clear();
	fish2.clear();
	iceblocks.clear();
	iceblocks2.clear();
}