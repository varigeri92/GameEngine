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
	void StartFrame();

private:
	OpenGL_Renderer openGL_Renderer;

};

