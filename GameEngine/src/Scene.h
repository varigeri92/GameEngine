#pragma once
#include "Engine.h"
#include <map>
#include <unordered_map>
#include <vector>
#include <glm/glm.hpp>

#include "Components.h"

#include "Rendering/Renderer.h"
#include "Rendering/Camera.h"

#include "entt/entt.hpp"
#include "UI/Outliner.h"
//#include "UI/inspector.h"

namespace core::ui {
	class UI;
}


namespace editor::ui {
	//class Outliner;
	class Inspector;
}
namespace core
{
	struct Entity;

	class Scene
	{
	public:

		Entity CreateEntity(std::string name);
		CameraComponent* GetActiveCamera() const { return activeCamera; };

		entt::registry m_registry;

		//TEMP:
		DirectionalLight* Light;
		Transform* LightTransform;
		Ambient* ambient;
		//
		uint32_t m_drawCalls = 0;
		uint32_t m_batches = 0;

	private:
		void CreateScene(Renderer* renderer, core::ui::UI &ui);

		void Awake();
		void Start();
		void Update();
		void Render();
		void ApplicationClose();


		Renderer* renderer;
		CameraComponent* activeCamera;
		entt::entity cameraEntity;

		
		friend class Engine;
		core::ui::UI* ui;

		//TEMP:

		//test:
		uint32_t current;
		editor::ui::Outliner outliner;


		
	};

}

