#pragma once

#include <glad/glad.h>
#include <stb/stb_image.h>

#include "Shader.h"


#define TT_DIFFUSE		"diffuse"
#define TT_SPECULAR		"specular"

#define n_TEXTURE_DEFAULT_DIFFUSE		Texture("planks.png", TT_DIFFUSE, 0)
#define n_TEXTURE_DEFAULT_SPECULAR		Texture("planksSpec.png", TT_SPECULAR, 1)

namespace DevEngine::Graphics {

	class Texture
	{
	public:

		Texture(const char* image, const char* texType, GLuint slot);

		void TexUnit(Shader& shader, const char* uniform, GLuint unit);
		void Bind();
		void Unbind();
		void Delete();

	public:
		GLuint ID;
		const char* type;
		GLuint unit;
	};
}
