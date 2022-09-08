#pragma once
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Log.h"

#include "Rendering/OpenGL/GL_VertexBuffer.h"
#include "Rendering/Camera.h"

namespace core {

	struct Entity;

	struct Transform
	{
		Transform() :
			position{ 0.0f, 0.0f, 0.0f },
			rotation{ 0.0f, 0.0f, 0.0f },
			scale{ 1.f, 1.f, 1.f }
		{
			LOG_INFO("Transform ComponentCreated! With default parameters ");
		}

		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;

		glm::vec3 Front = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 Right = glm::vec3(1.0f, 0.0f, 0.0f);

		glm::vec3 WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);

		glm::mat4 model{};
		glm::mat4 view{};

		Entity* entity = nullptr;
	};

	struct MeshComponent
	{
		MeshComponent(std::vector<Vertex> vertices, std::vector<uint32_t> indices) : m_vertices{ vertices }, m_indices{ indices }
		{
			m_vertexBuffer.CreateBuffer(vertices, indices);
		}
	
		GL_VertexBuffer m_vertexBuffer;
		std::vector<Vertex> m_vertices;
		std::vector<uint32_t> m_indices;

		Entity* entity = nullptr;
	};

	struct CameraComponent
	{
		CameraComponent(float aspect, float fov, float near, float far) :
			m_aspect{ aspect }, 
			m_fov{ fov }, 
			m_near{ near }, 
			m_far{far}
		{
			Camera camera(aspect, fov, near, far);
			proj = camera.GetProjection();
			view = camera.GetView();
		};

		float m_aspect, m_fov, m_near, m_far;

		glm::mat4 proj{};
		glm::mat4 view{};

		//CameraMovement
		float v_axis = 0, h_axis = 0, u_axis = 0;
		float MouseSensitivity = 1500.f;
		float speed = 5.f;

		Entity* entity = nullptr;
	};
}