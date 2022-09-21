#ifndef BULLET_OBJECT_HPP
#define BULLET_OBJECT_HPP

#include "game_object.hpp"


class BulletObject : public GameObject {
public:
	BulletObject();
	BulletObject(std::string name, glm::vec2 pos, glm::vec2 size, glm::vec2 velocity, Texture2D sprite);

	glm::vec2 Size;
	bool Stuck;
	glm::vec2 Move(float dt, unsigned int window_width);
	void Reset(glm::vec2 position, glm::vec2 velocity);
private:

};

#endif