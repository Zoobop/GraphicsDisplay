#pragma once

#include <glad/glad.h>
#include <string>
#include <iostream>

#include "../Engine/Utils/FileUtils.h"

using namespace ZM::Utils;

namespace ZM { namespace Graphics {

	class Shader
	{
	public:
		Shader(const char* vertexPath, const char* fragmentPath);
		~Shader();

		GLuint GetShaderID();

		void Activate();
		void Delete();

		void CompileErrors(unsigned int shader, const char* type);

	private:
		void Load();

	private:
		GLuint m_ShaderID;
		const char* m_VertexPath;
		const char* m_FragmentPath;
	};

}}