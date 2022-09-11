#pragma once
#include "Window.h"
#include "Components.h"
#include "GL_UniformBuffer.h"
#include <memory>

namespace core {

	class	Scene;
	struct	Transform;
	struct	MeshComponent;

};

class OpenGL_Renderer
{
public:
	OpenGL_Renderer() = default;

	void InitRenderer(Window* window);
	void Draw(core::MeshComponent* mesh, core::Transform transform, core::Scene& scene);
	void StartFrame(core::Scene& scene);
private:
	Window* window;
	std::unique_ptr<GL_UniformBuffer<GL_GlobalMatrixObject>> m_glUniforms;
	std::unique_ptr<GL_UniformBuffer<GL_Lights>> m_glLights;
};

