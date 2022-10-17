#include "game_level.hpp"
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>


void GameLevel::Load(const char* file, unsigned int levelWidth, unsigned int levelHeight)
{
    // clear old data
    this->Mushrooms.clear();
    // load from file
    unsigned int tileCode;
    GameLevel level;
    std::string line;
    std::ifstream fstream(file);
    std::vector<std::vector<unsigned int>> tileData;
    if (fstream)
    {
        while (std::getline(fstream, line)) // read each line from level file
        {
            std::istringstream sstream(line);
            std::vector<unsigned int> row;
            while (sstream >> tileCode) // read each word separated by spaces
                row.push_back(tileCode);
            tileData.push_back(row);
        }
        if (tileData.size() > 0)
            this->init(tileData, levelWidth, levelHeight);
    }
}

void GameLevel::init(std::vector<std::vector<unsigned int>> tileData,
    unsigned int lvlWidth, unsigned int lvlHeight)
{
    // calculate dimensions
    unsigned int height = tileData.size();
    unsigned int width = tileData[0].size();
    float unit_width = lvlWidth / static_cast<float>(width);
    float unit_height = lvlHeight / height;
    // initialize level tiles based on tileData		
    for (unsigned int y = 0; y < height; ++y)
    {
        for (unsigned int x = 0; x < width; ++x)
        {
            if (tileData[y][x] == 1)
            {
                glm::vec2 pos(unit_width * x, unit_height * y);
                glm::vec2 size(unit_width, unit_height);
                std::vector<Texture2D> objTexture = ResourceManager::GetTextures("mushroom");
                GameObject obj("mushroom", pos, size, 0, objTexture, glm::vec3(1.0f, 1.0f, 1.0f));
                obj.AnimationState = 0;
                obj.IsSolid = true;
                std::cout << ResourceManager::GetTextures("mushroom").size() << " is full size" << std::endl;
                this->Mushrooms.push_back(obj);
            }
        }
    }
}

void GameLevel::Draw(SpriteRenderer& renderer)
{
    for (GameObject& tile : this->Mushrooms)
        if (!tile.Destroyed)
            tile.Draw(renderer);
}

bool GameLevel::IsCompleted()
{
    for (GameObject& tile : this->Mushrooms)
        if (!tile.IsSolid && !tile.Destroyed)
            return false;
    return true;
}