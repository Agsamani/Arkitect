#pragma once

#include <functional>

#include "renderer/Texture.h"
#include "renderer/Font.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace Arkitect {

	struct TransformComponent {
		glm::vec3 Translation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;

		glm::mat4 GetTransform() {
			return glm::translate(glm::mat4(1.0f), Translation)
				* glm::toMat4(glm::quat(Rotation))
				* glm::scale(glm::mat4(1.0f), Scale);
		}
	};

	struct SpriteComponent {
		glm::vec4 Color = { 1.0f, 1.0f, 1.0f, 1.0f };
		std::shared_ptr<Texture2D> Texture;
		float TilingFactor = 1.0f;

		SpriteComponent() = default;
		SpriteComponent(const SpriteComponent&) = default;
		SpriteComponent(const glm::vec4& color)
			:Color(color) {}
	};

	
	// Physics
	struct RigidBody2DComponent {
		enum class BodyType { Static = 0, Dynamic, Kinematic };
		BodyType Type = BodyType::Static;
		bool FixedRotation = false;

		void* RuntimeBody;

		RigidBody2DComponent() = default;
		RigidBody2DComponent(const RigidBody2DComponent&) = default;
	};

	struct BoxCollider2DComponent {
		glm::vec2 Size = { 0.5, 0.5 };
		glm::vec2 Offset = { 0.0, 0.0 };

		float Density = 1.0f;
		float Friction = 0.5f;
		float Restitution = 0.0f;
		float RestitutionThreshold = 0.5f;

		BoxCollider2DComponent() = default;
		BoxCollider2DComponent(const BoxCollider2DComponent&) = default;
	};

	// TODO: Circle collider

	// Scripts
	class ScriptableEntity;

	struct ScriptComponent {
		ScriptableEntity* instance = nullptr;

		std::function<void()> InstantiateScript;
		std::function<void()> DestroyScript;

		template<typename T, typename... Args> // May have bugs?
		void Bind(Args&&... args) {

			InstantiateScript = [&]() {
				instance = static_cast<ScriptableEntity*>(new T(std::forward<Args>(args)...));
			};

			DestroyScript = [&]() {
				delete instance;
				instance = nullptr;
			};

		}
	};

	// Text
	struct TextComponent {
		std::string TextString;
		std::shared_ptr<Font> FontAsset = Font::GetDefault();
		glm::vec4 Color{ 1.0f };
		float Kerning = 0.0f;
		float LineSpacing = 0.0f;
	};
}