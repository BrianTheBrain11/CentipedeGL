#ifndef BALL_OBJECT_HPP
#define BALL_OBJECT_HPP

#include "glm/glm.hpp"
#include "texture.hpp"
#include "game_object.hpp"

class BallObject : public GameObject {
public:
	float Radius;
	bool Stuck;

	BallObject();
	BallObject(glm::vec2 pos, float radius, glm::vec2 velocity, Texture2D sprite);

	glm::vec2 Move(float dt, unsigned int window_width);
	void Reset(glm::vec2 position, glm::vec2 velocity);
};

#endif
