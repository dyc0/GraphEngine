#ifndef TEXTURE_HPP
#define TEXTURE_HPP

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
