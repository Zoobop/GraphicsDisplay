#include "Shader.h"
#include <glm/gtc/type_ptr.inl>

namespace DevEngine::Graphics {

	Shader::Shader(const char* vertexPath, const char* fragmentPath) : m_VertexPath(vertexPath), m_FragmentPath(fragmentPath)
	{
		Load();
	}

	Shader::Shader()
	{

	}

	Shader::~Shader()
	{
		Delete();
	}

	GLuint Shader::GetShaderID()
	{
		return m_ShaderID;
	}

	void Shader::Activate()
	{
		/** Tell OpenGL which Shader Program we want to use */
		glUseProgram(m_ShaderID);
	}

	void Shader::Delete()
	{
		glDeleteProgram(m_ShaderID);
	}

	void Shader::CompileErrors(unsigned int shader, const char* type)
	{
		GLint hasCompiled;
		char infoLog[1024];
		if (type != "PROGRAM") {
			glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
			if (hasCompiled == GL_FALSE) {

				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "SHADER_COMPILATION_ERROR for: " << type << "\n" << std::endl;
			}
		}
		else {
			glGetProgramiv(shader, GL_COMPILE_STATUS, &hasCompiled);
			if (hasCompiled == GL_FALSE) {

				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "SHADER_LINKING_ERROR for: " << type << "\n" << std::endl;
			}
		}
	}

	void Shader::SetUniformVec2(const char* uniform, DVector2 vector)
	{
		glUniform2f(glGetUniformLocation(m_ShaderID, uniform), vector.x, vector.y);
	}

	void Shader::SetUniformVec3(const char* uniform, DVector3 vector)
	{
		glUniform3f(glGetUniformLocation(m_ShaderID, uniform), vector.x, vector.y, vector.z);
	}

	void Shader::SetUniformVec4(const char* uniform, DVector4 vector)
	{
		glUniform4f(glGetUniformLocation(m_ShaderID, uniform), vector.x, vector.y, vector.z, vector.w);
	}

	void Shader::SetUniformMat4(const char* uniform, DMatrix4 matrix)
	{
		glm::mat4 converted = matrix.ConvertToGLM();

		glUniformMatrix4fv(glGetUniformLocation(m_ShaderID, uniform), 1, GL_FALSE, glm::value_ptr(converted));
	}

	void Shader::Load()
	{
		std::string vertexCode = FileUtils::GetFileContents(m_VertexPath);
		std::string fragmentCode = FileUtils::GetFileContents(m_FragmentPath);

		const char* vertexSource = vertexCode.c_str();
		const char* fragmentSource = fragmentCode.c_str();

		/** Create Vertex Shader Object and get reference */
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		/** Attach Vertex Shader source to the Vertex Shader Object */
		glShaderSource(vertexShader, 1, &vertexSource, NULL);
		/** Compile the Vertex Shader into machine code */
		glCompileShader(vertexShader);
		CompileErrors(vertexShader, "VERTEX");

		/** Create Fragment Shader Object and get reference */
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		/** Attach Fragment Shader source to the Vertex Shader Object */
		glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
		/** Compile the Fragment Shader into machine code */
		glCompileShader(fragmentShader);
		CompileErrors(fragmentShader, "FRAGMENT");

		/** Create Shader Program Object and get its reference */
		m_ShaderID = glCreateProgram();
		/** Attach the Vertex and Fragment Shaders to the Shader Program */
		glAttachShader(m_ShaderID, vertexShader);
		glAttachShader(m_ShaderID, fragmentShader);
		/** Wrap-up/Link all the shaders together into the Shader Program */
		glLinkProgram(m_ShaderID);
		CompileErrors(m_ShaderID, "PROGRAM");

		/** Delete the now useless Vertex and Fragment Shader objects */
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

}