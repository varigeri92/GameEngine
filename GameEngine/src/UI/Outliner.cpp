#include "Outliner.h"
#include "Scene.h"
#include "Components.h"
#include "UI.h"
#include "../ImGui/imgui.h"
#include "Entity.h"
#include "inspector.h"


static ImGuiTreeNodeFlags base_flags = 
ImGuiTreeNodeFlags_OpenOnArrow | 
ImGuiTreeNodeFlags_OpenOnDoubleClick |
ImGuiTreeNodeFlags_SpanAvailWidth | 
ImGuiTreeNodeFlags_SpanFullWidth;

static ImGuiTreeNodeFlags node_flags = base_flags;
void SetupTreeBranch() {

}

editor::ui::Outliner::Outliner(core::Scene* scene)
{
	this->scene = scene;
}

void editor::ui::Outliner::DrawHelper(entt::entity _entity) {

	ImGuiTreeNodeFlags flags = node_flags;
	if (current == _entity)
		flags |= ImGuiTreeNodeFlags_Selected;


	std::string name = scene->m_registry.get<core::EntityComponent>(_entity).name;
	if (ImGui::TreeNodeEx((const void*)_entity, flags, name.c_str()))
	{
		if (ImGui::IsItemClicked()) {
			inspector->SelectEntity(_entity);
			current = _entity;
		}

		ImGui::TreePop();
	}
	if (ImGui::IsItemClicked()) {
		inspector->SelectEntity(_entity);
		current = _entity;
	}
}

void editor::ui::Outliner::DrawOutliner()
{
	ImGui::Begin("Outliner");
	if (ImGui::TreeNodeEx("Scene", base_flags |= ImGuiTreeNodeFlags_DefaultOpen))
	{
		scene->m_registry.each([&](auto _entity) {
			DrawHelper(_entity);
		});
		ImGui::TreePop();
	}
	ImGui::End();
}

