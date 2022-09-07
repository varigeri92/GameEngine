#include "Scene.h"
#include "Log.h"
#include "Component.h"
#include "UI/UI.h"
#include "UI/inspector.h"

#include "Components.h"
#include "entt/entt.hpp"

#include "Rendering/Renderer.h"
#include "Rendering/Camera.h"

core::Entity core::Scene::CreateEntity(std::string name)
{
	LOG_INFO("ENTITY created: " << name);
	entt::entity entity = m_registry.create();
	m_registry.emplace<Transform>(entity);
	return Entity(name, *this, entity);
}

void core::Scene::CreateScene(Renderer* renderer, core::ui::UI &ui)
{
	this->ui = &ui;
	this->renderer = renderer;
}

void core::Scene::Awake()
{
	auto view = m_registry.view<Component>();

	for (auto entity : view)
	{
		auto component = view.get<Component>(entity);
		component.OnAwake();
	}
}

void core::Scene::Start()
{
	auto view = m_registry.view<Component>();

	for (auto entity : view)
	{
		auto component = view.get<Component>(entity);
		component.OnStart();
	}
}

void core::Scene::Update()
{
	auto view = m_registry.view<Component>();

	for (auto entity : view)
	{
		auto component = view.get<Component>(entity);
		component.OnUpdate();
	}
}

void core::Scene::Render()
{
	renderer->StartFrame();
	ui->OnFrameStart();
	/*
	*/
	auto view = m_registry.view<Transform, MeshComponent>();

	for (auto entity : view)
	{
		auto transform = view.get<Transform>(entity);
		auto mesh = view.get<MeshComponent>(entity);

		renderer->Draw(&mesh, transform, *this);
		editor::ui::Inspector inspector(mesh.entity);
		inspector.DrawInspector();
	}

	editor::ui::Inspector inspector(activeCamera->entity);
	inspector.DrawInspector();

	ui->DrawGUI();
}

void core::Scene::ApplicationClose()
{

}


