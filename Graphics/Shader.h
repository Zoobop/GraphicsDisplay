#pragma once

#include <glad/glad.h>
#include <string>
#include <iostream>

#include "../Engine/Utils/FileUtils.h"
#include "../Math/DevMath.h"

using namespace DevEngine::Utils;
using namespace DevEngine::Math;

namespace DevEngine::Graphics {

#define SHADER_FILE_PATH "Graphics/Shaders/"

	class Shader
	{
	public:
		Shader();
		Shader(const char* vertexPath, const char* fragmentPath);
		~Shader();

		GLuint GetShaderID();

		void Activate();
		void Delete();

		void CompileErrors(unsigned int shader, const char* type);

		void SetUniformVec2(const char* uniform, DVector2 vector);
		void SetUniformVec3(const char* uniform, DVector3 vector);
		void SetUniformVec4(const char* uniform, DVector4 vector);

		void SetUniformMat4(const char* uniform, DMatrix4& matrix);
		void SetUniformMat4(const char* uniform, glm::mat4 matrix);

	private:
		void Load();

	private:
		GLuint m_ShaderID;
		const char* m_VertexPath;
		const char* m_FragmentPath;
	};

}