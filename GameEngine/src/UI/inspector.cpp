#include "inspector.h"
#include "UI.h"
#include "../ImGui/imgui.h"
#include "glm/glm.hpp"
#include "Log.h"
#include "Components.h"
#include "entt/entt.hpp"

#include "Log.h"

using namespace core;


editor::ui::Inspector::Inspector(core::Scene& _scene) : 
    m_scene { &_scene }
{}

editor::ui::Inspector::Inspector() {}

void editor::ui::Inspector::SelectEntity(entt::entity entity)
{
    m_entity = { entity, *m_scene };
}

void editor::ui::Inspector::SelectEntity(core::Entity entity)
{
    m_entity = { entity };
}

void editor::ui::Inspector::DrawInspector()
{
    ImGui::Begin("Inspector");
    
    if (m_entity.m_entity == entt::null) return;

    ImGui::Text(m_entity.GetComponent<EntityComponent>().name.c_str());
    ImGui::Separator();
    Transform& transform = m_entity.GetComponent<Transform>();
    ImGui::DragFloat3("Position", glm::value_ptr(transform.position), 0.1f);
    ImGui::DragFloat3("Rotation", glm::value_ptr(transform.rotation), 0.1f);
    ImGui::DragFloat3("Scale", glm::value_ptr(transform.scale), 0.1f);
    ImGui::Separator();

    ImGui::End();
}
