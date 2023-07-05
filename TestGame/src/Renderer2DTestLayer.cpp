#include "Renderer2DTestLayer.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui.h"


Renderer2DTestLayer::Renderer2DTestLayer()
	:Layer("Renderer2DLayer"), m_Camera(1.6)
{
}

void Renderer2DTestLayer::OnAttach()
{
	Arkitect::RenderCommand::SetClearColor({ 0.15, 0.15, 0.15, 1.0 });

	Arkitect::Renderer2D::Init();

	Arkitect::Font font("assets/fonts/Inconsolata-Medium.ttf");

	m_TestTexture = std::make_shared<Arkitect::Texture2D>("assets/textures/testTex.png", 1);
	m_TestTexture->BindImage(1);

	m_TestScene = std::make_unique<Arkitect::Scene>();

	entito = m_TestScene->CreateEntity("Yo");
	entito.AddComponent<Arkitect::TransformComponent>();
	entito.AddComponent<Arkitect::SpriteComponent>(glm::vec4(0.21f, 0.67f, 0.76f, 1.0f));
	entito.AddComponent<Arkitect::RigidBody2DComponent>();
	entito.AddComponent<Arkitect::BoxCollider2DComponent>();

	auto& x = entito.GetComponent<Arkitect::RigidBody2DComponent>();
	x.Type = Arkitect::RigidBody2DComponent::BodyType::Dynamic;

	Arkitect::Entity entitoi = m_TestScene->CreateEntity("Ho");
	entitoi.AddComponent<Arkitect::TransformComponent>();
	entitoi.AddComponent<Arkitect::SpriteComponent>(glm::vec4(0.81f, 0.27f, 0.46f, 1.0f));
	entitoi.AddComponent<Arkitect::RigidBody2DComponent>();
	entitoi.AddComponent<Arkitect::BoxCollider2DComponent>();

	auto& gt = entitoi.GetComponent<Arkitect::TransformComponent>();
	gt.Translation.y = -3;
	gt.Scale.x = 10;
	gt.Rotation.z = 0.3;

	m_TestScene->OnSceneStart();
}

void Renderer2DTestLayer::OnDetach()
{

}

void Renderer2DTestLayer::OnUpdate(float dt)
{
	m_Camera.OnUpdate(dt);

	Arkitect::RenderCommand::Clear();

	m_TestScene->OnUpdate(dt);
	m_TestScene->OnSceneUpdate(dt, m_Camera.GetCamera());

	Arkitect::Renderer2D::BeginScene(m_Camera.GetCamera());

// 	int maxIt = 16;
// 	float mx = 1.6 * ((Arkitect::Input::GetMouseX() / float(2048)) - 0.5) * 2;
// 	float my = ((Arkitect::Input::GetMouseY() / float(1280)) - 0.5) * 2;
// 	for (int i = 0; i < maxIt; i++) {
// 		glm::mat4 transform =
// 			glm::translate(glm::mat4(1.0f), glm::vec3(((maxIt - i) / float(maxIt)) * mx, (-(maxIt - i) / float(maxIt)) * my, 0.0))
// 			* glm::rotate(glm::mat4(1.0f), glm::radians(((maxIt - i) / float(maxIt) * 360.0f * my)), glm::vec3(0, 0, 1))
// 			* glm::scale(glm::mat4(1.0), glm::vec3((i + 1) / (1 * float(maxIt)), (i + 1) / float(maxIt), 1.0));
// 		float lerpval = i / float(maxIt);
// 		glm::vec4 color = m_QuadColorA + (m_QuadColorB - m_QuadColorA) * lerpval;
// 		Arkitect::Renderer2D::DrawQuad(transform, color);
// 	}
// 	
	Arkitect::Renderer2D::EndScene();
}

void Renderer2DTestLayer::OnEvent(Arkitect::Event& e)
{
	m_Camera.OnEvent(e);
	if (e.GetEventType() == Arkitect::EventType::MouseButtonPressed)
	{
		entito = m_TestScene->CreateEntity("A");
		entito.AddComponent<Arkitect::TransformComponent>();
		float shade = Arkitect::Random::Float();
		entito.AddComponent<Arkitect::SpriteComponent>(glm::vec4(shade*0.5 + 0.5, shade*0.6, shade*0.2 + 0.7, 1.0f));
		entito.AddComponent<Arkitect::RigidBody2DComponent>();
		entito.AddComponent<Arkitect::BoxCollider2DComponent>();
		entito.GetComponent<Arkitect::RigidBody2DComponent>().Type = Arkitect::RigidBody2DComponent::BodyType::Dynamic;
		m_TestScene->OnSceneStart();

	}
}

void Renderer2DTestLayer::OnImGuiUpdate()
{
	ImGui::Begin("color");
	ImGui::ColorEdit4("QuadA", glm::value_ptr(m_QuadColorA));
	ImGui::ColorEdit4("QuadB", glm::value_ptr(m_QuadColorB));
	ImGui::End();
}
