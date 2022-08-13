#include "rktpch.h"
#include "Entity.h"

namespace Arkitect {
	Entity::Entity(entt::entity entityHandle, Scene* scene)
		:m_EntityHandle(entityHandle), m_Scene(scene)
	{
	}
}
