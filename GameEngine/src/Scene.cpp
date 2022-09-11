#include "Scene.h"
#include "Log.h"

#include "UI/UI.h"
#include "UI/inspector.h"

#include "Components.h"
#include "entt/entt.hpp"

#include "Rendering/Renderer.h"
#include "Rendering/Camera.h"

#include "CameraSystem.h"

#include "UI/Outliner.h"
#include "UI/Inspector.h"
#include "entt/entt.hpp"

#include "ImGui/imgui.h"
#include "EngineTime.h"


editor::ui::Inspector inspector;

core::Entity core::Scene::CreateEntity(std::string name)
{
	LOG_INFO("ENTITY created: " << name);
	entt::entity entity = m_registry.create();
	m_registry.emplace<Transform>(entity);
	m_registry.emplace<EntityComponent>(entity, name);
	inspector.m_scene = &*this;
	return Entity(name, *this, entity);
}

void core::Scene::CreateScene(Renderer* renderer, core::ui::UI &ui)
{
	this->ui = &ui;
	this->renderer = renderer;
	outliner.scene = &*this;
	outliner.inspector = &inspector;
}

void core::Scene::Awake()
{
	Entity entity = { cameraEntity, *this };
	Transform& t = entity.GetComponent<Transform>();
	InitCameraTransform(t, 
		{ 0.f, 0.f, 5.f }, 
		{ 0.f, -90.f, 0.f }
	);
	inspector.SelectEntity(entity);
}

void core::Scene::Start()
{
	current = 1;
}

void core::Scene::Update()
{

	/*
	auto view = m_registry.view<Transform>();
	for (auto entity : view)
	{
		auto transform = view.get<Transform>(entity);
	}
	*/

	Entity entity = { cameraEntity, *this };
	Transform& transform = entity.GetComponent<Transform>();
	FlyCameraUpdate(transform, *activeCamera);
	UpdateView(*activeCamera, transform);
}

void core::Scene::Render()
{
	renderer->StartFrame(*this);
	ui->OnFrameStart();

	auto view = m_registry.view<Transform, MeshComponent>();

	for (auto entity : view)
	{
		auto transform = view.get<Transform>(entity);
		auto mesh = view.get<MeshComponent>(entity);

		renderer->Draw(&mesh, transform, *this);
	}

	outliner.DrawOutliner();
	inspector.DrawInspector();

	ImGui::Begin("light");

	ImGui::Separator();
	ImGui::SliderFloat("intensity", &Light->lightIntensity, 0, 2.f);
	ImGui::ColorEdit3("color", glm::value_ptr(Light->lightColor));
	
	ImGui::Separator();

	ImGui::SliderFloat("ambient_intensity", &ambient->intensity, 0, 2.f);
	ImGui::ColorEdit3("ambient_color", glm::value_ptr(ambient->ambientColor));
	ImGui::Separator();

	ImGui::End();

	ImGui::Begin("FPS");

	std::string frametime = "Frame time: " + std::to_string(Time::GetDelta());
	std::string fps = "Frame count: " + std::to_string(1 / Time::GetDelta());
	std::string drawCalls = "Draw Calls: " + std::to_string(m_drawCalls);
	std::string batches = "Batches: " + std::to_string(m_batches);
	ImGui::Text(frametime.c_str());
	ImGui::Text(fps.c_str());
	ImGui::Text(drawCalls.c_str());
	ImGui::Text(batches.c_str());
	ImGui::End();

	ui->DrawGUI();
}

void core::Scene::ApplicationClose()
{

}


