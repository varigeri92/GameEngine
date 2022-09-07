#pragma once
#include <vector>
#include "glm/glm.hpp"

namespace core 
{
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 color;
		glm::vec2 UV;
	};
}


class GL_VertexBuffer
{
public:
	void CreateBuffer(std::vector<core::Vertex> &vertices, std::vector<uint32_t> &indices);
	void Bind();
	void DestoyBuffer();

	bool IsBound() const { return m_isbound; };
	uint32_t GetIndexCount() const { return m_indexCount; };
private:
	bool m_isbound;
	uint32_t m_indexCount;

	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;

};

