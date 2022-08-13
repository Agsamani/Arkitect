#pragma once

#include <string>
#include <entt.hpp>

#include "core/Deltatime.h"

namespace Arkitect {
	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string& name = std::string());
		void DestroyEntity(Entity entity);

		template<typename... Components>
		auto GetAllEntitiesWith()
		{
			return m_Registry.view<Components...>();
		}

		void OnUpdate(Deltatime dt);

	private:
		entt::registry m_Registry;

		friend class Entity;
	};
}

