#pragma once

#include <string>
#include <vector>
#include "core/Base.h"


namespace Arkitect {
	enum class ShaderDataType {
		None = 0, Bool, Float, Float2, Float3, Float4, Int, Int2, Int3, Int4, Mat2, Mat3, Mat4
	};

	uint32_t CalculateSizeOfDataType(ShaderDataType type) {
		switch (type)
		{
		case ShaderDataType::Float:    return sizeof(float);
		case ShaderDataType::Float2:   return sizeof(float) * 2;
		case ShaderDataType::Float3:   return sizeof(float) * 3;
		case ShaderDataType::Float4:   return sizeof(float) * 4;
		case ShaderDataType::Mat2:     return sizeof(float) * 2 * 2;
		case ShaderDataType::Mat3:     return sizeof(float) * 3 * 3;
		case ShaderDataType::Mat4:     return sizeof(float) * 4 * 4;
		case ShaderDataType::Int:      return sizeof(int);
		case ShaderDataType::Int2:     return sizeof(int) * 2;
		case ShaderDataType::Int3:     return sizeof(int) * 3;
		case ShaderDataType::Int4:     return sizeof(int) * 4;
		case ShaderDataType::Bool:     return sizeof(bool);
		}

		RKT_CORE_CRITICAL("Unknown shader data type!");
		return 0;
	}

	struct LayoutElement {
		std::string Name;
		ShaderDataType Type;
		uint32_t Size;
		size_t Offset;
		bool Normalized;

		LayoutElement() = default;
		LayoutElement(ShaderDataType type, std::string name, bool normalized = false)
			:Name(name), Type(type), Size(CalculateSizeOfDataType(type)), Offset(0), Normalized(normalized)
		{
		}

		uint32_t GetElementCount(ShaderDataType type) {
			switch (type)
			{
			case ShaderDataType::Float:    return 1;
			case ShaderDataType::Float2:   return 2;
			case ShaderDataType::Float3:   return 3;
			case ShaderDataType::Float4:   return 4;
			case ShaderDataType::Mat2:     return 2 * 2;
			case ShaderDataType::Mat3:     return 3 * 3;
			case ShaderDataType::Mat4:     return 4 * 4;
			case ShaderDataType::Int:      return 1;
			case ShaderDataType::Int2:     return 2;
			case ShaderDataType::Int3:     return 3;
			case ShaderDataType::Int4:     return 4;
			case ShaderDataType::Bool:     return 1;
			}

			RKT_CORE_CRITICAL("Unknown shader data type!");
			return 0;
		}
	};

	class BufferLayout {
	public:
		BufferLayout() {}
		BufferLayout(std::initializer_list<LayoutElement>& elements) :
			m_Elements(elements)
		{
			CalculateElementsData();
		}
	private:
		void CalculateElementsData() {
			size_t offset = 0;
			for (LayoutElement& element : m_Elements) {
				m_Stride += element.Size;
				element.Offset = offset;
				offset += element.Size;
			}
		}
		std::vector<LayoutElement> m_Elements;
		uint32_t m_Stride = 0;
	};

	class VertexBuffer {
	public:
		VertexBuffer(uint32_t size);
		VertexBuffer(const void* datt ,uint32_t size);

		void Bind() const;
		void Unbind() const;

		const BufferLayout& GetLayout() const { return m_Layout; }
		void SetLayout(const BufferLayout& layout) const { m_Layout = layout; }
	private:
		uint32_t m_RendererID;
		BufferLayout m_Layout;
	};
}
