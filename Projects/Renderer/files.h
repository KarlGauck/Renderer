#include <string>

class FileHandler
{
public:
	static std::string readFile(std::string path);
	static const char* readFileCStyle(std::string path);
};