#pragma once

#include <vector>

#include <glm/glm.hpp>
#include <glad/glad.h>

namespace ZM { namespace Graphics {

	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec3 color;
		glm::vec2 texUV;
	};

	class VertexBuffer
	{
	public:
		VertexBuffer(std::vector<Vertex>& vertices);

		void Bind() const;
		void Unbind() const;
		void Delete() const;

	private:
		GLuint m_BufferID;
	};

}}
