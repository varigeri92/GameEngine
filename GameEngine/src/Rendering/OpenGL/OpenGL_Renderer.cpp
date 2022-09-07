#include "OpenGL_Renderer.h"
#include "GL/glew.h"
#include <SDL_opengl.h>
#include "Log.h"
#include "GL_Texture.h"
#include "GL_Shader.h"
#include "GL_VertexBuffer.h"
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp" 
#include "glm/gtx/quaternion.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Components.h"
#include "Drawable.h"
#include "Entity.h"
#include "Scene.h"
#include "UI/UI.h"
#include "UI/inspector.h"

#include "AssetPath.h"



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

std::vector<GL_VertexBuffer> vertexBuffers;

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

	GL_VertexBuffer vertexBuffer;
	vertexBuffer.CreateBuffer(vertices, indices);
	vertexBuffers.push_back(vertexBuffer);


	shader = GL_Shader(ASSETS_PATH"Shaders\\default.vert",
		ASSETS_PATH"Shaders\\default.frag");

	texture = { ASSETS_PATH"Textures\\Suzanne.jpg" };
	


	//uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glPolygonMode(GL_FRONT, GL_FILL);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	//glViewport(0, 0, window->width,window->width);
}

void OpenGL_Renderer::Draw(core::MeshComponent* mesh, Transform transform, Scene& scene)
{
	glViewport(0, 0, window->width, window->height);

	float aspect = (float)window->width / window->height;

	shader.Use();
	glm::mat4 projection = glm::mat4(1.0f);
	projection = scene.GetActiveCamera()->proj;
	shader.SetMat4("projection", projection);

	texture.Bind();
	//vertexBuffers[0].Bind();
	mesh->m_vertexBuffer.Bind();

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 translate = glm::mat4(1.0f);
	glm::mat4 rotation = glm::mat4(1.0f);
	glm::mat4 scale = glm::mat4(1.0f);

	glm::mat4 modelMatrix(1.f);
	
	translate = glm::translate(glm::mat4(1), mesh->entity->GetComponet<Transform>().position);


	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1), mesh->entity->GetComponet<Transform>().scale);

	glm::vec3 EulerAngles(
		degreesToRadians(mesh->entity->GetComponet<Transform>().rotation.x),
		degreesToRadians(mesh->entity->GetComponet<Transform>().rotation.y),
		degreesToRadians(mesh->entity->GetComponet<Transform>().rotation.z)
	);

	glm::quat Quaternion = glm::quat(-EulerAngles);
	glm::mat4 RotationMatrix = glm::toMat4(Quaternion);

	model = model * translate * RotationMatrix * scaleMatrix;

	view = glm::lookAt(
		scene.GetActiveCamera()->entity->GetComponet<Transform>().position,
		scene.GetActiveCamera()->entity->GetComponet<Transform>().position +
		scene.GetActiveCamera()->entity->GetComponet<Transform>().Front,
		scene.GetActiveCamera()->entity->GetComponet<Transform>().Up
	);


	unsigned int modelLoc = glGetUniformLocation(shader.Get(), "model");
	unsigned int viewLoc = glGetUniformLocation(shader.Get(), "view");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);

	glDrawElements(GL_TRIANGLES, mesh->m_vertexBuffer.GetIndexCount(), GL_UNSIGNED_INT, 0);
	//glDrawElements(GL_TRIANGLES, vertexBuffers[0].GetIndexCount(), GL_UNSIGNED_INT, 0);
}

void OpenGL_Renderer::StartFrame()
{
	SDL_GL_SwapWindow(window->GetWindow());
	glClearColor(0.5f, 0.5f, 0.5f, 1.f);
	glClearDepth(1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
