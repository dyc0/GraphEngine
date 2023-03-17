#ifndef MESH_HPP
#define MESH_HPP

#include "externals.hpp"

class Vertex
{
    public:
    Vertex(const glm::vec3 pos);

    protected:
    private:
    glm::vec3 pos_;
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
        NUM_BUFFERS
    };

    GLuint m_vertexArrayObject;
    GLuint m_vertexArrayBuffers[NUM_BUFFERS];
    unsigned int m_drawCount;
};

#endif
