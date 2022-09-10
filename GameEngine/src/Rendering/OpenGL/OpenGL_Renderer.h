#pragma once
#include "Window.h"
#include "Components.h"

namespace core {

	class	Scene;
	struct	Transform;
	struct	MeshComponent;

};

class OpenGL_Renderer
{
public:
	void InitRenderer(Window* window);
	void Draw(core::MeshComponent* mesh, core::Transform transform, core::Scene& scene);
	void StartFrame(core::Scene& scene);
private:
	Window* window;
};

