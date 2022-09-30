#include <iostream>
#include <string>
#include <map>

#include "game_object.hpp"
#include "texture.hpp"
#include "resource_manager.hpp"

GameObject::GameObject() : Name(" "), Position(0.0f, 0.0f), Size(1.0f, 1.0f), Velocity(0.0f), Color(1.0f), Rotation(0.0f), IsSolid(false), Destroyed(false), AnimationState(0) {}
GameObject::GameObject(std::string name, glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color, glm::vec2 velocity) : Name(name), Position(pos), Size(size), Sprite(sprite), Velocity(velocity), Color(color), Rotation(0.0f), IsSolid(false), Destroyed(false), isMultiFrame(false) {}

GameObject::GameObject(std::string name, glm::vec2 pos, glm::vec2 size, int animationState, std::vector<Texture2D> textureMap, glm::vec3 color, glm::vec2 velocity) : Name(name), Position(pos), AnimationState(animationState),  Size(size), Velocity(velocity), Color(color), Rotation(0.0f), IsSolid(false), Destroyed(false), isMultiFrame(true)
{
	this->textureMap = textureMap;
	std::cout << "internal map size" << this->textureMap.size() << std::endl;
}


void GameObject::Draw(SpriteRenderer& renderer)
{
	Texture2D spriteText;
	if (this->isMultiFrame)
		spriteText = this->textureMap[this->AnimationState];
	else
		spriteText = this->Sprite;
	renderer.DrawSprite(spriteText, this->Position, this->Size, this->Rotation, this->Color);
}