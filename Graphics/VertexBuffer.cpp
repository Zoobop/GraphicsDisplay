#include "VertexBuffer.h"

namespace DevEngine::Graphics {

	VertexBuffer::VertexBuffer(std::vector<Vertex>& vertices)
	{
		glGenBuffers(1, &m_BufferID);
		/** Bind the Vertex Buffer Object specifying it's a GL_ARRAY_BUFFER */
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
		/** Introduce the vertices into the Vertex Buffer Object */
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
	}

	void VertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	}

	void VertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void VertexBuffer::Delete() const
	{
		glDeleteBuffers(1, &m_BufferID);
	}
}