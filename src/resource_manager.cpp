#include <span>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

#include "stb_image.h"
#include "resource_manager.hpp"

// Instantiate static variables
std::map<std::string, Texture2D>                ResourceManager::Textures;
std::map<std::string, Shader>                   ResourceManager::Shaders;
std::map<std::string, std::vector<Texture2D>>   ResourceManager::TextureMaps;


Shader ResourceManager::LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name)
{
    Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
    return Shaders[name];
}

Shader ResourceManager::GetShader(std::string name)
{
    return Shaders[name];
}

Texture2D ResourceManager::LoadTexture(const char* file, bool alpha, std::string name)
{
    Textures[name] = loadTextureFromFile(file, alpha);
    return Textures[name];
}

void ResourceManager::LoadTexturesFromSpriteMap(const char* file, bool alpha, std::string name, unsigned int height_, unsigned int width_)
{
    std::vector<Texture2D> textureMap;
    loadTexturesFromFile(file, alpha, height_, width_, &textureMap);
    std::cout << "size of texture map " << textureMap.size() << std::endl;
    for (int i = 0; i < textureMap.size(); i++)
    {
        std::string textureName = name + "_";
        textureName += std::to_string(i);
        Textures[textureName] = textureMap[i];
        TextureMaps[textureName] = textureMap;
        std::cout << textureName << std::endl;
    }
    TextureMaps[name] = textureMap;
}

Texture2D ResourceManager::GetTexture(std::string name)
{
    return Textures[name];
}

std::vector<Texture2D> ResourceManager::GetTextures(std::string name)
{
    return TextureMaps[name];
}

void ResourceManager::Clear()
{
    // (properly) delete all shaders	
    for (auto iter : Shaders)
        glDeleteProgram(iter.second.ID);
    // (properly) delete all textures
    for (auto iter : Textures)
        glDeleteTextures(1, &iter.second.ID);
}

Shader ResourceManager::loadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile)
{
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    try
    {
        // open files
        std::ifstream vertexShaderFile(vShaderFile);
        std::ifstream fragmentShaderFile(fShaderFile);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();
        // close file handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        // if geometry shader path is present, also load a geometry shader
        if (gShaderFile != nullptr)
        {
            std::ifstream geometryShaderFile(gShaderFile);
            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    }
    catch (std::exception e)
    {
        std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    const char* gShaderCode = geometryCode.c_str();
    // 2. now create shader object from source code
    Shader shader;
    shader.Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
    return shader;
}

Texture2D ResourceManager::loadTextureFromFile(const char* file, bool alpha)
{
    // create texture object
    Texture2D texture;
    if (alpha)
    {
        texture.Internal_Format = GL_RGBA;
        texture.Image_Format = GL_RGBA;
    }
    // load image
    int width, height, nrChannels;
    unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);
    // now generate texture
    texture.Generate(width, height, data);
    std::cout << width << std::endl;
    std::cout << height << std::endl;
    // and finally free image data
    stbi_image_free(data);
    return texture;
}

void ResourceManager::loadTexturesFromFile(const char* file, bool alpha, int width_, int height_, std::vector<Texture2D>* textureMap_)
{
    int width, height, nrChannels;
    unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 4);
    for (int i = 0; i < height/height_; i+=1)
    {
        int dataPointer = (i * width_ * height_ * 4);
        Texture2D subSpriteTexture;
        if (alpha)
        {
            subSpriteTexture.Internal_Format = GL_RGBA;
            subSpriteTexture.Image_Format = GL_RGBA;
        }

        unsigned char subData[1024];
        unsigned char* subDataPtr = subData;
        memcpy(subData, data + dataPointer, 1024);


        subSpriteTexture.Generate(width_, height_, subData);
        textureMap_->push_back(subSpriteTexture);
        std::cout << "add 1 to texture map full size " << textureMap_->size() << std::endl;
    }

    stbi_image_free(data);
}