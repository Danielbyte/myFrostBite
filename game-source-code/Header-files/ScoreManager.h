#pragma once

#include <sstream>
#include <fstream>
#include "Player.h"
#include "OverWorld.h"

class NegativeScoreError{};

class ScoreManager
{
public:
	ScoreManager();
	int getHighScore() const;
	void updateHighScore(const int currentScore);
	void updatePlayerScore(shared_ptr<Player>&, const std::string _scoreType, const int temperature);
	Text getScore(shared_ptr<Player>&);
	void mSetScoreHUDPos();
	void resetHUDPos();
	void computeWinningScore(OverWorld& _overworld, Stopwatch& _watch, shared_ptr<Player>&, bool& computed,
		int& counter, SoundManager& manage_sound);

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

	std::ifstream highScoreFile;
	std::ofstream output;
};