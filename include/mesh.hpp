#ifndef MESH_HPP
#define MESH_HPP

#include <string>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "obj_loader.hpp"


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
    Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
	Mesh(const std::string& fileName);
	
    virtual ~Mesh();

    void draw();

    protected:
    private:
	void InitMesh(const IndexedModel& model);

	enum
    {
        POSITION_VB,
		TEXCOORD_VB,

		INDEX_VB,

        NUM_BUFFERS
    };

    GLuint m_vertexArrayObject;
    GLuint m_vertexArrayBuffers[NUM_BUFFERS];
    unsigned int m_drawCount;
};

#endif
