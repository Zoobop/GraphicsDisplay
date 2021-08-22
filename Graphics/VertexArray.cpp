#include "VertexArray.h"

namespace DevEngine::Graphics {

	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_ArrayID);
	}

	void VertexArray::LinkAttrib(VertexBuffer& vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizei stride, void* offset)
	{
		vbo.Bind();
		glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
		glEnableVertexAttribArray(layout);
		vbo.Unbind();

	}

	void VertexArray::Bind()
	{
		glBindVertexArray(m_ArrayID);
	}

	void VertexArray::Unbind()
	{
		glBindVertexArray(0);
	}

	void VertexArray::Delete()
	{
		glDeleteVertexArrays(1, &m_ArrayID);
	}
}