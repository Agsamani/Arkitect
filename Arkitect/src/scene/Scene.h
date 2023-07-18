#pragma once

#include <string>
#include <entt.hpp>

#include "core/Deltatime.h"
#include "events/Event.h"

//Temp
#include "Renderer/camera/OrthigraphicCamera.h"
#include "renderer/Renderer2D.h"

class b2World;
class b2Body;

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

		void OnSceneStart();
		void OnSceneUpdate(Deltatime dt, const OrthographicCamera& camera);

		void OnUpdate(Deltatime dt);
		void OnEvent(Event& e);

	private:
		void OnPhysics2DStart();

	private:
		entt::registry m_Registry;
		b2World* m_PhysicsWorld = nullptr;

		b2World* m_PhyisicsWorld;
		friend class Entity;
	};
}

