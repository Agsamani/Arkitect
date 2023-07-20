#pragma once
#include "Arkitect.h"

class GameLayer : public Arkitect::Layer {

public:
	GameLayer();
	~GameLayer();

	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(float dt) override;
	void OnImGuiUpdate() override;
	void OnEvent(Arkitect::Event& e) override;

private:
	Arkitect::Entity m_PacMan;

	Arkitect::OrthographicCameraController m_Camera;

	std::shared_ptr<Arkitect::Scene> m_Scene;
};
