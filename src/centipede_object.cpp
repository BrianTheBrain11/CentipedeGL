#include "centipede_object.hpp"
#include <iostream>

CentipedeObject::CentipedeObject(std::string name, glm::vec2 pos, glm::vec2 size, int animationState, std::vector<Texture2D> textureMap, glm::vec3 color, glm::vec2 velocity) : 
	GameObject(name, pos, size, animationState, textureMap, color, velocity)
{
	this->head = false;
}

void CentipedeObject::Draw(SpriteRenderer& renderer)
{
	renderer.DrawSprite(this->textureMap[0], this->Position, this->Size, (float)this->Direction, this->Color);
}