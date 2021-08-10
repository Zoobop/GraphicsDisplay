#version 330 core

/** Outputs colors in RGBA */
out vec4 FragColor;

/** Imports the current position from the Vertex Shader */
in vec3 currentPos;
/** Imports the normal from the Vertex Shader */
in vec3 normal;
/** Imports the color from the Vertex Shader */
in vec3 color;
/** Imports the texture coordinates from the Vertex Shader */
in vec2 texCoord;

/** Gets the Texture Unit from the main function */
uniform sampler2D diffuse0;
uniform sampler2D specular0;
/** Gets the color of the light from the main function */
uniform vec4 lightColor;
/** Gets the position of the light from the main function */
uniform vec3 lightPos;
/** Gets the position of the camera from the main function */
uniform vec3 camPos;

vec4 PointLight()
{
	vec3 lightVec = lightPos - currentPos;
	float distance = length(lightVec);
	float a = 3.0f;
	float b = 0.7f;
	float intensity = 1.0f / (a * distance * distance + b * distance + 1.0f);

	/** Amibent lighting */
	float ambient = 0.10f;

	/** Diffuse lighting */
	vec3 Normal = normalize(normal);
	vec3 lightDirection = normalize(lightVec);
	float diffuse = max(dot(Normal, lightDirection), 0.0f);

	/** Specular lighting */
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - currentPos);
	vec3 reflectionDirection = reflect(-lightDirection, Normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	return (texture(diffuse0, texCoord) * (diffuse * intensity + ambient) + texture(specular0, texCoord).r * specular * intensity) * lightColor;
}

vec4 DirectionLight()
{
	/** Amibent lighting */
	float ambient = 0.10f;

	/** Diffuse lighting */
	vec3 Normal = normalize(normal);
	vec3 lightDirection = normalize(vec3(1.0f, 1.0f, 0.0f));
	float diffuse = max(dot(Normal, lightDirection), 0.0f);

	/** Specular lighting */
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - currentPos);
	vec3 reflectionDirection = reflect(-lightDirection, Normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	return (texture(diffuse0, texCoord) * (diffuse + ambient) + texture(specular0, texCoord).r * specular) * lightColor;
}

vec4 SpotLight()
{
	float outerCone = 0.90f;
	float innerCone = 0.95f;
	
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

	float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDirection);
	float intensity = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

	return (texture(diffuse0, texCoord) * (diffuse * intensity + ambient) + texture(specular0, texCoord).r * specular * intensity) * lightColor;
}

void main()
{
	/** Outputs the final color */
	FragColor = SpotLight();
};