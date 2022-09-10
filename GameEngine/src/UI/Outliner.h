#pragma once
#include <memory>
#include "entt/entt.hpp"

namespace core{
class Scene;
}

namespace editor::ui
{
	class Inspector;

	class Outliner
	{
	public:
		Outliner(core::Scene* scene);
		Outliner() = default;
		void DrawOutliner();
		void DrawHelper(entt::entity _entity);
		core::Scene* scene;
		Inspector* inspector;
		entt::entity current;
	private:
	};
}
