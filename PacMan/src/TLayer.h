#pragma once
#include "Arkitect.h"

class TLayer : public Arkitect::Layer {

public:
	TLayer();

	~TLayer() = default;

	void OnImGuiUpdate() override;
	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(float dt) override;
	void OnEvent(Arkitect::Event & e) override;
};