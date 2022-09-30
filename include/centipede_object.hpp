#ifndef CENTIPEDE_OBJECT_HPP
#define CENTIPEDE_OBJECT_HPP

#include "glm/glm.hpp"
#include "texture.hpp"
#include "game_object.hpp"

class CentipedeObject : public GameObject {
public:
	CentipedeObject(CentipedeObject* previous, CentipedeObject* next);
	CentipedeObject* Previous;
	CentipedeObject* Next;
	CentipedeObject* Max();
	CentipedeObject* Min();
	void Tick();
	void Draw(SpriteRenderer& renderer);
private:
	bool head;
};

#endif