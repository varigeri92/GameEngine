#include "OpenGL_Renderer.h"
#include "GL/glew.h"
#include <SDL_opengl.h>
#include "Log.h"
#include "GL_Texture.h"
#include "GL_Shader.h"
#include "GL_VertexBuffer.h"
#include "GL_UniformBuffer.h"
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp" 
#include "glm/gtx/quaternion.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Components.h"
#include "Entity.h"
#include "Scene.h"
#include "UI/UI.h"
#include "UI/inspector.h"

#include "AssetPath.h"

#include "CameraSystem.h"




using namespace core;
#define degreesToRadians(x) x*(3.141592f/180.0f)


std::vector<Vertex> vertices = {
	// positions          // colors           // texture coords
	{{ 0.5f,  0.5f, 0.0f },   { 1.0f, 0.0f, 0.0f },   { 1.0f, 1.0f } },
	{{ 0.5f, -0.5f, 0.0f },   { 0.0f, 1.0f, 0.0f },   { 1.0f, 0.0f } },
	{{-0.5f, -0.5f, 0.0f },   { 0.0f, 0.0f, 1.0f },   { 0.0f, 0.0f } },
	{{-0.5f,  0.5f, 0.0f },   { 1.0f, 1.0f, 0.0f },   { 0.0f, 1.0f } }
};
std::vector<uint32_t> indices
{  
	0, 1, 2,  
	2, 3, 0   
};



GL_Shader shader;
//GL_VertexBuffer vertexBuffer;
GL_Texture texture;

//std::vector<GL_VertexBuffer> vertexBuffers;
GL_GlobalMatrixObject glMatrices{};
GL_Lights glLights {};


void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
	if(type == GL_DEBUG_TYPE_ERROR)
		LOG_ERROR("GL: [" << type << "] " << message);
	if (type == GL_DEBUG_TYPE_ERROR_ARB)
		LOG_ERROR("GL: [" << type << "] " << message);
	
}

void OpenGL_Renderer::InitRenderer(Window* window)
{
	this->window = window;
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		LOG_ERROR("GLEW:: cant init glew! " << glewGetErrorString(err));
	}
	SDL_GL_MakeCurrent(window->GetWindow(), window->GetContext());

	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glEnable(GL_DEPTH_TEST);

	glDebugMessageCallback(MessageCallback, 0);
	LOG_INFO("GLEW:: Using GLEW: " << glewGetString(GLEW_VERSION));



	shader = GL_Shader(ASSETS_PATH"Shaders\\default.vert",
		ASSETS_PATH"Shaders\\default.frag");
	/*
	glGenBuffers(1, &glUniforms.m_glBuffer);
	glBindBuffer(GL_UNIFORM_BUFFER, glUniforms.m_glBuffer);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(glUniforms.m_ubo), nullptr, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	*/

	//uint32_t bindingBlockID = shader.GetUniformBlock("ViewProj");
	//LOG_INFO("Block Binding: 'ViewProj': " << bindingBlockID);
	//bindingBlockID = shader.GetUniformBlock("Lights");
	//LOG_INFO("Block Binding: 'Lights': " << bindingBlockID);

	texture = { ASSETS_PATH"Textures\\Suzanne.jpg" };
	{
		//GL_UniformBuffer<GL_GlobalMatrixObject> glUniforms{sizeof(glMatrices)};
		m_glUniforms = std::make_unique<GL_UniformBuffer<GL_GlobalMatrixObject>>(sizeof(glMatrices));
		m_glLights = std::make_unique<GL_UniformBuffer<GL_Lights>>(sizeof(glLights));
	}
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

}

void OpenGL_Renderer::Draw(core::MeshComponent* mesh, Transform transform, Scene& scene)
{
	shader.Use();
	texture.Bind();
	mesh->m_vertexBuffer.Bind();

	// Update Matrices:
	glm::mat4 translate = glm::translate(glm::mat4(1), transform.position);
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1), transform.scale);
	glm::vec3 EulerAngles(
		degreesToRadians(transform.rotation.x),
		degreesToRadians(transform.rotation.y),
		degreesToRadians(transform.rotation.z)
	);
	glm::quat Quaternion = glm::quat(-EulerAngles);
	glm::mat4 RotationMatrix = glm::toMat4(Quaternion);
	glm::mat4 model = glm::mat4(1.0f) * translate * RotationMatrix * scaleMatrix;

	unsigned int modelLoc = glGetUniformLocation(shader.Get(), "model");
	unsigned int viewLoc = glGetUniformLocation(shader.Get(), "view");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	//----------------________________---------------------------//



	glDrawElements(GL_TRIANGLES, mesh->m_vertexBuffer.GetIndexCount(), GL_UNSIGNED_INT, 0);
}

void OpenGL_Renderer::StartFrame(core::Scene& scene)
{
	SDL_GL_SwapWindow(window->GetWindow());
	glClearColor(0.5f, 0.5f, 0.5f, 1.f);
	glClearDepth(1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0, 0, window->width, window->height);
	float aspect = (float)window->width / window->height;
	UpdateCameraProj_Aspect(*scene.GetActiveCamera(), aspect);
	glMatrices.proj = scene.GetActiveCamera()->proj;
	glMatrices.view = scene.GetActiveCamera()->view;


	m_glUniforms->UpdateUBO(glMatrices, 0);


	glm::vec3 front;
	front.x = cos(glm::radians(scene.LightTransform->rotation.y)) * cos(glm::radians(scene.LightTransform->rotation.x));
	front.y = sin(glm::radians(scene.LightTransform->rotation.x));
	front.z = sin(glm::radians(scene.LightTransform->rotation.y)) * cos(glm::radians(scene.LightTransform->rotation.x));
	scene.LightTransform->Front = glm::normalize(front);
	scene.LightTransform->Right = glm::normalize(glm::cross(scene.LightTransform->Front, scene.LightTransform->WorldUp));
	scene.LightTransform->Up = glm::normalize(glm::cross(scene.LightTransform->Right, scene.LightTransform->Front));

	glLights.direction = { scene.LightTransform->Front.x,scene.LightTransform->Front.y, scene.LightTransform->Front.z, 0};
	glLights.Color = { scene.Light->lightColor.r, scene.Light->lightColor.g, scene.Light->lightColor.b, scene.Light->lightIntensity };
	m_glLights->UpdateUBO(glLights, 1);
	
}
