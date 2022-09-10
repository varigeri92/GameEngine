#pragma once
#include <string>
#include <vector>
#include "Entity.h"
#include "entt/entt.hpp"


namespace core
{
	class Scene;
};


namespace editor::ui
{
	struct  InspectorField
	{
		std::string fieldName;
	};
	struct  InspectorFloatField : public InspectorField
	{
		float value;
	};

	struct  InspectorVector3Field : public InspectorField
	{
		float value[3] = { 0.f, 0.f, 0.f };
	};

	class ComponentInspector
	{
		std::string title;
		std::vector<InspectorField> fields;
	};

	class Inspector
	{
	public:
		Inspector(core::Scene& _scene);
		Inspector();

		void SelectEntity(entt::entity);
		void SelectEntity(core::Entity);
		void DrawInspector();

		core::Scene* m_scene;
		core::Entity m_entity;
	private:
	};
}

