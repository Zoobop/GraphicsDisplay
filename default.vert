#version 330 core

/** Position/Coordinates */
layout (location = 0) in vec3 aPos;
/** Colors */
layout (location = 1) in vec3 aColor;
/** Texture Coordinates */
layout (location = 2) in vec2 aTex;
/** Normals (not necessarily normalized) */
layout (location = 3) in vec3 aNormal;

/** Outputs the color of the Fragment Shader */
out vec3 color;
/** Outputs the texture coordinates of the Fragment Shader */
out vec2 texCoord;
/** Outputs the normals of the Fragment Shader */
out vec3 normal;
/** Outputs the current position */
out vec3 currentPos;

uniform mat4 camMatrix;
uniform mat4 model;

void main()
{
	currentPos = vec3(model * vec4(aPos, 1.0f));

	gl_Position = camMatrix * vec4(currentPos, 1.0);
	color = aColor;
	texCoord = aTex;
	normal = aNormal;
};