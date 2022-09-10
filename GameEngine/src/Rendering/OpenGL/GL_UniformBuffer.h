#pragma once

#include "GL/glew.h"
#include "glm/glm.hpp"

struct GL_UBO
{
	glm::mat4 view;
	glm::mat4 proj;
};

class GL_UniformBuffer
{
public:
	GL_UniformBuffer(glm::mat4 view, glm::mat4 proj);
	GL_UniformBuffer();
	
	GL_UniformBuffer UpdateUBO(glm::mat4 view, glm::mat4 proj);
	void Bind();
	void Unbind();
	unsigned int m_glBuffer = 0;
	GL_UBO m_ubo;
private:
};

