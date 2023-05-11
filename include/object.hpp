#ifndef OBJLOADER_HPP
#define OBJLOADER_HPP

#include "common.hpp"
#include "errors.hpp"

#include <glm/glm.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include<vector>

class ObjectHandler
{
	public:
		ObjectHandler() = default;
		void loadOBJ(const std::string& path,
				std::vector<glm::vec3> & outVertices,
				std::vector<glm::vec2> & outUvs,
				std::vector<glm::vec3> & outNormals
				);

	private:
	void tokenize(const std::string& line,  std::vector<std::string>& tokens, char delimiter = ' ') const;
	void parseLine(const std::string& line,
				   std::vector<glm::vec3>& vertices, 
				   std::vector<glm::vec3>& normals, 
				   std::vector<glm::vec2>& uvs, 
				   std::vector<unsigned int>& vIndices, 
				   std::vector<unsigned int>& uIndices, 
				   std::vector<unsigned int>& nIndices) const;

};

#endif
