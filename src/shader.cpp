#include "shader.hpp"

void Shader::createVertexShader(const std::string &vertSrc)
{
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	createShader(vertexShader, vertSrc);
}

void Shader::createFragmentShader(const std::string &fragSrc)
{
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	createShader(fragmentShader, fragSrc);	
}

void Shader::generateShaderProgram()
{
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);	
	glBindFragDataLocation(shaderProgram, 0, "outColor");
	glLinkProgram(shaderProgram);
}

void Shader::setPerspective(const glm::mat4 perspective)
{
	proj = perspective;
}

void Shader::setCamera(const glm::mat4 camera)
{
	view = camera;
}

void Shader::bindGlobalTransforms() const
{
	glUseProgram(shaderProgram);

	GLuint uniView = glGetUniformLocation(shaderProgram, "view");
	glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));

	GLuint uniProj = glGetUniformLocation(shaderProgram, "proj");
	glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));
}

GLuint Shader::getProgram() const
{
	return shaderProgram;
}

bool Shader::checkShaderError(GLuint shader) const
{
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (!status)
	{
		char buffer[512];
		glGetShaderInfoLog(shader, 512, NULL, buffer);
		for(size_t i = 0; buffer[i] != '\0'; i++)
		{
			if (i >= 512) break;
			std::cout << buffer[i];
    	}
		std::cerr << std::endl;
	}
	return status;
}

std::string Shader::load_shader(const std::string& fileName) const
{
	std::ifstream file;
	file.open(fileName);

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


void Shader::createShader(GLuint& shader, const std::string& source)
{
	std::string shaderStr = load_shader(source);
	const char* shaderChar = shaderStr.c_str();
	glShaderSource(shader, 1, &shaderChar, NULL);
	glCompileShader(shader);
	if (!checkShaderError(shader)) return;
}
