#pragma once
#include "Component.h"
#include "Rendering/OpenGL/GL_VertexBuffer.h"
namespace core 
{
	struct Entity;
	struct Transform;

	class Drawable : public Component
	{
	public:
		Drawable() = default;
		Drawable(const Drawable& other) = default;
		Drawable(Drawable&&) = default;

		uint32_t shaderID;
		uint32_t batchID;
		Transform* transformComponent;
		GL_VertexBuffer vertexBuffer;

	private:
		friend class Engine;
	};

}
