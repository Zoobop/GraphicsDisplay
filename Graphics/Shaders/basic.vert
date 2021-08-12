#version 330 core

layout (location = 0) in vec4 position;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix = mat4(1.0f);
uniform mat4 modelMatrix = mat4(1.0f);

void main()
{
	gl_Position = position; 
}