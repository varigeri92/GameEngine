#pragma once
#include <string>
#include <vector>
#include "Entity.h"


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
		Inspector(core::Entity* entity);
		//Inspector(core::Transform* t);
		void DrawInspector();

	private:
		core::Entity* m_CurrentEntity;
	};
}

