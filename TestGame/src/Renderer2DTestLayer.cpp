#include "Renderer2DTestLayer.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui.h"


Renderer2DTestLayer::Renderer2DTestLayer()
	:Layer("Renderer2DLayer"), m_Camera(1.6)
{
	m_Renderer2D = std::make_unique<Arkitect::Renderer2D>();
}

void Renderer2DTestLayer::OnAttach()
{
	Arkitect::RenderCommand::SetClearColor({ 0.15, 0.15, 0.15, 1.0 });

	m_Renderer2D->Init();

	m_TestTexture = std::make_shared<Arkitect::Texture2D>("assets/textures/testTex.png", 1);
	m_TestTexture->BindImage(1);

}

void Renderer2DTestLayer::OnDetach()
{

}

void Renderer2DTestLayer::OnUpdate(float dt)
{
	m_Camera.OnUpdate(dt);

	Arkitect::RenderCommand::Clear();


	m_Renderer2D->BeginScene(m_Camera.GetCamera());
	int maxIt = 8;
	for (int i = 0; i < maxIt; i++) {
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(((maxIt - i) / float(maxIt)) * 1.6 * ((Arkitect::Input::GetMouseX() / float(2048)) - 0.5) * 2, (-(maxIt - i) / float(maxIt)) * ((Arkitect::Input::GetMouseY() / float(1280)) - 0.5) * 2, 0.0)) * glm::scale(glm::mat4(1.0), glm::vec3((i + 1) / float(maxIt), (i + 1) / float(maxIt), 1.0));//glm::rotate(glm::mat4(1.0f), glm::radians(45.0), glm::vec3(0, 0, 1));
		float lerpval = i / float(maxIt);
		glm::vec4 color = m_QuadColorA + (m_QuadColorB - m_QuadColorA) * lerpval;
		m_Renderer2D->DrawQuad(transform, m_TestTexture, color);
	}
	
	m_Renderer2D->EndScene();
}

void Renderer2DTestLayer::OnEvent(Arkitect::Event& e)
{
	m_Camera.OnEvent(e);
}

void Renderer2DTestLayer::OnImGuiUpdate()
{
	ImGui::Begin("color");
	ImGui::ColorEdit4("QuadA", glm::value_ptr(m_QuadColorA));
	ImGui::ColorEdit4("QuadB", glm::value_ptr(m_QuadColorB));
	ImGui::End();
}
