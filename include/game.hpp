#ifndef GAME_HPP
#define GAME_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <map>

#include <glm/glm.hpp>
#include "game_level.hpp"
#include "game_object.hpp"
#include "bullet_object.hpp"

enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

enum Direction {
	UP,
	RIGHT,
	DOWN, 
	LEFT
};

typedef std::tuple<bool, Direction, glm::vec2> Collision;

class Game
{
public:
	GameState State;
	GameLevel Level;
	std::map<int, int> Keys;
	unsigned int Width, Height;

	std::vector<GameLevel> Levels;

	Game(unsigned int width, unsigned int height);
	~Game();

	void Init();
	void ProcessInput(float dt);
	void Update(float dt);
	void Render();
	void DoCollisions();
	void ResetLevel();
	void ResetPlayer();

private:
	//bool CheckCollision(GameObject& one, GameObject& two);
	//bool CheckCollision(BallObject& one, GameObject& two);

	Direction VectorDirection(glm::vec2 target);
	bool CheckCollision(BulletObject& one, GameObject& two);
};

#endif