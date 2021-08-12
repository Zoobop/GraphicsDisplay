#include "VertexBufferObject.h"

VertexBufferObject::VertexBufferObject(std::vector<Vertex>& vertices)
{
	glGenBuffers(1, &ID);
	/** Bind the Vertex Buffer Object specifying it's a GL_ARRAY_BUFFER */
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	/** Introduce the vertices into the Vertex Buffer Object */
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
}

void VertexBufferObject::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VertexBufferObject::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBufferObject::Delete()
{
	glDeleteBuffers(1, &ID);
}
