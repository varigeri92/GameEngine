#pragma once
#include <string>
#include "Components.h"

#include <vector>
#include <utility>
#include <entt/entt.hpp>
#include "Scene.h"


namespace core {
	class Scene;

	struct Entity
	{
		Entity(std::string name, Scene& _scene, entt::entity entity) :
			name{ name },
			scene{ &_scene },
			m_entity{ entity }
		{};

		template<typename T, typename... Args>
		T& AddComponet(Args&& ... args)
		{
			T& component = scene->m_registry.emplace<T>(m_entity, std::forward<Args>(args)...);
			component.entity = &*this;
			return component;
		}
		template<typename T>
		T& GetComponent()
		{
			return scene->m_registry.get<T>(m_entity);
		}

		std::string name;
		entt::entity m_entity;

		uint64_t UUID;
		Scene* scene;
	
	};
}

