#ifndef MESH_HPP
#define MESH_HPP

class Vertex
{
    public:
    Vertex(const glm::vec3 pos, const glm::vec2 texCoord);

    glm::vec3 pos_;
	glm::vec2 texCoord_;

    protected:
    private:
};

class Mesh
{
    public:
    Mesh(Vertex* vertices, unsigned int numVertices);
    virtual ~Mesh();

    void draw();

    protected:
    private:
    enum
    {
        POSITION_VB,
		TEXCOORD_VB,
        NUM_BUFFERS
    };

    GLuint m_vertexArrayObject;
    GLuint m_vertexArrayBuffers[NUM_BUFFERS];
    unsigned int m_drawCount;
};

#endif
