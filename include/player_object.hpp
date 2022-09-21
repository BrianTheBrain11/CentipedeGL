#ifndef PLAYER_OBJECT_HPP
#define PLAYER_OBJECT_HPP

#include "glm/glm.hpp"
#include "texture.hpp"
#include "game_object.hpp"

class PlayerObject : public GameObject {
public:

	PlayerObject();
	PlayerObject(glm::vec2 pos, float radius, glm::vec2 velocity, Texture2D sprite);

	glm::vec2 Move(float dt, unsigned int window_width);
	void Reset(glm::vec2 position, glm::vec2 velocity);
};

#endif