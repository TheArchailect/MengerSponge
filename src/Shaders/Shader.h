#pragma once
#include "../Core/include.h"
#include "../Core/Camera.h"
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
static void UpdateShader
(
	unsigned int shader,
	const glm::mat4& model,
	const glm::mat4& view,
	const glm::mat4& projection,
	Camera& camera
) 
{
	// matricies
	int ModelLocation = glGetUniformLocation(shader, "Model");
	glUniformMatrix4fv(ModelLocation, 1, GL_FALSE, glm::value_ptr(model));
	int ViewLocation = glGetUniformLocation(shader, "View");
	glUniformMatrix4fv(ViewLocation, 1, GL_FALSE, glm::value_ptr(view));
	int ProjectionLocation = glGetUniformLocation(shader, "Projection");
	glUniformMatrix4fv(ProjectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
	// misc uniforms
	int SystemTime = glGetUniformLocation(shader, "SystemTime");
	glUniform1f(SystemTime, SDL_GetTicks());
	// camera
	int CameraLocation = glGetUniformLocation(shader, "Camera");
	glUniform3f
	(
		CameraLocation, 
		camera.m_Position.x, 
		camera.m_Position.y, 
		camera.m_Position.z
	);
	// lighting
	int DirectionLocation = glGetUniformLocation(shader, "u_Light.Direction");
	glUniform3f(DirectionLocation, -0.2, -1.0, -0.3);
	int AmbientLocation = glGetUniformLocation(shader, "u_Light.Ambient");
	glUniform3f(AmbientLocation, 0.05f, 0.05f, 0.05f);
	int DiffuseLocation = glGetUniformLocation(shader, "u_Light.Diffuse");
	glUniform3f(DiffuseLocation, 0.4f, 0.4f, 0.4f);
	int SpecularLocation = glGetUniformLocation(shader, "u_Light.Specular");
	glUniform3f(SpecularLocation, 0.5f, 0.5f, 0.5f);
	// materials
	int MaterialDiffuseLocation = glGetUniformLocation(shader, "u_Material.Diffuse");
	glUniform3f(MaterialDiffuseLocation, 0.5f, 0.5f, 0.3f);
	int MaterialShininessLocation = glGetUniformLocation(shader, "u_Material.Shininess");
	glUniform1f(MaterialShininessLocation, 64);
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
			//ALT_CORE_ERROR("error opening shader file: {0}\n{1}", filePath, e.what());
			std::cout << "error opening shader file : " << filePath << e.what() << std::endl;
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
			//ALT_CORE_ERROR(message);
			glDeleteShader(ID);
		}
	}
public:
	unsigned int ID;
private:
	const char* src;
};