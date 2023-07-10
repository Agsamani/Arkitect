#include <rktpch.h>
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"
#include "Program.h"
#include "RenderCommand.h"
#include "Texture.h"

#include "renderer/MSDFData.h"


namespace Arkitect {

	struct QuadVertex {
		glm::vec2 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
	};

	struct Renderer2DData {
		std::shared_ptr<VertexBuffer> QuadVB;
		std::shared_ptr<VertexArray> QuadVA;
		std::shared_ptr<Program> QuadShader;
		std::shared_ptr<Program> TextShader;

		std::shared_ptr<Texture2D> QuadWhiteTexture;

		glm::vec4 QuadVertexPositions[4];

		glm::mat4 CameraMatrix;

	};

	static Renderer2DData s_Data;


	void Renderer2D::Init()
	{
		s_Data.QuadVertexPositions[0] = glm::vec4(-0.5, -0.5, 0.0, 1.0);
		s_Data.QuadVertexPositions[1] = glm::vec4(0.5, -0.5, 0.0, 1.0);
		s_Data.QuadVertexPositions[2] = glm::vec4(0.5,  0.5, 0.0, 1.0);
		s_Data.QuadVertexPositions[3] = glm::vec4(-0.5,  0.5, 0.0, 1.0);

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};


		s_Data.QuadVB = std::make_shared<VertexBuffer>(4 * sizeof(QuadVertex));
		s_Data.QuadVA = std::make_shared<VertexArray>();

		BufferLayout layout = {
			{ShaderDataType::Float2, "position"},
			{ShaderDataType::Float4, "color"},
			{ShaderDataType::Float2, "texcoord"}
		};
		s_Data.QuadVB->SetLayout(layout);

		std::shared_ptr<IndexBuffer> IBO = std::make_shared<IndexBuffer>(indices, 6);

		s_Data.QuadVA->SetIndexBuffer(IBO);
		s_Data.QuadVA->AddVertexBuffer(s_Data.QuadVB);

		s_Data.QuadShader = std::make_unique<Program>();
		s_Data.QuadShader->AttachShader(Shader("assets/shaders/engine/Renderer2DQuad.vert", ShaderType::Vertex));
		s_Data.QuadShader->AttachShader(Shader("assets/shaders/engine/Renderer2DQuad.frag", ShaderType::Fragment));
		s_Data.QuadShader->LinkProgram();
		s_Data.QuadShader->UseProgram();

		s_Data.TextShader = std::make_unique<Program>();
		s_Data.TextShader->AttachShader(Shader("assets/shaders/engine/Renderer2DQuad.vert", ShaderType::Vertex));
		s_Data.TextShader->AttachShader(Shader("assets/shaders/engine/Renderer2DText.frag", ShaderType::Fragment));
		s_Data.TextShader->LinkProgram();
		s_Data.TextShader->UseProgram();

		s_Data.QuadWhiteTexture = std::make_shared<Texture2D>(1, 1);
		glm::u8vec4 colorWhite = glm::u8vec4(255);
		s_Data.QuadWhiteTexture->SetData(&colorWhite, 4);
		s_Data.QuadWhiteTexture->BindImage(0);
	}

	void Renderer2D::Shutdown()
	{
		
	}

	

	void Renderer2D::BeginScene(const OrthographicCamera& ortho)
	{
		s_Data.CameraMatrix = ortho.GetViewProjection();
	}

	void Renderer2D::EndScene()
	{

	}

	void Renderer2D::DrawQuad(const glm::mat4& transform, const glm::vec4& color)
	{
		DrawQuad(transform, s_Data.QuadWhiteTexture, color);
	}

	void Renderer2D::DrawQuad(const glm::mat4& transform, const std::shared_ptr<Texture2D>& texture, const glm::vec4& tintColor)
	{
		QuadVertex Vertices[4];
		glm::vec2 TexCoords[4] = { {0.0, 0.0},
									{1.0, 0.0},
									{1.0, 1.0},
									{0.0, 1.0} };

		for (int i = 0; i < 4; i++)
		{
			Vertices[i].Position = glm::vec2((transform * s_Data.QuadVertexPositions[i]));
			Vertices[i].Color = tintColor;
			Vertices[i].TexCoord = TexCoords[i];	// TODO: Move to init
		}

		s_Data.QuadVB->SetData(Vertices, sizeof(Vertices));


		s_Data.QuadShader->UseProgram();
		s_Data.QuadShader->UploadUniformInt("u_Texture", 0);
		texture->Bind();
		s_Data.QuadShader->UploadUniformMat4("u_Camera", s_Data.CameraMatrix);

		RenderCommand::DrawIndexed(s_Data.QuadVA, 6);

	}

	void Renderer2D::DrawSprite(const glm::mat4& transform, const SpriteComponent& sprite)
	{
		if (sprite.Texture) {
			DrawQuad(transform, sprite.Texture, sprite.Color);
		}
		else {
			DrawQuad(transform, sprite.Color);
		}
	}

	void Renderer2D::DrawText(std::shared_ptr<Font> font, const std::string& text, const glm::mat4& transform)
	{
		QuadVertex Vertices[4];

		const auto& fontGeometry = font->GetMSDFData()->FontGeometry;
		const auto& metrics = fontGeometry.getMetrics();
		std::shared_ptr<Texture2D> fontAtlas = font->GetAtlasTexture();

		double x = 0.0;
		double fsScale = 1.0 / (metrics.ascenderY - metrics.descenderY);
		double y = 0.0;

		const float spaceGlyphAdvance = fontGeometry.getGlyph(' ')->getAdvance();

		for (int i = 0; i < text.length(); i++)
		{
			char character = text[i];

			if (character == '\r')
				continue;

			if (character == '\n')
			{
				x = 0;
				y -= fsScale * metrics.lineHeight;
				continue;
			}

			if (character == ' ')
			{
				float advance = spaceGlyphAdvance;
				if (i < text.size() - 1)
				{
					char nextCharacter = text[i + 1];
					double dAdvance;
					fontGeometry.getAdvance(dAdvance, character, nextCharacter);
					advance = (float)dAdvance;
				}

				x += fsScale * advance;
				continue;
			}

			if (character == '\t')
			{
				x += 4.0f * (fsScale * spaceGlyphAdvance);
				continue;
			}

			auto glyph = fontGeometry.getGlyph(character);
			if (!glyph)
				glyph = fontGeometry.getGlyph('?');
			if (!glyph)
				return;

			double al, ab, ar, at;
			glyph->getQuadAtlasBounds(al, ab, ar, at);
			glm::vec2 texCoordMin((float)al, (float)ab);
			glm::vec2 texCoordMax((float)ar, (float)at);

			double pl, pb, pr, pt;
			glyph->getQuadPlaneBounds(pl, pb, pr, pt);
			glm::vec2 quadMin((float)pl, (float)pb);
			glm::vec2 quadMax((float)pr, (float)pt);

			quadMin *= fsScale, quadMax *= fsScale;
			quadMin += glm::vec2(x, y);
			quadMax += glm::vec2(x, y);

			float texelWidth = 1.0f / fontAtlas->GetWidth();
			float texelHeight = 1.0f / fontAtlas->GetHeight();
			texCoordMin *= glm::vec2(texelWidth, texelHeight);
			texCoordMax *= glm::vec2(texelWidth, texelHeight);

			Vertices[0].Position = glm::vec2((transform * glm::vec4(quadMin, 0.0f, 1.0f)));
			Vertices[0].Color = glm::vec4(1.0);
			Vertices[0].TexCoord = texCoordMin;

			Vertices[1].Position = glm::vec2(((transform * glm::vec4(quadMax.x, quadMin.y, 0.0f, 1.0f))));
			Vertices[1].Color = glm::vec4(1.0);
			Vertices[1].TexCoord = { texCoordMax.x, texCoordMin.y };

			Vertices[2].Position = glm::vec2(((transform * glm::vec4(quadMax, 0.0f, 1.0f))));
			Vertices[2].Color = glm::vec4(1.0);
			Vertices[2].TexCoord = texCoordMax;

			Vertices[3].Position = glm::vec2(((transform * glm::vec4(quadMin.x, quadMax.y, 0.0f, 1.0f))));
			Vertices[3].Color = glm::vec4(1.0);
			Vertices[3].TexCoord = { texCoordMin.x, texCoordMax.y };

			s_Data.QuadVB->SetData(Vertices, sizeof(Vertices));

			s_Data.TextShader->UseProgram();
			s_Data.TextShader->UploadUniformInt("u_FontAtlas", 0);
			font->GetAtlasTexture()->Bind();
			s_Data.QuadShader->UploadUniformMat4("u_Camera", s_Data.CameraMatrix);

			RenderCommand::DrawIndexed(s_Data.QuadVA, 6);

			if (i < text.length() - 1)
			{
				double advance = glyph->getAdvance();
				char nextCharacter = text[i + 1];
				fontGeometry.getAdvance(advance, character, nextCharacter);

				x += fsScale * advance;
			}
		}
	}

}