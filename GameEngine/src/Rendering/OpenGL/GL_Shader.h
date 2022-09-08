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
	uint32_t GetUniformBlock(const char* name);
	uint32_t GetUniformBlock() const { return m_uniformBlock; };
	uint32_t Get() const { return shaderProgram; };

private:
	uint32_t shaderProgram;
	uint32_t m_uniformBlock;
};

