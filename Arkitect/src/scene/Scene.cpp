#include "rktpch.h"
#include "Scene.h"
#include "Entity.h"
#include "ScriptableEntity.h"

// Box2D
#include "box2d/b2_world.h"
#include "box2d/b2_body.h"
#include "box2d/b2_fixture.h"
#include "box2d/b2_polygon_shape.h"
#include "box2d/b2_circle_shape.h"

#include "core/Base.h"
#include "renderer/Renderer2D.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//

namespace Arkitect {

	Scene::Scene()
	{
		Renderer2D::Init();
	}

	Scene::~Scene()
	{
		delete m_PhyisicsWorld;

		// TODO: move to scene stop or sth
		auto view = m_Registry.view<ScriptComponent>();
		for (auto e : view) {
			Entity entity = { e , this };
			ScriptComponent& sc = entity.GetComponent<ScriptComponent>();
			sc.instance->OnDestroy();
			sc.DestroyScript();
		}
	}

	Entity Scene::CreateEntity(const std::string& name /*= std::string()*/)
	{
		Entity entity = { m_Registry.create(), this };
		return entity;
	}

	void Scene::DestroyEntity(Entity entity)
	{
		m_Registry.destroy(entity);
	}

	void Scene::OnSceneStart()
	{
		auto view = m_Registry.view<ScriptComponent>();
		for (auto e : view) {
			Entity entity = { e , this };
			ScriptComponent& sc = entity.GetComponent<ScriptComponent>();
			sc.InstantiateScript();
			sc.instance->OnCreate();
		}

		OnPhysics2DStart();
	}

	void Scene::OnSceneUpdate(Deltatime dt, const OrthographicCamera& camera)
	{

		Renderer2D::BeginScene(camera);

		auto group = m_Registry.group<SpriteComponent>(entt::get<TransformComponent>);
		for (auto entity : group) {
			auto [transform, sprite] = group.get<TransformComponent, SpriteComponent>(entity);

			Renderer2D::DrawSprite(transform.GetTransform(), sprite);
		}

		Renderer2D::EndScene();
	}

	void Scene::OnUpdate(Deltatime dt)
	{
		{
			auto view = m_Registry.view<ScriptComponent>();
			for (auto e : view) {
				Entity entity = { e , this };
				entity.GetComponent<ScriptComponent>().instance->OnUpdate(dt);
			}
		}

		{
			int32 velocityIterations = 6;
			int32 positionIterations = 2;

			m_PhyisicsWorld->Step(dt, velocityIterations, positionIterations);

			auto view = m_Registry.view<RigidBody2DComponent>();
			for (auto e : view) {
				Entity entity = { e, this };
				auto& transform = entity.GetComponent<TransformComponent>();
				auto& rb2d = entity.GetComponent<RigidBody2DComponent>();

				b2Body* body = (b2Body*)rb2d.RuntimeBody;
				auto const& pos = body->GetPosition();
				transform.Translation.x = pos.x;
				transform.Translation.y = pos.y;
				transform.Rotation.z = body->GetAngle();
			}
		}
	}

	void Scene::OnEvent(Event& e)
	{
		auto view = m_Registry.view<ScriptComponent>();
		for (auto ent : view) {
			if (e.Handled) {
				break;
			}
			Entity entity = { ent , this };
			entity.GetComponent<ScriptComponent>().instance->OnEvent(e);
		}
	}

	void Scene::OnPhysics2DStart()
	{
		m_PhyisicsWorld = new b2World({ 0.0f, -9.8f });

		auto view = m_Registry.view<RigidBody2DComponent>();
		for (auto e : view) {
			Entity entity = { e, this };
			auto& transform = entity.GetComponent<TransformComponent>();
			auto& rb2d = entity.GetComponent<RigidBody2DComponent>();

			b2BodyDef bodyDef;

			switch (rb2d.Type) {
			case RigidBody2DComponent::BodyType::Static:    bodyDef.type = b2_staticBody; break;
			case RigidBody2DComponent::BodyType::Dynamic:   bodyDef.type = b2_dynamicBody; break;
			case RigidBody2DComponent::BodyType::Kinematic: bodyDef.type = b2_kinematicBody; break;
			default: bodyDef.type = b2_staticBody;
			}

			bodyDef.position.Set(transform.Translation.x, transform.Translation.y);
			bodyDef.angle = transform.Rotation.z;

			b2Body* body = m_PhyisicsWorld->CreateBody(&bodyDef);
			body->SetFixedRotation(rb2d.FixedRotation);
			rb2d.RuntimeBody = body;

			if (entity.HasComponent<BoxCollider2DComponent>()) {
				auto bc2d = entity.GetComponent<BoxCollider2DComponent>();

				b2PolygonShape shape;
				shape.SetAsBox(bc2d.Size.x * transform.Scale.x, bc2d.Size.y * transform.Scale.y);

				b2FixtureDef fixture;
				fixture.shape = &shape;
				fixture.density = bc2d.Density;
				fixture.friction = bc2d.Friction;
				fixture.restitution = bc2d.Restitution;
				fixture.restitutionThreshold = bc2d.RestitutionThreshold;
				body->CreateFixture(&fixture);
			}
		}
	}

}