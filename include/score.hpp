#ifndef SCORE_HPP
#define SCORE_HPP

#include <vector>

#include "game_object.hpp"

class Score {
public:
	Score();
	Score(int points);
	int Points;
	int Lives;
	std::vector<GameObject> ScoreObjects;
	std::vector<GameObject> LifeCounter;

	void Update();
	void Draw(SpriteRenderer& renderer);
	void Reset();
};

#endif