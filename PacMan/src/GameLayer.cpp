#include "GameLayer.h"
#include "imgui.h"

GameLayer::GameLayer()
	:Layer("GameLayer"), m_Camera(1.0), m_Scene(std::make_shared<Arkitect::Scene>())
{

}

void GameLayer::OnAttach()
{
	Arkitect::RenderCommand::SetClearColor(glm::vec4(0.15, 0.15, 0.15, 1.0));
	Arkitect::Renderer2D::Init();

	Arkitect::SpriteSheet spriteSheet(std::make_shared<Arkitect::Texture2D>("assets/textures/PacManSheet.png", true));

	auto& background = m_Scene->CreateEntity("Background");
	background.AddComponent<Arkitect::SpriteComponent>().SetSpriteSheet(spriteSheet, { 228, 0 }, { 451, 247 });
	background.AddComponent<Arkitect::TransformComponent>();
	background.GetComponent<Arkitect::TransformComponent>().Translation.z = 0.0;

	m_PacMan = m_Scene->CreateEntity("PacMan");
	m_PacMan.AddComponent<Arkitect::SpriteComponent>();//.SetSpriteSheet(spriteSheet, { 488, spriteSheet.GetTexture()->GetHeight() - 1}, { 502,spriteSheet.GetTexture()->GetHeight() - 14 - 1});
	m_PacMan.AddComponent<Arkitect::TransformComponent>().Scale = { 0.06, 0.06, 1.0 };
	m_PacMan.GetComponent<Arkitect::TransformComponent>().Translation.z = 1.0;

	m_Scene->OnSceneStart();

	// TODO : Change y reverse of sprite sheet

	Arkitect::SpriteAnimationSpec spec;
	spec.FrameWidth = 15;
	spec.FrameHeight = 15;
	spec.HorizontalFrameCount = 3;
	spec.VerticalFrameCount = 1;
	spec.FrameCount = 3;
	spec.StartPixelCoordinate = { 456 ,spriteSheet.GetTexture()->GetHeight() - 1 };
	spec.Duration = 0.25;

	m_Animation = std::make_shared<Arkitect::SpriteAnimation>(spriteSheet, spec);
	m_Animation->Reset();

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

	m_Animation->OnUpdate(dt);
	m_PacMan.GetComponent<Arkitect::SpriteComponent>().SetSpriteSheet(m_Animation->GetSpriteSheet());
}

void GameLayer::OnImGuiUpdate()
{
	ImGui::Begin("Animation");
	if (ImGui::Button("Play")) {
		m_Animation->Play();
	}
	if (ImGui::Button("Pause")) {
		m_Animation->Pause();
	}
	if (ImGui::Button("Reset")) {
		m_Animation->Reset();
	}
	ImGui::End();
}

void GameLayer::OnEvent(Arkitect::Event& e)
{
	m_Camera.OnEvent(e);
}

GameLayer::~GameLayer()
{

}