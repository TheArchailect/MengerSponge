#pragma once
#include "../Core/include.h"
#include "Shader.h"
class ShaderProgram {
public:
	ShaderProgram(const std::string& vs_filePath, const std::string& fs_filePath) {
		vs = new Shader(vs_filePath, GL_VERTEX_SHADER);
		fs = new Shader(fs_filePath, GL_FRAGMENT_SHADER);
		shader = CreateShader(vs->ID, fs->ID);
		geo = nullptr;
	}
	ShaderProgram(const std::string& vs_filePath, 
		const std::string& geo_filePath, 
		const std::string& fs_filePath) {
		vs = new Shader(vs_filePath, GL_VERTEX_SHADER);
		fs = new Shader(fs_filePath, GL_FRAGMENT_SHADER);
		geo = new Shader(geo_filePath, GL_GEOMETRY_SHADER);
		shader = CreateShader(vs->ID, fs->ID, geo->ID);
	}
	unsigned int GetShaderProgramID() { return shader; };
private:
	unsigned int shader;
	Shader* vs;
	Shader* fs;
	Shader* geo;
};