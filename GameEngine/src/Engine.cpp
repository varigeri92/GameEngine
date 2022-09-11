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

#include "Rendering/OpenGL/GL_VertexBuffer.h"
#include "Entity.h"

#include "AssetPath.h"

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
	
	const aiScene* aiScene = importer.ReadFile(ASSETS_PATH "Models\\untitled.glb", aiProcess_JoinIdenticalVertices);
	if (aiScene) 
	{
		for (size_t i = 0; i < aiScene->mNumMeshes; i++)
		{
			for (size_t v = 0; v < aiScene->mMeshes[i]->mNumVertices; v++)
			{
				core::Vertex vertex;
				vertex.position = { aiScene->mMeshes[i]->mVertices[v].x, aiScene->mMeshes[i]->mVertices[v].y, aiScene->mMeshes[i]->mVertices[v].z };
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
	
	{
		Entity ent = scene.CreateEntity("entity");
		ent.AddComponet<MeshComponent>(vertices, indices);


		Entity empty = scene.CreateEntity("Directional Light");		
		scene.Light = &empty.AddComponet<DirectionalLight>();
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
