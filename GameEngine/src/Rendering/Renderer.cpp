#include "Renderer.h"
#include "OpenGL/OpenGL_Renderer.h"
#include "Components.h"

using namespace core;

void Renderer::InitRenderer(Window* window)
{
	openGL_Renderer = OpenGL_Renderer();
	openGL_Renderer.InitRenderer(window);
}

void Renderer::Draw(MeshComponent* mesh, core::Transform transform, core::Scene& scene)
{
	openGL_Renderer.Draw(mesh, transform, scene );
}

void Renderer::StartFrame()
{
	openGL_Renderer.StartFrame();
}
