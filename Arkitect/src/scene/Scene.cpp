#include "rktpch.h"
#include "Scene.h"
#include "Entity.h"

namespace Arkitect {
	
	Scene::Scene()
	{

	}

	Scene::~Scene()
	{

	}

	Arkitect::Entity Scene::CreateEntity(const std::string& name /*= std::string()*/)
	{
		Entity entity = { m_Registry.create(), this };
		return entity;
	}

	void Scene::DestroyEntity(Entity entity)
	{
		m_Registry.destroy(entity);
	}

}