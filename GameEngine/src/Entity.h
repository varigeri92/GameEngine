#pragma once
#include <string>
#include "Components.h"

#include <vector>
#include <utility>
#include <entt/entt.hpp>
#include "Scene.h"


namespace core {
	struct Entity
	{
		Entity(std::string name, Scene& _scene, entt::entity entity) :
			scene{ &_scene },
			m_entity{ entity }
		{};

		Entity(entt::entity entity, Scene& _scene) :
			m_entity	{ entity  },
			scene		{ &_scene }
		{};

		Entity() = default;
		~Entity();

		template<typename T, typename... Args>
		T& AddComponet(Args&& ... args)
		{
			T& component = scene->m_registry.emplace<T>(m_entity, std::forward<Args>(args)...);
			return component;
		}
		template<typename T>
		T& GetComponent()
		{
			return scene->m_registry.get<T>(m_entity);
		}

		template<typename T>
		bool TryGetComponent(T& component)
		{
			component = scene->m_registry.get<T>(m_entity);
			return true;
		}

		entt::entity m_entity;
		Scene* scene;
	
	};
}

