#pragma once

#include <glad/glad.h>
#include <vector>

namespace DevEngine::Graphics {

	class ElementBufferObject
	{
	public:
		GLuint ID;
		ElementBufferObject(std::vector<GLuint>& indices);

		void Bind();
		void Unbind();
		void Delete();

	};
}