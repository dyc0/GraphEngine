#include "mesh.hpp"

Vertex::Vertex(const glm::vec3 pos, const glm::vec2 texCoord): pos_(pos), texCoord_(texCoord) { }

Mesh::Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices):
    m_drawCount(numIndices)
{
    glGenVertexArrays(1, &m_vertexArrayObject);
    glBindVertexArray(m_vertexArrayObject);

	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> texCoords;

	positions.reserve(numVertices);
	texCoords.reserve(numVertices);

	for (size_t i = 0; i<numVertices; i++)
	{
		positions.push_back(vertices[i].pos_);
		texCoords.push_back(vertices[i].texCoord_);
	}

    glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(texCoords[0]), &texCoords[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices* sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);
	
	glBindVertexArray(0);
}


Mesh::Mesh(const std::string& fileName)
{
	IndexedModel model = OBJModel(fileName).ToIndexedModel();


}


void Mesh::InitMesh(const IndexedModel& model)
{
    glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(texCoords[0]), &texCoords[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices* sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);
	
	glBindVertexArray(0);
}


Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Mesh::draw()
{
    glBindVertexArray(m_vertexArrayObject);
	
	glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, 0);
    //glDrawArrays(GL_TRIANGLES, 0, m_drawCount);

    glBindVertexArray(0);
}
