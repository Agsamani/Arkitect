#include "MandleBulbDemo.h"
#include "imgui.h"

#include <fstream>
#include <sstream>

#define GLM_ENABLE_EXPERIMENTAL // TODO : move to premake maybe
#include "glm/gtx/vector_angle.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>


void MandleBulbDemo::OnAttach()
{
	Arkitect::RenderCommand::SetClearColor({ 0.15, 0.15, 0.15, 1.0 });


	float vertices[] = {
		-1.0f, -1.0f,
		 1.0f, -1.0f,
		 1.0f,  1.0f,
		-1.0f,  1.0f
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	VAO = std::make_shared<Arkitect::VertexArray>();

	std::shared_ptr<Arkitect::VertexBuffer> VBO = std::make_shared<Arkitect::VertexBuffer>(vertices, sizeof(vertices));

	Arkitect::BufferLayout layout = {
		{Arkitect::ShaderDataType::Float2, "position"}
	};
	VBO->SetLayout(layout);

	std::shared_ptr<Arkitect::IndexBuffer> IBO = std::make_shared<Arkitect::IndexBuffer>(indices, 6);

	VAO->SetIndexBuffer(IBO);
	VAO->AddVertexBuffer(VBO);

	program = std::make_unique<Arkitect::Program>();
	program->AttachShader(Arkitect::Shader("assets/shaders/RayMarchingFractal.vert", Arkitect::ShaderType::Vertex));
	program->AttachShader(Arkitect::Shader("assets/shaders/RayMarchingFractal.frag", Arkitect::ShaderType::Fragment));

	program->LinkProgram();
	program->UseProgram();

	cPosition = glm::vec3(0.0, 0.0, -3.0);
	cameraDir = glm::vec4(0.0, 0.0, 1.0, 1.0);

	cOrientation = glm::rotate(glm::mat4(1.0), theta, glm::vec3(0.5, -0.4, 0.7));
	newOrientation = glm::mat4(1.0);
}

void MandleBulbDemo::OnDetach()
{

}

void MandleBulbDemo::OnUpdate(float dt)
{
	float moveSpeed = 1.5;
	float rotationSpeed = 2.0;
	if (Arkitect::Input::IsKeyPressed(Arkitect::Key::W)) {
		cPosition.y += moveSpeed * dt;
	}
	else if (Arkitect::Input::IsKeyPressed(Arkitect::Key::S)) {
		cPosition.y -= moveSpeed * dt;
	}
	if (Arkitect::Input::IsKeyPressed(Arkitect::Key::D)) {
		cPosition.x += moveSpeed * dt;
	}
	else if (Arkitect::Input::IsKeyPressed(Arkitect::Key::A)) {
		cPosition.x -= moveSpeed * dt;
	}
	if (Arkitect::Input::IsKeyPressed(Arkitect::Key::Z)) {
		cPosition.z += moveSpeed * dt;
	}
	else if (Arkitect::Input::IsKeyPressed(Arkitect::Key::X)) {
		cPosition.z -= moveSpeed * dt;
	}

	if (Arkitect::Input::IsKeyPressed(Arkitect::Key::E)) {
		var += 0.5 * dt;
	}
	else if (Arkitect::Input::IsKeyPressed(Arkitect::Key::Q)) {
		var -= 0.5 * dt;
	}


	if (Arkitect::Input::IsMouseButtonPressed(Arkitect::Mouse::ButtonLeft)) {

		glm::vec2 curserPos = Arkitect::Input::GetMousePosition();
		curserPos = glm::normalize(glm::vec2(curserPos.x, -curserPos.y)) * glm::vec2(2.0 * 1.6, 2.0) - glm::vec2(1.0);
		if (firstClick) {
			cOrientation *= newOrientation;
			newOrientation = glm::mat4(1.0);
			firstClick = false;
			prevCurserPos = curserPos;
		}
		glm::vec3 B = glm::normalize(glm::vec3(prevCurserPos, 1.0));
		glm::vec3 A = glm::normalize(glm::vec3(curserPos, 1.0));

		glm::vec3 yRAxis = glm::cross(glm::vec3(0.0, 1.0, 0.0), glm::vec3(cameraDir));
		newOrientation = glm::rotate(glm::mat4(1.0), (A.x - B.x) * 3, glm::vec3(0.0, 1.0, 0.0));// *glm::rotate(glm::mat4(1.0), A.y - B.y, yRAxis);
		//cameraDir = newOrientation * cameraDir;

	}
	else {
		firstClick = true;
	}


	program->UploadUniformMat4("u_Transform", glm::translate(glm::mat4(1.0f), cPosition));
	program->UploadUniformMat4("u_RayRotation", cOrientation * newOrientation);
	program->UploadUniformFloat("u_Var", var);
	program->UploadUniformInt("u_Power", powerVar);
	program->UploadUniformFloat3("u_GlowColor", GlowColor);
	program->UploadUniformFloat3("u_BGColor", BGColor);
	program->UploadUniformFloat3("u_AColor", AColor);
	program->UploadUniformFloat3("u_BColor", BColor);
	program->UploadUniformInt("u_MaxIt", maxIt);
	program->UploadUniformFloat("u_Div", divi);


	//var += 0.15 * dt;
	//theta -= 0.12 * dt;
	cOrientation = glm::rotate(glm::mat4(1.0), theta, glm::vec3(0.5, -0.4, 0.7));

	Arkitect::RenderCommand::Clear();
	program->UseProgram();
	Arkitect::RenderCommand::DrawIndexed(VAO, 6);
}

void MandleBulbDemo::OnImGuiUpdate()
{
	ImGui::Begin("Colors:");
	ImGui::ColorEdit3("Glow Color", glm::value_ptr(GlowColor));
	ImGui::ColorEdit3("Background Color", glm::value_ptr(BGColor));
	ImGui::ColorEdit3("A Color", glm::value_ptr(AColor));
	ImGui::ColorEdit3("B Color", glm::value_ptr(BColor));
	ImGui::InputInt("Max iterations", &maxIt, 10, 100);
	ImGui::InputFloat("Div", &divi);
	ImGui::End();
}

void MandleBulbDemo::OnEvent(Arkitect::Event& e)
{

}