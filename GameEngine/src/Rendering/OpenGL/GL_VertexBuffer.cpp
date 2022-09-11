#include "GL_VertexBuffer.h"
#include <GL/glew.h>
#include "Log.h"

void GL_VertexBuffer::CreateBuffer(std::vector<core::Vertex> &vertices, std::vector<uint32_t> &indices)
{
	m_indexCount = indices.size();
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(core::Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * indices.size(), indices.data(), GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(core::Vertex), (void*)offsetof(core::Vertex, position));
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(core::Vertex), (void*)offsetof(core::Vertex, color));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(core::Vertex), (void*)offsetof(core::Vertex, UV));
	glEnableVertexAttribArray(2);
	// normal vector attribute
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(core::Vertex), (void*)offsetof(core::Vertex, normal));
	glEnableVertexAttribArray(3);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void GL_VertexBuffer::Bind()
{
	glBindVertexArray(VAO);
}

void GL_VertexBuffer::DestoyBuffer()
{
}
