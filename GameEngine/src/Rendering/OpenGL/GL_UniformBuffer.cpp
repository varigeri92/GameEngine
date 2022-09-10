#include "GL_UniformBuffer.h"


GL_UniformBuffer::GL_UniformBuffer(glm::mat4 view, glm::mat4 proj) : m_ubo{ view, proj }, m_glBuffer { 0 }
{
	glGenBuffers(1, &m_glBuffer);
	glBindBuffer(GL_UNIFORM_BUFFER, m_glBuffer);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(m_ubo), nullptr, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

GL_UniformBuffer::GL_UniformBuffer()
{
	glm::mat4 view = glm::mat4(1.f);
	glm::mat4 proj = glm::mat4(1.f);
	m_ubo = { view, proj };

}

GL_UniformBuffer GL_UniformBuffer::UpdateUBO(glm::mat4 view, glm::mat4 proj)
{
	m_ubo.view = view;
	m_ubo.proj = proj;

	glBindBuffer(GL_UNIFORM_BUFFER, m_glBuffer);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(m_ubo), &m_ubo);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	// define the range of the buffer that links to a uniform binding point
	glBindBufferRange(GL_UNIFORM_BUFFER, 0, m_glBuffer, 0, sizeof(m_ubo));
	return *this;
}

void GL_UniformBuffer::Bind()
{
	glBindBuffer(GL_UNIFORM_BUFFER, m_glBuffer);
}

void GL_UniformBuffer::Unbind()
{
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
