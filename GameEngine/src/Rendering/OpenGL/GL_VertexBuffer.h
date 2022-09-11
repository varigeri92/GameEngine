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
		glm::vec3 normal;
	};
}


class GL_VertexBuffer
{
public:
	void CreateBuffer(std::vector<core::Vertex> &vertices, std::vector<uint32_t> &indices);
	void CreateBatch();

	uint32_t Push(std::vector<core::Vertex>& vertices, std::vector<uint32_t>& indices);
	void Bind();
	void UnBind();
	void DestoyBuffer();

	bool IsBound() const { return m_isbound; };
	uint32_t GetIndexCount() const { return m_indexCount; };
private:
	bool m_isbound;

	bool isBatch = false;

	uint32_t batchID = 0;

	uint32_t m_indexCount = 0;
	uint32_t m_vertexCount = 0;

	uint32_t m_vertexIndex = 0;
	uint32_t m_indexIndex = 0;

	uint32_t m_AvailableVerices = 0;
	uint32_t m_AvailableIndices = 0;



	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;

};

