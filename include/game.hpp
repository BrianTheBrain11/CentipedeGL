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
#include "centipede_object.hpp"

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
	double lastTime;
	std::vector<GameLevel> Levels;
	std::vector<std::vector<CentipedeObject>> Centipedes;

	Game(unsigned int width, unsigned int height);
	~Game();

	void Init();
	void CentipedeInit(int bodyLength);
	void ProcessInput(float dt);
	void Update(float dt);
	void Render();
	void CentipedeDraw(SpriteRenderer& renderer);
	void DoCollisions();
	void ResetLevel();
	void ResetPlayer();

private:
	//bool CheckCollision(GameObject& one, GameObject& two);
	//bool CheckCollision(BallObject& one, GameObject& two);

	Direction VectorDirection(glm::vec2 target);
	bool CheckCollision(GameObject& one, GameObject& two);
	bool CheckCollision(GameObject& one, glm::vec2& twoPos, glm::vec2& twoSize);
	bool CheckCollision(glm::vec2& onePos, glm::vec2& oneSize, GameObject& two);
};

#endif
