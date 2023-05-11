#include "object.hpp"
#include "common.hpp"
#include <cstddef>
#include <cstdio>
#include <glm/fwd.hpp>
#include <sstream>
#include <string>
#include <vector>

void ObjectHandler::loadOBJ(const std::string& path,
							std::vector<glm::vec3> & outVertices,
							std::vector<glm::vec2> & outUvs,
							std::vector<glm::vec3> & outNormals
							)
{
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> tmpVertices, tmpNormals;
	std::vector<glm::vec2> tmpUvs;
	
	std::vector<std::string> lines = *parse_file(path);
	

	for (auto line: lines)
		parseLine(line, tmpVertices, tmpNormals, tmpUvs, vertexIndices, uvIndices, normalIndices);

	for (size_t i = 0; i<vertexIndices.size(); i++)
	{
		outVertices.push_back(tmpVertices[vertexIndices[i] - 1]);
		outUvs.push_back(tmpUvs[uvIndices[i] - 1]);
		outNormals.push_back(tmpNormals[normalIndices[i] - 1]);
	}
}

void ObjectHandler::tokenize(const std::string& line,  std::vector<std::string>& tokens, char delimiter)const
{
	std::stringstream ss(line);	

	std::string token;
	while (getline(ss, token, delimiter))
		tokens.push_back(token);
}


void ObjectHandler::parseLine(
		const std::string& line,
		std::vector<glm::vec3>& vertices,
		std::vector<glm::vec3>& normals,
		std::vector<glm::vec2>& uvs,
		std::vector<unsigned int>& vIndices,
		std::vector<unsigned int>& uIndices,
		std::vector<unsigned int>& nIndices) const
{
   	std::vector<std::string> tokens, indices;	
	
	tokenize(line, tokens); 
	switch (line[0]) {
	case '#': break;
	case 'v':
		switch(line[1])
		{
		case ' ':
		vertices.push_back(
			glm::vec3(std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3]))
			);
		break;
		case 't':
		uvs.push_back(
				glm::vec2(std::stof(tokens[1]), std::stof(tokens[2]))
				);
		case 'n':
		normals.push_back(
			glm::vec3(std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3]))
			);
		}
		break;
	case 'f':
		for (int i=1; i<4; i++)
		{
			tokenize(tokens[i], indices, '/');
			vIndices.push_back(std::stoi(indices[0]));
			uIndices.push_back(std::stoi(indices[1]));
			nIndices.push_back(std::stoi(indices[2]));
			indices.clear();
		}
		break;
	}
	tokens.clear();
}
