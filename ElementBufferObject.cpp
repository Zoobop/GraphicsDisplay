#include "ElementBufferObject.h"

ElementBufferObject::ElementBufferObject(std::vector<GLuint>& indices)
{
	glGenBuffers(1, &ID);
	/** Bind the Element Buffer Object specifying it's a GL_ELEMENT_ARRAY_BUFFER */
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	/** Introduce the indices into the Element Buffer Object */
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
}

void ElementBufferObject::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void ElementBufferObject::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void ElementBufferObject::Delete()
{
	glDeleteBuffers(1, &ID);
}
