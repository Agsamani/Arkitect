#include "TestLayer.h"
#include "imgui.h"

#include <fstream>
#include <sstream>

#include <glm/glm.hpp>


void TestLayer::OnAttach()
{
	
}

void TestLayer::OnDetach()
{
	
}

void TestLayer::OnUpdate(float dt)
{
	
}

void TestLayer::OnImGuiUpdate()
{
	ImGui::Begin("Test");
	ImGui::Text("LOOOLE");
	if (ImGui::Button("TOUCH ME!")) {
		RKT_INFO("lol");
	}
	ImGui::End();
}

void TestLayer::OnEvent(Arkitect::Event& e)
{
	
}
