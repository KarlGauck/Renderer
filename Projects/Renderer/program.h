#include <string>
#include "glm/gtc/matrix_transform.hpp"

class ShaderProgram
{
public:
	ShaderProgram(std::string vertSource, std::string fragSource);
	void use();

	void uniformMatrix4fv(std::string name, glm::mat4 matrix);

private:
	int handle;
	void shaderCompilationDebug(unsigned int shader);
	void programLinkingDebug();
};