#include "rktpch.h"
#include "Mesh.h"

#include <fstream>
#include "json.hpp"

#include <glad/glad.h>

using json = nlohmann::json;

namespace Arkitect {
	
	Mesh::Mesh(const std::string& path)
	{
		std::ifstream file(path);
		// TODO check path
		json data = json::parse(file);
		auto node = data["nodes"][0];
		//if (node.contains("rotation"))
		int indicesIndex = data["meshes"][(int)node["mesh"]]["primitives"][0]["indices"];
		int positionIndex = data["meshes"][(int)node["mesh"]]["primitives"][0]["attributes"]["POSITION"];
	
		std::string bufferUri = path.substr(0, path.find_last_of('/') + 1) + (std::string)data["buffers"][0]["uri"];
		uint32_t bufferSize = data["buffers"][0]["byteLength"];
		std::ifstream bufferFile(bufferUri, std::ios::binary);
		
		uint8_t* buffer = new uint8_t[bufferSize];
		bufferFile.read((char*)buffer, bufferSize);

		auto positionBufferView = data["bufferViews"][(int)data["accessors"][positionIndex]["bufferView"]];
		auto indicesBufferView = data["bufferViews"][(int)data["accessors"][indicesIndex]["bufferView"]];

		auto x = data["accessors"][indicesIndex]["componentType"];
		std::shared_ptr<VertexBuffer> vertexBuffer = std::make_shared<VertexBuffer>(buffer + (int)positionBufferView["byteOffset"], positionBufferView["byteLength"]);
		std::shared_ptr<IndexBuffer> indexBuffer =  std::make_shared<IndexBuffer>(buffer + (int)indicesBufferView["byteOffset"], (int)data["accessors"][indicesIndex]["count"], data["accessors"][indicesIndex]["componentType"]);

		BufferLayout layout = {
			{ShaderDataType::Float3, "position"}
		};
		vertexBuffer->SetLayout(layout);

		m_VertexArray = std::make_shared<VertexArray>();
		m_VertexArray->AddVertexBuffer(vertexBuffer);
		m_VertexArray->SetIndexBuffer(indexBuffer);

		bufferFile.close();
		delete[] buffer;
	}

	Mesh::~Mesh()
	{

	}

	glm::mat4 Mesh::GetTransform()
	{
		return glm::mat4(1.0);
	}

}