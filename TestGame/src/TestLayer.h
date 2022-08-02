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

};

