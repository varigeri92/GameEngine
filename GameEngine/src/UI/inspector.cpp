#include "inspector.h"
#include "UI.h"
#include "../ImGui/imgui.h"
#include "glm/glm.hpp"
#include "Log.h"
#include "Components.h"


editor::ui::Inspector::Inspector(core::Entity* entity) : m_CurrentEntity { entity }{}

using namespace core;

void editor::ui::Inspector::DrawInspector()
{
    if (!m_CurrentEntity) { 
        LOG_INFO("current entity is nullptr");
        return;
    }

    ImGui::Begin(m_CurrentEntity->name.c_str());
    ImGui::DragFloat3("Position", glm::value_ptr(m_CurrentEntity->GetComponent<Transform>().position), 0.1f);
    ImGui::DragFloat3("Rotation", glm::value_ptr(m_CurrentEntity->GetComponent<Transform>().rotation), 0.1f);
    ImGui::DragFloat3("Scale", glm::value_ptr(m_CurrentEntity->GetComponent<Transform>().scale), 0.1f);
    ImGui::End();

}
