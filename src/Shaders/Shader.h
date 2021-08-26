#pragma once
#include "Core/include.h"
#include "Core/Components/Camera.h"
#include "Scenes/Scene.h"
// Vertex & Fragment
static int CreateShader(unsigned int vs, unsigned int fs) {
	unsigned int program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);
	glDeleteShader(vs);
	glDeleteShader(fs);
	return program;
}
// Vertex, Geometry & Fragment
static int CreateShader(unsigned int vs, unsigned int fs, unsigned int geo) {
	unsigned int program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, geo);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);
	glDeleteShader(vs);
	glDeleteShader(geo);
	glDeleteShader(fs);
	return program;
}
// Update Uniforms
static void SetMat4(unsigned int shader,  std::string u_Name, const glm::mat4& m)
{
	int Mat4Location = glGetUniformLocation(shader, u_Name.c_str());
	if (Mat4Location == GL_INVALID_VALUE || Mat4Location == GL_INVALID_OPERATION || Mat4Location == -1) SDL_LogError(SDL_LOG_CATEGORY_CUSTOM, "Error loading %s matrix", u_Name.c_str());
	else
	{
		glUniformMatrix4fv(Mat4Location, 1, GL_FALSE, glm::value_ptr(m));
	}
}
static void SetVec3(unsigned int shader, std::string u_Name, const glm::vec3& v)
{
	int Vec3Location = glGetUniformLocation(shader, u_Name.c_str());
	if (Vec3Location == GL_INVALID_VALUE || Vec3Location == GL_INVALID_OPERATION || Vec3Location == -1) SDL_LogError(SDL_LOG_CATEGORY_CUSTOM, "Error loading %s vec3", u_Name.c_str());
	else
	{
		glUniform3f(Vec3Location, v.x, v.y, v.z);
	}
}
static void SetFloat(unsigned int shader, std::string u_Name, const float f)
{
	int FloatLocation = glGetUniformLocation(shader, u_Name.c_str());
	if (FloatLocation == GL_INVALID_VALUE || FloatLocation == GL_INVALID_OPERATION || FloatLocation == -1) SDL_LogError(SDL_LOG_CATEGORY_CUSTOM, "Error loading %s float", u_Name.c_str());
	else
	{
		glUniform1f(FloatLocation, f);
	}
}
static void SetInt(unsigned int shader, std::string u_Name, const int i)
{
	int IntLocation = glGetUniformLocation(shader, u_Name.c_str());
	if (IntLocation == GL_INVALID_VALUE || IntLocation == GL_INVALID_OPERATION || IntLocation == -1) SDL_LogError(SDL_LOG_CATEGORY_CUSTOM, "Error loading %s int", u_Name.c_str());
	else
	{
		glUniform1i(IntLocation, i);
	}
}

class Shader
{
public:
	Shader(const std::string& filePath, unsigned int type) {
		std::string source;
		std::ifstream ShaderFile;
		ShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try {
			ShaderFile.open(filePath);
			std::stringstream ShaderStream;
			ShaderStream << ShaderFile.rdbuf();
			ShaderFile.close();
			source = ShaderStream.str();
		}
		catch (std::ifstream::failure& e) {
			SDL_LogCritical(SDL_LOG_CATEGORY_CUSTOM, "error loading shader file: %s, %s", filePath.c_str(), e.what());
		}
		ID = glCreateShader(type);
		src = source.c_str();
		glShaderSource(ID, 1, &src, nullptr);
		glCompileShader(ID);
		int result;
		glGetShaderiv(ID, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE) {
			int length;
			glGetShaderiv(ID, GL_INFO_LOG_LENGTH, &length);
			char* message = (char*)alloca(length * sizeof(char));
			glGetShaderInfoLog(ID, length, &length, message);
			SDL_LogCritical(SDL_LOG_CATEGORY_CUSTOM, "%s", message);
			glDeleteShader(ID);
		}
	}
public:
	unsigned int ID;
private:
	const char* src;
};