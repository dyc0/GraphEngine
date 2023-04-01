#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <iostream>
#include <string>

#include <GL/glew.h>

class Texture
{
	public:
	Texture(const std::string& fileName);
	virtual ~Texture();

	void Bind(unsigned int unit);

	protected:
	private:
	GLuint m_texture;
};

#endif
