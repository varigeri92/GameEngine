#pragma once
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Log.h"

#include "Rendering/OpenGL/GL_VertexBuffer.h"
#include "Rendering/OpenGL/GL_Texture.h"
#include "Rendering/OpenGL/GL_Shader.h"

#include "Rendering/Camera.h"
#include <string>
#include <memory>
#include <Rendering/Material.h>


typedef glm::vec3 Color;
typedef glm::vec4 Color4;

namespace core {

	struct Entity;

	struct EntityComponent
	{
		EntityComponent(std::string _name) : 
			name{ _name } 
		{};

		std::string name;
	};

	struct Transform
	{
		Transform() :
			position{ 0.0f, 0.0f, 0.0f },
			rotation{ 0.0f, 0.0f, 0.0f },
			scale{ 1.f, 1.f, 1.f }
		{}

		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;

		glm::vec3 Front = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 Right = glm::vec3(1.0f, 0.0f, 0.0f);

		glm::vec3 WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);

		glm::mat4 model{};
		glm::mat4 view{};

		Transform* parent = nullptr;
	};

	struct MeshComponent
	{
		MeshComponent(std::vector<Vertex> vertices, std::vector<uint32_t> indices) : 
			m_vertices{ vertices }, 
			m_indices{ indices }
		{
			m_vertexBuffer->CreateBuffer(vertices, indices);
		}

		MeshComponent(){}
	
		std::shared_ptr<Material> material = nullptr;
		std::shared_ptr<GL_VertexBuffer> m_vertexBuffer;
		std::vector<Vertex> m_vertices;
		std::vector<uint32_t> m_indices;
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

	};

	struct Ambient
	{
		Color ambientColor;
		float intensity;
	};

	struct DirectionalLight
	{
		Color lightColor;
		float lightIntensity;
	};
}