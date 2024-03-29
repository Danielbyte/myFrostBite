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
	quit{false},
	P1Scored{false},
	P2Scored{false},
	restartP1{true},
	restartP2{true},
	counter1{0},
	counter2{0},
	iglooCounter1{0},
	iglooCounter2{0},
	tempDigitUpdated1{false},
	tempDigitUpdated2{false}
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

	mLivesHUDPos.x = 553.0f;
	mLivesHUDPos.y = 21.0f;

	//Game end text
	gameEndFont.loadFromFile("resources/SnowtopCaps.otf");
	gameOverTxt.setFont(gameEndFont);
	gameOverTxt.setCharacterSize(60);
	exitTxt.setFont(gameEndFont);
	exitTxt.setFillColor(Color::Black);
	exitTxt.setPosition(250.5f, 412.0f);
	exitTxt.setString("Menu(Esc)");

	gameWinTxt.setFont(gameEndFont);
	gameWinTxt.setCharacterSize(60);
	gameWinTxt.setPosition(300.0f, 10.0f);
	gameWinTxt.setString("VICTORY");

	exitTxt.setCharacterSize(60);
	gameOverTxt.setFillColor(Color::Black);
	gameOverTxt.setPosition(253.0f, 10.0f);
	gameOverTxt.setString("GAME OVER");

	scoreBoardTxt.setFont(gameEndFont);
	scoreBoardTxt.setCharacterSize(24);
	scoreBoardTxt.setFillColor(Color::White);
	scoreBoardTxt.setPosition(320.5f, 180.0f);
	scoreBoardTxt.setString("SCORE BOARD");

	player1ScoreTxt.setFont(gameEndFont);
	player1ScoreTxt.setCharacterSize(24);
	player1ScoreTxt.setFillColor(Color::White);
	player1ScoreTxt.setPosition(310.0f, 245.0f);

	player2ScoreTxt.setFont(gameEndFont);
	player2ScoreTxt.setCharacterSize(24);
	player2ScoreTxt.setFillColor(Color::White);
	player2ScoreTxt.setPosition(310.0f, 245.0f);

	highScoreTxt.setFont(gameEndFont);
	highScoreTxt.setCharacterSize(24);
	highScoreTxt.setFillColor(Color::White);
	highScoreTxt.setPosition(310.0f, 310.0f);
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

void Engine::computeScoreBoard(shared_ptr<Player>& _player,Text& _highScore, Text& _playerScore)
{
	auto score = std::to_string(_player->retrievePlayerScore());
	_playerScore.setString("YOUR SCORE: " + score);
	manage_scores.updateHighScore(_player->retrievePlayerScore());
	auto high_score = manage_scores.getHighScore();
	_highScore.setString("HIGH SCORE: " + std::to_string(high_score));
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
	//Re-initialize game/instantiate new objects
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
	P1Scored = false;
	P2Scored = false;
	bool restartP1 = true;//to mark if scoring watch for P1 can be restarted
	bool restartP2 = true;//to mark if scoring watch for P2 can be restarted
	counter1 = 0;
	counter2 = 0;
	iglooCounter1 = 0;
	iglooCounter2 = 0;
	tempDigitUpdated1 = false;
	tempDigitUpdated2 = false;

	bear2.reset(new Bear());
	bear.reset(new Bear());
	igloo_house.reset(new Igloo());
	igloo_house2.reset(new Igloo());
	overworld.resetOverWorld();
	overworld2.resetOverWorld();
	player1.reset(new Player1());
	player2.reset(new Player2());
	control_birds.reset(new BirdController());
	control_clamps.reset(new ClampController());
	control_crabs.reset(new CrabController());
	control_fish.reset(new FishController());
	control_ice.reset(new IceBlockController());
	manage_scores.resetHUDPos();
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