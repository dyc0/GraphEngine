#ifndef ERRORS_HPP
#define ERRORS_HPP

#include <exception>
#include <iostream>
#include <string>

class FileLoadingExceptions: public std::exception
{
	public:
	enum ERR_TYPE {FILE_NOT_OPEN, OTHER};

	FileLoadingExceptions(unsigned int which_type): which_(which_type) { };
	FileLoadingExceptions(unsigned int which_type, const std::string& fileName):
	   	which_(which_type), fileName_(fileName) { };

	const char * what() const noexcept override
	{
		std::string error;
		switch (which_) {
		case FILE_NOT_OPEN:
			error = "File " + fileName_ + " did not open correctly.";
			break;
		default:
			error = "Unknown file error.";	
		}
		const char * error_return = error.c_str();
		return error_return;
	}

	private:
	unsigned int which_;
	std::string fileName_;
};

#endif
