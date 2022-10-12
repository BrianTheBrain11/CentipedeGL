#ifndef CENTIPEDE_OBJECT_HPP
#define CENTIPEDE_OBJECT_HPP

#include "glm/glm.hpp"
#include "texture.hpp"
#include "game_object.hpp"

enum class Heading {
	NORTH = -90,
	EAST = 0,
	SOUTH = 90,
	WEST = 180
};

class CentipedeObject : public GameObject {
public:
	CentipedeObject(std::string name, glm::vec2 pos, glm::vec2 size, int animationState, std::vector<Texture2D> textureMap, glm::vec3 color, glm::vec2 velocity);

	bool head;
	void Draw(SpriteRenderer& renderer);
	Heading Course;
	Heading Direction;
	Heading LastDirection = Heading::EAST;
	glm::vec2 LastTurnDownPosition;
};

#endif