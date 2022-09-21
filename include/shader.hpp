#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// General purpose shader object compiles from files, generates and compiles shader with error messages

class Shader
{
public:
	unsigned int ID;

	Shader() {}

	Shader& Use();

	void Compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource = nullptr);

    void    SetFloat(const char* name, float value, bool useShader = false);
    void    SetInteger(const char* name, int value, bool useShader = false);
    void    SetVector2f(const char* name, float x, float y, bool useShader = false);
    void    SetVector2f(const char* name, const glm::vec2& value, bool useShader = false);
    void    SetVector3f(const char* name, float x, float y, float z, bool useShader = false);
    void    SetVector3f(const char* name, const glm::vec3& value, bool useShader = false);
    void    SetVector4f(const char* name, float x, float y, float z, float w, bool useShader = false);
    void    SetVector4f(const char* name, const glm::vec4& value, bool useShader = false);
    void    SetMatrix4(const char* name, const glm::mat4& matrix, bool useShader = false);

private:
    void checkCompileErrors(unsigned int object, std::string type);
};

#endif