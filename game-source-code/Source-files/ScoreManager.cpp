#include "../Header-files/ScoreManager.h"

ScoreManager::ScoreManager():
	high_score{0},
	iceBlockPts{30},
	winning{0},
	enteringIgloo{480},
	fish{30}
{
	scoreHUDPos.x = 400.0f;
	scoreHUDPos.y = 3.0f;
	score_font.loadFromFile("resources/ARCADE_N.ttf");
	score.setFont(score_font);
	score.setCharacterSize(20);
	score.setPosition(scoreHUDPos);
	mScoreHUDPos.x = 400.7365f;
	mScoreHUDPos.y = 0.0f;
}

Text ScoreManager::getScore(shared_ptr<Player>& _player)
{
	string _score = std::to_string(_player->retrievePlayerScore());
	score.setString(_score);
	return score;

}

void ScoreManager::mSetScoreHUDPos()
{
	score.setPosition(mScoreHUDPos);
}

void ScoreManager::resetHUDPos()
{
	score.setPosition(scoreHUDPos);
}

float ScoreManager::getHighScore()
{

}

void ScoreManager::updateHighScore()
{

}

void ScoreManager::updatePlayerScore(shared_ptr<Player>& _player, const std::string _scoreType, 
	const int temperature)
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
	if (_scoreType == "won")
	{
		_player->updatePlayerScore(30 * temperature);
	}
}

void ScoreManager::computeWinningScore(OverWorld& _overworld, Stopwatch& _watch, shared_ptr<Player>& _player,
	bool& computed, int& counter)
{
	auto temp = _overworld.getTemperatureInt();

	if (temp > 0)
	{
		auto time = _watch.elapsed_time();
		if (time >= 0.05f)
		{
			updatePlayerScore(_player, "won", temp);
			_overworld.decrementTemperature();
			_watch.restart_timer();
		}
	}

	temp = _overworld.getTemperatureInt();
	if (temp == 0 && counter == 0) { _watch.restart_timer(); ++counter;}

	if (!computed)
	{
		if (_watch.elapsed_time() >= 0.5f) // create a 0.5 seconds delay
		{
			computed = true;
		}
	}
}