#pragma once

#include <vector>

#include <glm/glm.hpp>
#include <glad/glad.h>

#include "../Math/DVector2.h"
#include "../Math/DVector3.h"

using namespace DevEngine::Math;

namespace DevEngine::Graphics {

	struct Vertex
	{
		DVector3 position;
		DVector3 normal;
		DVector3 color;
		DVector2 texUV;
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

}
