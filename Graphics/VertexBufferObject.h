#ifndef VERTEX_BUFFER_OBJECT_CLASS_H
#define VERTEX_BUFFER_OBJECT_CLASS_H

#include <vector>

#include <glm/glm.hpp>
#include <glad/glad.h>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
	glm::vec2 texUV;
};

class VertexBufferObject
{
public:
	GLuint ID;
	VertexBufferObject(std::vector<Vertex>& vertices);

	void Bind();
	void Unbind();
	void Delete();

};

#endif
