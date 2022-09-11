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

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

uint32_t GL_VertexBuffer::Push(std::vector<core::Vertex>& vertices, std::vector<uint32_t>& indices)
{
	if (m_AvailableIndices < indices.size() && m_AvailableVerices < vertices.size())
		return 0; // Return Invalid batch ID
	
	for (rsize_t i = 0; i< indices.size(); i++ )
	{
		indices[i] += m_vertexCount;
	}

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(core::Vertex) * m_vertexCount, sizeof(core::Vertex) * vertices.size(), vertices.data());

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * m_indexCount, sizeof(uint32_t) * indices.size(), indices.data());
	
	glBindVertexArray(0);

	m_vertexCount += vertices.size();
	m_indexCount += indices.size();

	m_AvailableIndices -= indices.size();
	m_AvailableVerices -= vertices.size();

	return batchID;
}
void GL_VertexBuffer::CreateBatch()
{
	uint32_t vertexCount = 100000000;
	uint32_t indexCout = vertexCount * 5;
	batchID = 1;
	m_AvailableVerices = vertexCount;
	m_AvailableIndices = indexCout;

	isBatch = true;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(core::Vertex) * vertexCount, nullptr, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * indexCout, nullptr, GL_DYNAMIC_DRAW);

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
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
}

void GL_VertexBuffer::UnBind()
{
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
