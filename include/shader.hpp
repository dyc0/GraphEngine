#ifndef SHADER_HPP
#define SHADER_HPP

#include "common.hpp"
#include "errors.hpp"

#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include<vector>

class Shader
{
	public:
	Shader() = default;

	void createVertexShader(const std::string& vertSrc);
	void createFragmentShader(const std::string& fragSrc);
	void generateShaderProgram();

	void setPerspective(const glm::mat4 perspective);
	void setCamera(const glm::mat4 camera);
	void bindGlobalTransforms() const;

	GLuint getProgram() const;

	protected:
	std::string load_shader(const std::string& fileName) const;
	bool checkShaderError(GLuint shader) const;
	void createShader(GLuint& shader, const std::string& source);

	private:
	GLuint vertexShader, fragmentShader;
	GLuint shaderProgram;

	glm::mat4 view;
	glm::mat4 proj;
};

#endif
