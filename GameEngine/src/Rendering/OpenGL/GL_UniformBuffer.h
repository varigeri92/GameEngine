#pragma once

#include "GL/glew.h"
#include "glm/glm.hpp"
#include "Components.h"
#include <vector>
//#include "GL_Shader.h"

struct GL_GlobalMatrixObject
{
	glm::mat4 view;
	glm::mat4 proj;
};

struct GL_Lights
{
	glm::vec4 direction{ 0.f,-1.f,0.f,0.f }; // W not used
	glm::vec4 Color {1.f, 1.f, 1.f, 1.f };	// W = intensity
};

template<class T>
class GL_UniformBuffer
{
public:


	GL_UniformBuffer<T>(size_t bufferSize)
	{
		glGenBuffers(1, &m_glBuffer);
		glBindBuffer(GL_UNIFORM_BUFFER, m_glBuffer);
		glBufferData(GL_UNIFORM_BUFFER, bufferSize, nullptr, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);

	};
	template<typename T>
	GL_UniformBuffer<T> UpdateUBO(T& ubo, uint32_t binding_index)
	{
		glBindBuffer(GL_UNIFORM_BUFFER, m_glBuffer);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(ubo), &ubo);
		glBindBufferRange(GL_UNIFORM_BUFFER, binding_index, m_glBuffer, 0, sizeof(ubo));

		return *this;
	};
	void Bind() {
		glBindBuffer(GL_UNIFORM_BUFFER, m_glBuffer);
	};
	void Unbind()
	{
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	};
	unsigned int m_glBuffer = 0;
	uint32_t m_bindingIndex = 0;
private:
};

