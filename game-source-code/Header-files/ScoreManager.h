#pragma once

#include <sstream>
#include <fstream>
#include "Player.h"

class ScoreManager
{
public:
	ScoreManager();
	float getHighScore();
	void updateHighScore();
	void updatePlayerScore(shared_ptr<Player>&, const std::string _scoreType, const int temperature);
	Text getScore(shared_ptr<Player>&);
	void mSetScoreHUDPos();
	void resetHUDPos();

private:
	int high_score;
	int iceBlockPts; //points per ice block
	int winning; // points for winning
	int enteringIgloo; //points for entering igloo
	int fish; //points for eating fish

	Text score;
	Font score_font;
	vector2f mScoreHUDPos; //position for score  heads up display in multiplayer
	vector2f scoreHUDPos;//position for score heads up display in single player mode
};