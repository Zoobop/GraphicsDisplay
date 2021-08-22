#pragma once

#include <glad/glad.h>
#include "VertexBuffer.h"

namespace ZM { namespace Graphics {

	class VertexArray
	{
	public:

		GLuint m_ArrayID;
		VertexArray();

		void LinkAttrib(VertexBuffer& vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizei stride, void* offset);
		void Bind();
		void Unbind();
		void Delete();

	};
}}