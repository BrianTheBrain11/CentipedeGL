#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <map>

#include "texture.hpp"
#include <vector>

#include "sprite_renderer.hpp"

class GameObject
{
public:

	std::vector<Texture2D>* textureMap;
	std::string Name;
	// object state
	glm::vec2 Position, Size, Velocity;
	glm::vec3 Color;
	float Rotation;
	bool IsSolid;
	bool Destroyed;
	int AnimationState;

	// current render state

	//constructors
	GameObject();
	GameObject(std::string name, glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f));
	GameObject(std::string name, glm::vec2 pos, glm::vec2 size, int animationState, std::vector<Texture2D> textureMap, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f));
	
	// draw sprite
	virtual void Draw(SpriteRenderer& renderer);
};

#endif