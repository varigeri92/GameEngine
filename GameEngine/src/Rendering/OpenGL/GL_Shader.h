#pragma once
#include <string>
#include <glm/glm.hpp>
#include <string>

class GL_Shader
{
public:
	GL_Shader(const char* vertexPath, const char* fragmentPath);
	GL_Shader() = default;

	void Use();
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;

	void SetMat4(std::string name, glm::mat4& mat);
	unsigned int Get() const { return shaderProgram; };

private:
	unsigned int shaderProgram;
};

