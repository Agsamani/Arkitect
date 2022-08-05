#pragma once
#include "Arkitect.h"

class TestLayer : public Arkitect::Layer
{
public:
	TestLayer()
		:Layer("TestLayer")
	{

	}

	~TestLayer() = default;

	void OnImGuiUpdate() override;


	void OnAttach() override;


	void OnDetach() override;


	void OnUpdate(float dt) override;


	void OnEvent(Arkitect::Event& e) override;

};

