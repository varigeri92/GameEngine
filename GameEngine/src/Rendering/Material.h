#pragma once
#include <memory>
#include "glm/glm.hpp"

class GL_Shader;
class GL_Texture;

struct  Material
{
	Material(std::shared_ptr<GL_Shader> _shader) :
		shader		{ _shader }
	{}


	std::shared_ptr<GL_Shader> shader;
	std::shared_ptr<GL_Texture> mainTexture;

	glm::vec4 Color = { 1.f, 1.f ,1.f, 1.f };
};