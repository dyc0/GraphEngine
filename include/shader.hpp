#ifndef SHADER_HPP
#define SHADER_HPP

#include <fstream>
#include <iostream>
#include <string>

#include <GL/glew.h>

#include "transform.hpp"
#include "camera.hpp"

class Shader
{
    public:
    Shader(const std::string& fileName);
    virtual ~Shader();

    void bind();
	void update(const Transform& transform, const Camera& camera);

    protected:
    std::string load_shader(const std::string& fileName) const;
    static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
    static GLuint create_shader(const std::string& text, GLenum shaderType);
    private:
	static const unsigned int NUM_SHADERS = 2;
    GLuint m_program;
    GLuint m_shaders[NUM_SHADERS];

	enum
	{
		TRANSFORM_U,

		NUM_UNIFORMS
	};
	GLuint m_uniforms[NUM_UNIFORMS];
};

#endif
