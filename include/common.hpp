#ifndef COMMON_HPP
#define COMMON_HPP

#include <fstream>
#include <string>
#include <vector>

#include "errors.hpp"

std::vector<std::string>* parse_file(const std::string& path);

#endif
