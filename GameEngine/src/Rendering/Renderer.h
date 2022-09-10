#pragma once
#include "OpenGL/OpenGL_Renderer.h"



	class	core::Scene;
	struct	core::Transform;
	struct	core::MeshComponent;


class Renderer
{
public:
	void InitRenderer(Window* window);

	void Draw(core::MeshComponent* drawable, core::Transform transform, core::Scene& scene);
	void StartFrame(core::Scene& scene);

private:
	OpenGL_Renderer openGL_Renderer;

};

