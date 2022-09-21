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
//GameObject* Player;

/*const glm::vec2 BULLET_SIZE(8.0f, 16.0f);
const glm::vec2 BULLET_VELOCITY(0.0f, 4000.0f);
BulletObject* Bullet;*/

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
	//ResourceManager::LoadTexture("sprites/background.jpg", false, "background");
	ResourceManager::LoadTexture("sprites/block.png", false, "block");
	//ResourceManager::LoadTexture("sprites/block_solid.png", false, "block_solid");

	// load bullet texture
	ResourceManager::LoadTexture("sprites/Bullet.png", true, "bullet");

	// load mushrooms
	ResourceManager::LoadTexturesFromSpriteMap("sprites/Mushroom.png", true, "mushroom", 16, 16);

	// load Player
	ResourceManager::LoadTexture("sprites/Player.png", true, "player");

	// load centipede textures


	// load starting level
	this->Level.Load("levels/starting_level.lvl", this->Width, this->Height);


	// player init
	glm::vec2 playerPos = glm::vec2(this->Width / 2.0f - PLAYER_SIZE.x / 2.0f, this->Height - PLAYER_SIZE.y);
	Texture2D playerTexture = ResourceManager::GetTexture("player");
	//Player = new GameObject("player", playerPos, PLAYER_SIZE, playerTexture);

}

void Game::Update(float dt)
{
	//Ball->Move(dt, this->Width);
	/*if (Bullet != nullptr)
		Bullet->Move(dt, this->Width);

	this->DoCollisions();

	if (Bullet != nullptr)
	{
		 (Bullet->Position.y >= this->Height) // did ball reach bottom edge?
		{
			this->ResetLevel();
			this->ResetPlayer();
		}
	}*/
}

void Game::ProcessInput(float dt)
{
	if (this->State == GAME_ACTIVE)
	{
		float velocity = PLAYER_VELOCITY * dt;
		// move playerboard
		/*if (this->Keys[GLFW_KEY_A])
		{
			if (Player->Position.x >= 0.0f)
			{
				Player->Position.x -= velocity;
			}
		}
		if (this->Keys[GLFW_KEY_D])
		{
			if (Player->Position.x <= this->Width - Player->Size.x)
			{
				Player->Position.x += velocity;
			}
		}
		if (this->Keys[GLFW_KEY_SPACE] == 1 && Bullet == nullptr)
		{
			glm::vec2 bulletPos = Player->Position + glm::vec2(PLAYER_SIZE.x / 2.0f - BULLET_SIZE.x, -BULLET_SIZE.x * 2.0f);
			Texture2D bulletTexture = ResourceManager::GetTexture("bullet");
			Bullet = new BulletObject("bullet", bulletPos, glm::vec2(8, 16), BULLET_VELOCITY, bulletTexture);
		}*/
	}
}

void Game::Render()
{
	if (this->State == GAME_ACTIVE) {

		// draw background
		Texture2D backgroundTexture = ResourceManager::GetTexture("background");
		Renderer->DrawSprite(backgroundTexture, glm::vec2(0.0f, 0.0f), glm::vec2(this->Width, this->Height), 0.0f);

		// draw level
		Level.Draw(*Renderer);
		//Player->Draw(*Renderer);
		//Ball->Draw(*Renderer);
		/*if (Bullet != nullptr)
			Bullet->Draw(*Renderer);*/
	}
}

bool Game::CheckCollision(BulletObject& one, GameObject& two)
{
	bool collisionX = one.Position.x + one.Size.x >= two.Position.x && two.Position.x + two.Size.x >= one.Position.x;
	bool collisionY = one.Position.y + one.Size.y >= two.Position.y && two.Position.y + two.Size.y >= one.Position.y;

	return collisionX && collisionY;
}

/*Collision Game::CheckCollision(BulletObject& one, GameObject& two)
{

	if (GameObject)

	
	// get center point circle first 
	glm::vec2 center(one.Position + one.Size.x);
	// calculate AABB info (center, half-extents)
	glm::vec2 aabb_half_extents(two.Size.x / 2.0f, two.Size.y / 2.0f);
	glm::vec2 aabb_center(
		two.Position.x + aabb_half_extents.x,
		two.Position.y + aabb_half_extents.y
	);
	// get difference vector between both centers
	glm::vec2 difference = center - aabb_center;
	glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
	// add clamped value to AABB_center and we get the value of box closest to circle
	glm::vec2 closest = aabb_center + clamped;
	// retrieve vector between center circle and closest point AABB and check if length <= radius
	difference = closest - center;

	if (glm::length(difference) <= one.Size.x)
		return std::make_tuple(true, VectorDirection(difference), difference);
	else
		return std::make_tuple(false, UP, glm::vec2(0.0f, 0.0f));
}*/

void Game::DoCollisions()
{
	/*if (Bullet != nullptr)
	{
		for (int i = 0; i < this->Levels[this->Level].Mushrooms.size(); i++)
		{
			GameObject* mushroom = &this->Levels[this->Level].Mushrooms[i];
			if (CheckCollision(*Bullet, *mushroom))
			{
				mushroom->AnimationState++;
				if (mushroom->AnimationState > mushroom->textureMap->size() - 1)
				{
					//delete mushroom;
					this->Levels[this->Level].Mushrooms.erase(this->Levels[this->Level].Mushrooms.begin() + i);
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
	}*/

	

	//Collision result = CheckCollision(*Bullet, *Player);
	/*if (!Bullet->Stuck && std::get<0>(result))
	{
		// check where it hit the board, and change velocity based on where it hit the board
		float centerBoard = Player->Position.x + Player->Size.x / 2.0f;
		float distance = (Bullet->Position.x + Bullet->Size.x) - centerBoard;
		float percentage = distance / (Player->Size.x / 2.0f);

		// then move accordingly
		float strength = 2.0f;
		glm::vec2 oldVelocity = Bullet->Velocity;
		Bullet->Velocity.x = BULLET_VELOCITY * percentage * strength;
		Bullet->Velocity.y = -1.0f * abs(Bullet->Velocity.y);
		Bullet->Velocity = glm::normalize(Bullet->Velocity) * glm::length(oldVelocity);
	}*/
}

Direction Game::VectorDirection(glm::vec2 target)
{
	glm::vec2 compass[] = {
		glm::vec2(0.0f, 1.0f),  // up
		glm::vec2(1.0f, 0.0f),  // right
		glm::vec2(0.0f, -1.0f), // down
		glm::vec2(-1.0f, 0.0f)  // left
	};

	float max = 0.0f;
	unsigned int best_match = -1;
	for (unsigned int i = 0; i < 4; i++)
	{
		float dot_product = glm::dot(glm::normalize(target), compass[i]);
		if (dot_product > max)
		{
			max = dot_product;
			best_match = i;
		}
	}
	return (Direction)best_match;
}

void Game::ResetLevel()
{
}

void Game::ResetPlayer()
{
	// reset player/ball stats
	/*Player->Size = PLAYER_SIZE;
	Player->Position = glm::vec2(this->Width / 2.0f - PLAYER_SIZE.x / 2.0f, this->Height - PLAYER_SIZE.y);*/
	//Bullet->Reset(Player->Position + glm::vec2(PLAYER_SIZE.x / 2.0f - Bullet->Size.x, -(Bullet->Size.x * 2.0f)), glm::vec2(BULLET_VELOCITY));
}