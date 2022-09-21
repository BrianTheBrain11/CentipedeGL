#include "bullet_object.hpp"


BulletObject::BulletObject() : GameObject(), Size(glm::vec2(16.0f, 16.0f)), Stuck(true) { }
BulletObject::BulletObject(std::string name, glm::vec2 pos, glm::vec2 size, glm::vec2 velocity, Texture2D sprite) : GameObject(name, pos, size, sprite, glm::vec3(1.0f), velocity), Size(size), Stuck(true) { }

glm::vec2 BulletObject::Move(float dt, unsigned int window_width)
{
	this->Position += glm::vec2(-dt * this->Velocity.x, -dt * this->Velocity.y);
	return this->Position;
}

void BulletObject::Reset(glm::vec2 position, glm::vec2 velocity)
{
	this->Position = position;
	this->Velocity = velocity;
	this->Stuck = true;
}