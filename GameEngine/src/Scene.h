#pragma once
#include "Engine.h"
#include <map>
#include <unordered_map>
#include <vector>
#include <glm/glm.hpp>
#include "Component.h"
#include "Components.h"

#include "Rendering/Renderer.h"
#include "Rendering/Camera.h"

#include "entt/entt.hpp"


namespace core::ui {
	class UI;
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
	private:
		void CreateScene(Renderer* renderer, core::ui::UI &ui);

		void Awake();
		void Start();
		void Update();
		void Render();
		void ApplicationClose();


		Renderer* renderer;
		CameraComponent* activeCamera;


		
		friend class Engine;
		core::ui::UI* ui;
	};

}

