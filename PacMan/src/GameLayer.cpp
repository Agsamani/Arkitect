#include "GameLayer.h"

GameLayer::GameLayer()
	:Layer("GameLayer"), m_Camera(1.6), m_Scene(std::make_shared<Arkitect::Scene>())
{

}

void GameLayer::OnAttach()
{
	Arkitect::RenderCommand::SetClearColor(glm::vec4(0.15, 0.15, 0.15, 1.0));
	Arkitect::Renderer2D::Init();

	Arkitect::SpriteSheet spriteSheet(std::make_shared<Arkitect::Texture2D>("assets/textures/PacManSheet.png", true));

	auto& background = m_Scene->CreateEntity("Background");
	background.AddComponent<Arkitect::SpriteComponent>().SetSpriteSheet(spriteSheet, { 228, 247 }, { 451, 0 });
	background.AddComponent<Arkitect::TransformComponent>();
	background.GetComponent<Arkitect::TransformComponent>().Translation.z = 0.0;

	m_PacMan = m_Scene->CreateEntity("PacMan");
	m_PacMan.AddComponent<Arkitect::SpriteComponent>().SetSpriteSheet(spriteSheet, { 488, 14 }, { 502, 0 });
	m_PacMan.AddComponent<Arkitect::TransformComponent>().Scale = { 0.06, 0.06, 1.0 };
	m_PacMan.GetComponent<Arkitect::TransformComponent>().Translation.z = 1.0;


	m_Scene->OnSceneStart();
}

void GameLayer::OnDetach()
{
	Arkitect::Renderer2D::Shutdown();
}

void GameLayer::OnUpdate(float dt)
{
	m_Camera.OnUpdate(dt);
	Arkitect::RenderCommand::Clear();

	m_Scene->OnSceneUpdate(dt, m_Camera.GetCamera());
	m_Scene->OnUpdate(dt);
}

void GameLayer::OnImGuiUpdate()
{
	
}

void GameLayer::OnEvent(Arkitect::Event& e)
{
	m_Camera.OnEvent(e);
}

GameLayer::~GameLayer()
{

}