#include "../Header-files/ScoreManager.h"

ScoreManager::ScoreManager():
	high_score{0},
	iceBlockPts{30},
	winning{0},
	enteringIgloo{480},
	fish{30}
{
	score_font.loadFromFile("resources/ARCADE_N.ttf");
	score.setFont(score_font);
	score.setCharacterSize(20);
	score.setPosition(400.0f, 3.0f);
}

Text ScoreManager::getScore(shared_ptr<Player>& _player)
{
	string _score = std::to_string(_player->retrievePlayerScore());
	score.setString(_score);
	return score;

}

float ScoreManager::getHighScore()
{

}

void ScoreManager::updateHighScore()
{

}

void ScoreManager::updatePlayerScore(shared_ptr<Player>& _player, const std::string _scoreType)
{
	if (_scoreType == "fish")
	{
		_player->updatePlayerScore(fish);
		return;
	}
	if (_scoreType == "ice")
	{
		_player->updatePlayerScore(iceBlockPts);
	}
	if (_scoreType == "igloo")
	{
		_player->updatePlayerScore(enteringIgloo);
	}
}