#include "common.hpp"

std::vector<std::string>* parse_file(const std::string& path)
{
	std::ifstream file;
	file.open(path);
	
	if (!file.is_open()) throw FileLoadingExceptions(FileLoadingExceptions::ERR_TYPE::FILE_NOT_OPEN, path);
	
	std::string line;
	std::vector<std::string>* lines = new std::vector<std::string>();
	while (file.good())
	{
		getline(file, line);
		(*lines).push_back(line);
	}

	return lines;
}
