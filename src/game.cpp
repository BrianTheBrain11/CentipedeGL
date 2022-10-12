#include <iostream>

#include "game.hpp"
#include "resource_manager.hpp"
#include "sprite_renderer.hpp"
#include "ball_object.hpp"
#include "bullet_object.hpp"

Game::Game(unsigned int width, unsigned int height) : State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{

}

Game::~Game()
{

}

SpriteRenderer* Renderer;

const glm::vec2 PLAYER_SIZE(16.0f, 16.0f);
const float PLAYER_VELOCITY(500.0f);
GameObject* Player;

const glm::vec2 BULLET_SIZE(8.0f, 16.0f);
const glm::vec2 BULLET_VELOCITY(0.0f, 4000.0f);
BulletObject* Bullet;
glm::vec2 bodyPos = glm::vec2(16.0, 16.0);

void Game::Init()
{
	// load shader
	ResourceManager::LoadShader("shaders/sprite.vert", "shaders/sprite.frag", nullptr, "sprite");

	// configure shader
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width),
		static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite").Use().SetMatrix4("projection", projection);


	Shader shader = ResourceManager::GetShader("sprite");
	// set render-specific controls
	Renderer = new SpriteRenderer(shader);
	
	// load textures
	ResourceManager::LoadTexture("sprites/background.jpg", false, "background");
	ResourceManager::LoadTexture("sprites/block.png", false, "block");

	// load bullet texture
	ResourceManager::LoadTexture("sprites/Bullet.png", true, "bullet");

	// load mushrooms
	ResourceManager::LoadTexturesFromSpriteMap("sprites/Mushroom.png", true, "mushroom", 16, 16);

	// load Player
	ResourceManager::LoadTexture("sprites/Player.png", true, "player");

	// load centipede textures
	ResourceManager::LoadTexturesFromSpriteMap("sprites/Centipede_Body.png", true, "centipede_body", 16, 16);

	// load starting level
	this->Level.Load("levels/starting_level.lvl", this->Width, this->Height);


	// player init
	glm::vec2 playerPos = glm::vec2(this->Width / 2.0f - PLAYER_SIZE.x / 2.0f, this->Height - PLAYER_SIZE.y);
	Texture2D playerTexture = ResourceManager::GetTexture("player");
	Player = new GameObject("player", playerPos, PLAYER_SIZE, playerTexture);

	CentipedeInit(5);
}

void Game::CentipedeInit(int bodyLength)
{
	std::vector<CentipedeObject> centipede;
	std::vector<Texture2D> centipedeTextures = ResourceManager::GetTextures("centipede_body");
	CentipedeObject prevBody("centipede_body", glm::vec2(240.0, 32.0), glm::vec2(16.0, 16.0), 0, centipedeTextures, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0));
	prevBody.head = true;
	prevBody.CourseX = Heading::EAST;
	std::cout << prevBody.textureMap.size() << " debug size" << std::endl;
	centipede.push_back(prevBody);
	for (int i = 1; i < bodyLength; i++)
	{
		CentipedeObject newBody = CentipedeObject("centipede_body", glm::vec2(240.0 + 16.0*i, 32.0), glm::vec2(16.0), 0, centipedeTextures, glm::vec3(1.0f), glm::vec3(0.0));
		centipede.push_back(newBody);
		newBody.CourseX = Heading::EAST;
	}
	Centipedes.push_back(centipede);
}

void Game::Update(float dt)
{
	CentipedeTick();
	if (Bullet != nullptr)
		Bullet->Move(dt, this->Width);

	this->DoCollisions();

	if (Bullet != nullptr)
	{
		if (Bullet->Position.y >= this->Height) // did ball reach bottom edge?
		{
			this->ResetLevel();
			this->ResetPlayer();
		}
	}

}

void Game::ProcessInput(float dt)
{
	if (this->State == GAME_ACTIVE)
	{
		float velocity = PLAYER_VELOCITY * dt;
		//move playerboard
		glm::vec2 newPos = Player->Position;
		glm::vec2 initPos = Player->Position;

		if (this->Keys[GLFW_KEY_A])
		{
			if (newPos.x >= 0.0f)
			{
				newPos.x -= velocity;
			}
		}
		if (this->Keys[GLFW_KEY_D])
		{
			if (newPos.x <= this->Width - Player->Size.x)
			{
				newPos.x += velocity;
			}
		}
		if (this->Keys[GLFW_KEY_W]) {
			if (newPos.y >= 0.0f)
			{
				newPos.y -= velocity;
			}
		}
		if (this->Keys[GLFW_KEY_S]) {
			if (newPos.y <= this->Height - Player->Size.y)
			{
				newPos.y += velocity;
			}
		}
		Player->Position = newPos;

		for (int i = 0; i < this->Level.Mushrooms.size(); i++)
		{
			GameObject* mushroom = &this->Level.Mushrooms[i];
			if (CheckCollision(*Player, *mushroom))
			{
				newPos = initPos;
			}
		}

		Player->Position = newPos;	

		if (this->Keys[GLFW_KEY_SPACE] == 1 && Bullet == nullptr)
		{
			glm::vec2 bulletPos = Player->Position + glm::vec2(PLAYER_SIZE.x / 2.0f - BULLET_SIZE.x, -BULLET_SIZE.x * 2.0f);
			Texture2D bulletTexture = ResourceManager::GetTexture("bullet");
			Bullet = new BulletObject("bullet", bulletPos, glm::vec2(8, 16), BULLET_VELOCITY, bulletTexture);
		}
	}
}

void Game::CentipedeTick()
{
	for (int i = 0; i < Centipedes.size(); i++)
	{
		std::vector<CentipedeObject>* centipede = &Centipedes[i];
		CentipedeObject* lastObj = nullptr;
		for (int j = 0; j < centipede->size(); j++)
		{

			int xDirectionInverter = 1;
			int* i = &xDirectionInverter;

			CentipedeObject* bodyObj = &(*centipede)[j];
			if (bodyObj->CourseX == Heading::WEST)
				*i = -1;


			bodyObj->LastDirection = bodyObj->Direction;
			bodyObj->Direction = bodyObj->CourseX;

			glm::vec2 newPos = bodyObj->Position;
			glm::vec2 initPos = bodyObj->Position;

			if (bodyObj->LastTurnDownPosition.y > bodyObj->Position.y -16.0)
			{
				newPos += glm::vec2(0.0 * *i, 1.0);
				bodyObj->Direction = Heading::SOUTH;
			}
			else
			{
				newPos += glm::vec2(1.0 * *i, 0.0);

				bodyObj->Position = newPos;

				if (CheckCollisionWalls(*bodyObj))
				{
					if (bodyObj->CourseX == Heading::WEST)
						bodyObj->CourseX = Heading::EAST;
					else
						bodyObj->CourseX = Heading::WEST;

					newPos += glm::vec2(-1.0 * *i, 0.0);
					bodyObj->Direction = bodyObj->CourseX;
					bodyObj->LastTurnDownPosition = newPos;
					newPos += glm::vec2(0.0 * *i, 1.0);

				}
				else
				{
					for (int k = 0; k < this->Level.Mushrooms.size(); k++)
					{
						GameObject* mushroom = &this->Level.Mushrooms[k];
						if (CheckCollision(*bodyObj, *mushroom))
						{
							if (bodyObj->CourseX == Heading::WEST)
								bodyObj->CourseX = Heading::EAST;
							else
								bodyObj->CourseX = Heading::WEST;

							newPos += glm::vec2(-1.0 * *i, 0.0);
							bodyObj->Direction = Heading::SOUTH;
							bodyObj->LastTurnDownPosition = newPos;
							newPos += glm::vec2(0.0 * *i, 1.0);
						}
					}
				}
			}

			bodyObj->Position = newPos;

			lastObj = bodyObj;
		}
	}
}

void Game::Render()
{
	if (this->State == GAME_ACTIVE) {

		// draw background
		Texture2D backgroundTexture = ResourceManager::GetTexture("background");
		Renderer->DrawSprite(backgroundTexture, glm::vec2(0.0f, 0.0f), glm::vec2(this->Width, this->Height), 0.0f);

		// draw level
		CentipedeDraw(*Renderer);
		Level.Draw(*Renderer);
		Player->Draw(*Renderer);
		if (Bullet != nullptr)
			Bullet->Draw(*Renderer);
	}
}

void Game::CentipedeDraw(SpriteRenderer& renderer)
{
	for (auto& centipede : Centipedes)
	{
		for (auto& bodyObj : centipede)
		{
			bodyObj.Draw(renderer);
		}
	}
}

bool Game::CheckCollisionWalls(GameObject& one)
{
	bool collisionX = one.Position.x + one.Size.x > this->Width || one.Position.x < 0;
	bool collisionY = one.Position.y + one.Size.y > this->Height || one.Position.y < 0;

	if (collisionX || collisionY)
		std::cout << "collision with wall" << std::endl;

	return collisionX || collisionY;
}

bool Game::CheckCollision(GameObject& one, GameObject& two)
{
	bool collisionX = one.Position.x + one.Size.x > two.Position.x && two.Position.x + two.Size.x > one.Position.x;
	bool collisionY = one.Position.y + one.Size.y > two.Position.y && two.Position.y + two.Size.y > one.Position.y;

	return collisionX && collisionY;
}

bool Game::CheckCollision(GameObject& one, glm::vec2& twoPos, glm::vec2& twoSize)
{
	bool collisionX = one.Position.x + one.Size.x > twoPos.x && twoPos.x + twoSize.x > one.Position.x;
	bool collisionY = one.Position.y + one.Size.y > twoPos.y && twoPos.y + twoSize.y > one.Position.y;

	return collisionX && collisionY;
}

bool Game::CheckCollision(glm::vec2& onePos, glm::vec2& oneSize, GameObject& two)
{
	bool collisionX = onePos.x + oneSize.x > two.Position.x && two.Position.x + two.Size.x > onePos.x;
	bool collisionY = onePos.y + oneSize.y > two.Position.y && two.Position.y + two.Size.y > onePos.y;

	return collisionX && collisionY;
}

void Game::DoCollisions()
{
	if (Bullet != nullptr)
	{
		for (int i = 0; i < this->Level.Mushrooms.size(); i++)
		{
			GameObject* mushroom = &this->Level.Mushrooms[i];
			if (CheckCollision(*Bullet, *mushroom))
			{
				mushroom->AnimationState++;
				if (mushroom->AnimationState > mushroom->textureMap.size() - 1)
				{
					//delete mushroom;
					this->Level.Mushrooms.erase(this->Level.Mushrooms.begin() + i);
				}

				delete Bullet;
				Bullet = nullptr;
				return;
			}
		}
		
		if (Bullet->Position.y < 0)
		{
			delete Bullet;
			Bullet = nullptr;
			return;
		}
	}
}

void Game::ResetLevel()
{
}

void Game::ResetPlayer()
{
	// reset player/ball stats
	/*Player->Size = PLAYER_SIZE;
	/*Player->Size = PLAYER_SIZE;
	Player->Position = glm::vec2(this->Width / 2.0f - PLAYER_SIZE.x / 2.0f, this->Height - PLAYER_SIZE.y);*/
	//Bullet->Reset(Player->Position + glm::vec2(PLAYER_SIZE.x / 2.0f - Bullet->Size.x, -(Bullet->Size.x * 2.0f)), glm::vec2(BULLET_VELOCITY));
}

