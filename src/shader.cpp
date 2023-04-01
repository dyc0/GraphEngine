#include "shader.hpp"

Shader::Shader(const std::string& fileName)
{
    m_program = glCreateProgram();
    // Vertex shader
    m_shaders[0] = create_shader(load_shader(fileName + ".vs"), GL_VERTEX_SHADER);
    // Fragment shader
    m_shaders[1] = create_shader(load_shader(fileName + ".fs"), GL_FRAGMENT_SHADER);

    for (size_t i = 0; i < NUM_SHADERS; i++)
        glAttachShader(m_program, m_shaders[i]);

    glBindAttribLocation(m_program, 0, "position_");
    glBindAttribLocation(m_program, 0, "texCoord_");

    glLinkProgram(m_program);
    CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Program failed to link: ");

    glValidateProgram(m_program);
    CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Program is invalid: ");

	m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program, "transform");
}

Shader::~Shader()
{
    for (size_t i = 0; i < NUM_SHADERS; i++)
    {
        glDetachShader(m_program, m_shaders[i]);
        glDeleteShader(m_shaders[i]);
    }

    glDeleteProgram(m_program);
}

std::string Shader::load_shader(const std::string& fileName) const
{
    std::ifstream file;
    file.open(fileName.c_str());

    std::string output, line;

    if (file.is_open())
        while (file.good())
        {
            getline(file, line);
            output.append(line + "\n");
        }
    else
        std::cerr << "Unable to load shader from file " << fileName << std::endl;

    return output;
}


void Shader::bind()
{
    glUseProgram(m_program);
}


void Shader::update(const Transform& transform, const Camera& camera)
{
	glm::mat4 model = camera.GetViewProjection() * transform.GetModel();

	glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
}


GLuint Shader::create_shader(const std::string &text, GLenum shaderType)
{
    GLuint shader = glCreateShader(shaderType);

    if (shader == 0)
        std::cerr << "Error: Shader creation failed." << std::endl;

    const GLchar* shaderSourceStrings[1];
    GLint shaderSourceStringLengths[1];
    shaderSourceStrings[0] = text.c_str();
    shaderSourceStringLengths[0] = text.length();

    glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
    glCompileShader(shader);

    CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed: ");

    return shader;
}

void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string &errorMessage)
{
    GLint success = 0;
    GLchar error[1024] = { 0 };

    if (isProgram)
        glGetProgramiv(shader, flag, &success);
    else
        glGetShaderiv(shader, flag, &success);

    if (success == GL_FALSE)
    {
        if (isProgram)
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        else
            glGetShaderInfoLog(shader, sizeof(error), NULL, error);
        std::cerr << errorMessage << ": '" << error << "'" << std::endl;
    }
}
