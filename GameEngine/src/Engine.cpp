//#define BUILD_DLL
//#include "GL/glew.h"
#include "Rendering/Renderer.h"
#include "Window.h"
#include <iostream>
#include "Engine.h"
#include "Log.h"
#include "input.h"
#include "EngineTime.h"
#include "Scene.h"
#include "Rendering/Camera.h"
#include "UI/UI.h"
#include "ImGui/imgui.h"


#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

#include "Entity.h"
#include "AssetPath.h"
#include "Rendering/Material.h"


#include "Rendering/OpenGL/GL_VertexBuffer.h"
#include "Rendering/OpenGL/GL_Shader.h"
#include "Rendering/OpenGL/GL_Texture.h"


using namespace core;


Window* window;
Renderer* renderer;
Engine::Engine(int _width, int _height) : width{ _width }, height{ _height }{}

Scene scene;

void Engine::LogMessage(const char* msg)
{
	LOG_INFO(msg);
}

int Engine::InitEngine() {

	int err = 0;
	window = new Window(width, height);

	err = window->InitWindow();
	err = window->CreateContext();
	Input::window = window;
	renderer = new Renderer();
	renderer->InitRenderer(window);

	LOG_INFO("Engine Ready!");
	return err;
}

_API int Engine::Run()
{
	core::ui::UI ui;
	ui.InitGUI(window);
	scene.CreateScene(renderer, ui);

	//test:
	Assimp::Importer importer;

	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;

	const aiScene* aiScene = importer.ReadFile(ASSETS_PATH "Models\\Suzann.glb", aiProcess_JoinIdenticalVertices);
	if (aiScene)
	{
		for (size_t i = 0; i < aiScene->mNumMeshes; i++)
		{
			for (size_t v = 0; v < aiScene->mMeshes[i]->mNumVertices; v++)
			{
				core::Vertex vertex;
				vertex.position = { aiScene->mMeshes[i]->mVertices[v].x, aiScene->mMeshes[i]->mVertices[v].y, aiScene->mMeshes[i]->mVertices[v].z };
				if (aiScene->mMeshes[i]->HasVertexColors(0))
					vertex.color = { aiScene->mMeshes[i]->mColors[0][v].r, aiScene->mMeshes[i]->mColors[0][v].g, aiScene->mMeshes[i]->mColors[0][v].b };
				else
					vertex.color = { 1.f, 1.f, 1.f };
				vertex.UV = { aiScene->mMeshes[i]->mTextureCoords[0][v].x, aiScene->mMeshes[i]->mTextureCoords[0][v].y };
				vertex.normal = { aiScene->mMeshes[i]->mNormals[v].x, aiScene->mMeshes[i]->mNormals[v].y, aiScene->mMeshes[i]->mNormals[v].z };
				vertices.push_back(vertex);
			}
			for (size_t f = 0; f < aiScene->mMeshes[i]->mNumFaces; f++)
			{

				for (size_t ind = 0; ind < aiScene->mMeshes[i]->mFaces[f].mNumIndices; ind++)
				{
					indices.push_back(static_cast<uint32_t>(aiScene->mMeshes[i]->mFaces[f].mIndices[ind]));
				}
			}
		}
	}
	else
	{
		LOG_ERROR(importer.GetErrorString());
	}
	LOG_INFO("Suzan has: " << vertices.size() << " vertices");
	LOG_INFO("Suzan has: " << indices.size() << " indices");
	LOG_INFO("Suzan has: " << indices.size() / vertices.size() << " times more indes than vertex");


	auto shader = std::make_shared<GL_Shader>(ASSETS_PATH"Shaders\\default.vert", ASSETS_PATH"Shaders\\default.frag");
	auto texture = std::make_shared<GL_Texture>(ASSETS_PATH"Textures\\White.jpg");
	auto texture_2 = std::make_shared<GL_Texture>(ASSETS_PATH"Textures\\Suzann.jpg");

	auto suzannMaterial = std::make_shared<Material>(shader);
	auto suzannMaterial_2 = std::make_shared<Material>(shader);

	size_t width = 1;
	size_t height = 1;
	size_t depth = 1;

	float distance = 3.5f;

	{

		uint32_t mat = 0;
		suzannMaterial->mainTexture = texture;
		suzannMaterial_2->mainTexture = texture_2;
		Entity ent1 = scene.CreateEntity("Suzann_inBatch");
		MeshComponent& mc1 = ent1.AddComponet<MeshComponent>();
		mc1.m_vertexBuffer = std::make_shared<GL_VertexBuffer>();
		mc1.m_vertexBuffer->CreateBatch();
		mc1.material = suzannMaterial_2;
		uint32_t bid = 0;

		auto _vertices = std::vector<Vertex>();

		glm::vec3 offset = { 0,0,0 };
		for (size_t w = 0; w < width; w++)
		{
			for (size_t h = 0; h < height; h++)
			{
				for (size_t d = 0; d < depth; d++)
				{

					offset = { (float)w, (float)h, (float)d };
					_vertices.clear();
					for (size_t i = 0; i < vertices.size(); i++)
					{
						Vertex vertex{
							{vertices[i].position + (offset * distance)},
							{vertices[i].color},
							{vertices[i].UV},
							{vertices[i].normal},
						};
						_vertices.push_back(vertex);

					}
					LOG_INFO("OFFSET: " << offset.x << " / " << offset.y << " / " << offset.z);
					bid = mc1.m_vertexBuffer->Push(_vertices, indices);
				}
			}
		}

		Entity ambientity = scene.CreateEntity("Ambient");
		auto ambientComponent = ambientity.AddComponet<Ambient>();
		ambientComponent.ambientColor = { 1.f, 1.f, 1.f };
		ambientComponent.intensity = 1;
		scene.ambient = &ambientComponent;

		Entity empty = scene.CreateEntity("Directional Light");		
		scene.Light = &empty.AddComponet<DirectionalLight>();
		scene.Light->lightColor = { 1.f, 1.f, 1.f };
		scene.Light->lightIntensity = 1.f;
		scene.LightTransform = &empty.GetComponent<Transform>();

		Entity cameraEntity = scene.CreateEntity("Camera");
		CameraComponent cameraComponent 
			= cameraEntity.AddComponet<CameraComponent>((float)window->width / (float)window->height, 60.f, 0.1f, 1000.f); 
		scene.cameraEntity = cameraEntity.m_entity;
		scene.activeCamera = &cameraComponent;
	}


	scene.Awake();
	scene.Start();
	SDL_Event e;
	bool bQuit = false;

	//main loop
	while (!Input::frameInput.isquit)
	{
		Time::StartFrameTimer();
		
		Input::ProcessInput(e);

		scene.Update();
		scene.Render();
		Time::EndFrameTimer();
	}

	ui.CleanUpGui();

	delete(renderer);
	delete(window);
	
	LOG_INFO("Engine closed");
	
	return 0;
}
