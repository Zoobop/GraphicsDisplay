#version 330 core
out vec4 FragColor;

/** Imports the color from the Vertex Shader */
in vec3 color;
/** Imports the texture coordinates from the Vertex Shader */
in vec2 texCoord;
/** Imports the normal from the Vertex Shader */
in vec3 normal;
/** Imports the current position from the Vertex Shader */
in vec3 currentPos;

/** Gets the Texture Unit from the main function */
uniform sampler2D tex0;

uniform sampler2D tex1;
/** Gets the color of the light from the main function */
uniform vec4 lightColor;
/** Gets the position of the light from the main function */
uniform vec3 lightPos;
/** Gets the position of the camera from the main function */
uniform vec3 camPos;

void main()
{
	/** Amibent lighting */
	float ambient = 0.10f;

	/** Diffuse lighting */
	vec3 Normal = normalize(normal);
	vec3 lightDirection = normalize(lightPos - currentPos);
	float diffuse = max(dot(Normal, lightDirection), 0.0f);

	/** Specular lighting */
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - currentPos);
	vec3 reflectionDirection = reflect(-lightDirection, Normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	FragColor = texture(tex0, texCoord) * lightColor * (diffuse + ambient) + texture(tex1, texCoord).r * specular;
};