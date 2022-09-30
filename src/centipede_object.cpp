#include "centipede_object.hpp"

CentipedeObject::CentipedeObject(CentipedeObject* previous, CentipedeObject* next) : Previous(previous), Next(next)
{
	this->head = false;
	if (previous == nullptr)
	{
		this->head = true;
	}
}

CentipedeObject* CentipedeObject::Max()
{
	CentipedeObject* nextIt = this->Previous;
	CentipedeObject* max = nullptr;
	while (nextIt->Previous != nullptr)
	{
		max = nextIt->Previous;
	}
	return max;
}

CentipedeObject* CentipedeObject::Min()
{
	CentipedeObject* nextIt = this->Next;
	CentipedeObject* min = nullptr;
	while (nextIt->Next != nullptr)
	{
		min = nextIt->Next;
	}
	return min;
}

void CentipedeObject::Draw(SpriteRenderer& renderer)
{
	renderer.DrawSprite(this->textureMap[this->AnimationState], this->Position, this->Size, this->Rotation, this->Color);
}

void CentipedeObject::Tick()
{
	CentipedeObject* maxObj = this->Max();
	CentipedeObject* minObj = this->Min();

	maxObj->Next->Previous = nullptr;
	maxObj->Previous = nullptr;
	maxObj->Next = minObj;

	minObj->Next = nullptr;

	maxObj = this->Max();
}