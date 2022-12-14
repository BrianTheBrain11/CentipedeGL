#ifndef GAME_HPP
#define GAME_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <vector>
#include <map>

#include "game_level.hpp"
#include "game_object.hpp"
#include "bullet_object.hpp"
#include "centipede_object.hpp"
#include "score.hpp"

enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

class Game
{
public:
	GameState State;
	GameLevel Level;
	Score GameScore;
	std::map<int, int> Keys;
	unsigned int Width, Height;
	double lastTime;
	std::vector<GameLevel> Levels;
	std::vector<std::vector<CentipedeObject>> Centipedes;

	Game(unsigned int width, unsigned int height);
	~Game();

	void Init(void);
	void CentipedeInit(int bodyLength);
	void ProcessInput(float dt);
	void ProcessBullet();
	void Update(float dt);
	void CentipedeTick(int speedSelection);
	void Render(void);
	void CentipedeDraw(SpriteRenderer& renderer);
	void DoCollisions(void);
	void ResetLevel(void);
	void ResetPlayer(void);

private:
	bool CheckCollision(GameObject& one, GameObject& two);
	bool CheckCollision(GameObject& one, glm::vec2& twoPos, glm::vec2& twoSize);
	bool CheckCollision(glm::vec2& onePos, glm::vec2& oneSize, GameObject& two);
	bool CheckCollisionWalls(GameObject& one);
};

#endif
