#version 330 core

/** Position/Coordinates */
layout (location = 0) in vec3 aPos;
/** Normals (not necessarily normalized) */
layout (location = 1) in vec3 aNormal;
/** Colors */
layout (location = 2) in vec3 aColor;
/** Texture Coordinates */
layout (location = 3) in vec2 aTex;

/** Outputs the current position */
out vec3 currentPos;
/** Outputs the normals of the Fragment Shader */
out vec3 normal;
/** Outputs the color of the Fragment Shader */
out vec3 color;
/** Outputs the texture coordinates of the Fragment Shader */
out vec2 texCoord;

/** Imports the camera matrix from the main function */
uniform mat4 camMatrix;
/** Imports the model matrix from the main function */
uniform mat4 model;
uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;

void main()
{
	/** Calculates current position */
	currentPos = vec3(model * translation * -rotation * scale * vec4(aPos, 1.0f));
	/** Assigns the normal from the Vertex Data to "normal" */
	normal = aNormal;
	/** Assigns the colors from the Vertex Data to "color" */
	color = aColor;
	/** Assigns the texture coordinates from the Vertex Data to "texCoord" */
	texCoord = mat2(0.0f, -1.0f, 1.0f, 0.0f) * aTex;
	/** Outputs the positions/coordinates of all vertices */
	gl_Position = camMatrix * vec4(currentPos, 1.0);
};