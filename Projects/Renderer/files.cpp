#include <iostream>
#include <fstream>

#include "files.h"

std::string FileHandler::readFile(std::string path)
{
	std::ifstream file(path);
	std::string content = "";
	std::string temp = "";

	while (getline(file, temp))
		content += temp + "\n";

	return content;
}

const char* FileHandler::readFileCStyle(std::string path)
{
	return readFile(path).c_str();
}
