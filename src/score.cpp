#include <math.h>
#include <iostream>
#include <string>
#include <stdio.h>

#include "score.hpp"
#include "resource_manager.hpp"

Score::Score()
{

}

Score::Score(int points)
{
	this->Points = points;
	this->Lives = 3;
}

void Score::Update()
{	
	this->ScoreObjects.clear();
	int points = this->Points;
	std::string pointsString = std::to_string(points);
	int digitLength = pointsString.length();

	for (int i = 1; points > 0; i++)
	{
		glm::vec2 pos(112 - ((i - 1) * 16), 0);
		glm::vec2 size(16, 16);
		std::vector<Texture2D> objTexture = ResourceManager::GetTextures("numbers");
		GameObject obj("numbers", pos, size, 0, objTexture, glm::vec3(1.0f, 1.0f, 1.0f));
		obj.AnimationState = points % 10;
		obj.IsSolid = true;
		this->ScoreObjects.push_back(obj);

		points /= 10 * i;
	}

	// iterating digit by digit, get digit
	/*for (int i = 0; i < digitLength; i++) {
		int digit = pointsString.c_str()[i];
		glm::vec2 pos(16 * 1, 16 * 1 + 16);
		glm::vec2 size(16, 16);
		std::vector<Texture2D> objTexture = ResourceManager::GetTextures("numbers");
		GameObject obj("numbers", pos, size, 0, objTexture, glm::vec3(1.0f, 1.0f, 1.0f));
		obj.AnimationState = 0;
		obj.IsSolid = true;
		this->ScoreObjects.push_back(obj);
	}*/
}

void Score::Draw(SpriteRenderer& renderer)
{
	for (int i = 0; i < this->ScoreObjects.size(); i++)
	{
		GameObject scoreObj = this->ScoreObjects[i];
		scoreObj.Draw(renderer);
	}
}

void Score::Reset()
{
	this->Points = 0;
	this->ScoreObjects.clear();
}