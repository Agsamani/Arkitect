#pragma once
#include "scene/Entity.h"
#include "events/Event.h"


namespace Arkitect {

	class ScriptableEntity
	{
	public:
		virtual ~ScriptableEntity() = default;


	protected:
		virtual void OnCreate() {};
		virtual void OnUpdate(Deltatime dt) {};
		virtual void OnEvent(Event& e) {};
		virtual void OnDestroy() {};
	private:
		Entity m_Entity;
		friend class Scene;
	};
}