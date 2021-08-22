#include "Mesh.h"
#include "../Engine/Utils/DebugUtils.h"

namespace DevEngine::Graphics {

	Mesh::Mesh(MeshData& meshData)
		: m_Indices(meshData.meshI), m_Vertices(meshData.meshV)
	{
		Texture textures[] = { n_TEXTURE_DEFAULT_DIFFUSE, n_TEXTURE_DEFAULT_SPECULAR };

		m_Textures = std::vector<Texture>(textures, textures + sizeof(textures) / sizeof(Texture));

		Initialize();
	}

	Mesh::Mesh(MeshData& meshData, std::vector<Texture>& textures)
		: m_Indices(meshData.meshI), m_Vertices(meshData.meshV), m_Textures(textures)
	{
		Initialize();
	}

	Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures)
		: m_Vertices(vertices), m_Indices(indices), m_Textures(textures)
	{
		Initialize();
	}

	Mesh::Mesh()
	{

	}

	void Mesh::Draw
	(
		Shader& shader,
		Camera& camera, 
		DMatrix4 matrix, 
		DVector3 translation, 
		DQuaternion rotation, 
		DVector3 scale
	)
	{
		shader.Activate();
		m_VAO.Bind();

		unsigned int numDiffuse = 0;
		unsigned int numSpecular = 0;

		for (unsigned int i = 0; i < m_Textures.size(); i++) {

			std::string num;
			std::string type = m_Textures[i].type;
			if (type == "diffuse") {
				num = std::to_string(numDiffuse++);
			}
			else if (type == "specular") {
				num = std::to_string(numSpecular++);
			}
			m_Textures[i].TexUnit(shader, (type + num).c_str(), i);
			m_Textures[i].Bind();
		}

		shader.SetUniformVec3("camPos", camera.m_Position);
		camera.Matrix(shader, "camMatrix");

		glm::mat4 trans = glm::translate(translation.ConvertToGLM());
		glm::mat4 rot = glm::mat4_cast(rotation.ConvertToGLM());
		glm::mat4 scl = glm::scale(scale.ConvertToGLM());

		shader.SetUniformMat4("translation", trans);
		shader.SetUniformMat4("rotation", rot);
		shader.SetUniformMat4("scale", scl);
		shader.SetUniformMat4("model", matrix.ConvertToGLM());

		glDrawElements(GL_TRIANGLES, (GLsizei)m_Indices.size(), GL_UNSIGNED_INT, 0);
	}

	void Mesh::Initialize()
	{
		m_VAO.Bind();

		/** Generates Vertex Buffer Object and links it to vertices */
		VertexBuffer vbo(m_Vertices);
		/** Generates Element Buffer Object and links it to indices */
		ElementBufferObject ebo(m_Indices);

		/** Links vbo to vao */
		m_VAO.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
		m_VAO.LinkAttrib(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
		m_VAO.LinkAttrib(vbo, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
		m_VAO.LinkAttrib(vbo, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));
		/** Unbind all to prevent accidentally modifying them */
		m_VAO.Unbind();
		vbo.Unbind();
		ebo.Unbind();
	}

	MeshData::MeshData(const Vertex vertices[], const GLuint indices[])
	{
		MeshData::meshV = std::vector<Vertex>(vertices, vertices + sizeof(*vertices) / sizeof(Vertex));
		MeshData::meshI = std::vector<GLuint>(indices, indices + sizeof(*indices) / sizeof(GLuint));
	}

	MeshData::MeshData()
	{

	}

	MeshData& MeshData::CubeMesh()
	{
		Vertex cubeV[] = {
			/**  Coordinates  */
			Vertex{DVector3(-0.1f, -0.1f,  0.1f)},
			Vertex{DVector3(-0.1f, -0.1f, -0.1f)},
			Vertex{DVector3(0.1f,  -0.1f, -0.1f)},
			Vertex{DVector3(0.1f,  -0.1f,  0.1f)},
			Vertex{DVector3(-0.1f,  0.1f,  0.1f)},
			Vertex{DVector3(-0.1f,  0.1f, -0.1f)},
			Vertex{DVector3(0.1f,   0.1f, -0.1f)},
			Vertex{DVector3(0.1f,   0.1f,  0.1f)},
		};
		GLuint cubeI[] = {
			0, 1, 2,
			0, 2, 3,
			0, 4, 7,
			0, 7, 3,
			3, 7, 6,
			3, 6, 2,
			2, 6, 5,
			2, 5, 1,
			1, 5, 4,
			1, 4, 0,
			4, 5, 6,
			4, 6, 7,
		};

		MeshData::meshV = std::vector<Vertex>(cubeV, cubeV + sizeof(cubeV) / sizeof(Vertex));
		MeshData::meshI = std::vector<GLuint>(cubeI, cubeI + sizeof(cubeI) / sizeof(GLuint));

		return *this;
	}

	MeshData& MeshData::PlaneMesh()
	{
		Vertex planeV[] = {
			/**  Coordinates     |         Colors       | Texture Coords |        Normals       */
			Vertex{DVector3(-1.0f, 0.0f,  1.0f), DVector3(0.0f, 1.0f, 0.0f), DVector3(1.0f, 1.0f, 1.0f), DVector2(0.0f, 0.0f)},
			Vertex{DVector3(-1.0f, 0.0f, -1.0f), DVector3(0.0f, 1.0f, 0.0f), DVector3(1.0f, 1.0f, 1.0f), DVector2(0.0f, 1.0f)},
			Vertex{DVector3(1.0f, 0.0f,  -1.0f), DVector3(0.0f, 1.0f, 0.0f), DVector3(1.0f, 1.0f, 1.0f), DVector2(1.0f, 1.0f)},
			Vertex{DVector3(1.0f, 0.0f,   1.0f), DVector3(0.0f, 1.0f, 0.0f), DVector3(1.0f, 1.0f, 1.0f), DVector2(1.0f, 0.0f)},
		};
		GLuint planeI[] = {
			0, 1, 2,	// Bottom side
			0, 2, 3,	// Bottom side
		};

		MeshData::meshV = std::vector<Vertex>(planeV, planeV + sizeof(planeV) / sizeof(Vertex));
		MeshData::meshI = std::vector<GLuint>(planeI, planeI + sizeof(planeI) / sizeof(GLuint));

		return *this;
	}

	MeshData& MeshData::PyramidMesh()
	{
		Vertex pyramidV[] = {
		Vertex{DVector3(-0.5f, 0.0f, 0.5f), DVector3(0.83f, 0.70f, 0.44f), DVector3(0.0f, 0.0f, 0.0f), DVector2(-1.0f, 0.0f)}, // Bottom side
		Vertex{DVector3(-0.5f, 0.0f, -0.5f), DVector3(0.83f, 0.70f, 0.44f), DVector3(0.0f, 5.0f, 0.0f), DVector2(-1.0f, 0.0f)}, // Bottom side
		Vertex{DVector3(0.5f, 0.0f, -0.5f), DVector3(0.83f, 0.70f, 0.44f), DVector3(5.0f, 5.0f, 0.0f), DVector2(-1.0f, 0.0f)}, // Bottom side
		Vertex{DVector3(0.5f, 0.0f, 0.5f), DVector3(0.83f, 0.70f, 0.44f), DVector3(5.0f, 0.0f, 0.0f), DVector2(-1.0f, 0.0f)}, // Bottom side

		Vertex{DVector3(-0.5f, 0.0f, 0.5f), DVector3(0.83f, 0.70f, 0.44f), DVector3(0.0f, 0.0f, -0.8f), DVector2(0.5f, 0.0f)}, // Left side
		Vertex{DVector3(-0.5f, 0.0f, -0.5f), DVector3(0.83f, 0.70f, 0.44f), DVector3(5.0f, 0.0f, -0.8f), DVector2(0.5f, 0.0f)}, // Left side
		Vertex{DVector3(0.0f, 0.8f, 0.0f), DVector3(0.92f, 0.86f, 0.76f), DVector3(2.5f, 5.0f, -0.8f), DVector2(0.5f, 0.0f)}, // Left side

		Vertex{DVector3(-0.5f, 0.0f, -0.5f), DVector3(0.83f, 0.70f, 0.44f), DVector3(5.0f, 0.0f, 0.0f), DVector2(0.5f, -0.8f)}, // Non-facing side
		Vertex{DVector3(0.5f, 0.0f, -0.5f), DVector3(0.83f, 0.70f, 0.44f), DVector3(0.0f, 0.0f, 0.0f), DVector2(0.5f, -0.8f)}, // Non-facing side
		Vertex{DVector3(0.0f, 0.8f, 0.0f), DVector3(0.92f, 0.86f, 0.76f), DVector3(2.5f, 5.0f, 0.0f), DVector2(0.5f, -0.8f)}, // Non-facing side

		Vertex{DVector3(0.5f, 0.0f, -0.5f), DVector3(0.83f, 0.70f, 0.44f), DVector3(0.0f, 0.0f, 0.8f), DVector2(0.5f, 0.0f)}, // Right side
		Vertex{DVector3(0.5f, 0.0f, 0.5f), DVector3(0.83f, 0.70f, 0.44f), DVector3(5.0f, 0.0f, 0.8f), DVector2(0.5f, 0.0f)}, // Right side
		Vertex{DVector3(0.0f, 0.8f, 0.0f), DVector3(0.92f, 0.86f, 0.76f), DVector3(2.5f, 5.0f, 0.8f), DVector2(0.5f, 0.0f)}, // Right side

		Vertex{DVector3(0.5f, 0.0f, 0.5f), DVector3(0.92f, 0.86f, 0.76f), DVector3(5.0f, 0.0f, 0.0f), DVector2(0.5f, 0.8f)}, // Facing side
		Vertex{DVector3(-0.5f, 0.0f, 0.5f), DVector3(0.92f, 0.86f, 0.76f), DVector3(0.0f, 0.0f, 0.0f), DVector2(0.5f, 0.8f)}, // Facing side
		Vertex{DVector3(0.0f, 0.8f, 0.0f), DVector3(0.92f, 0.86f, 0.76f), DVector3(2.5f, 5.0f, 0.0f), DVector2(0.5f, 0.8f)}, // Facing side
		};
		GLuint pyramidI[] = {
			0, 1, 2,	// Bottom side
			0, 2, 3,	// Bottom side
			4, 6, 5,	// Left side
			7, 9, 8,	// Non-facing side
			10, 12, 11,	// Right side
			13, 15, 14,	// Facing side
		};

		MeshData::meshV = std::vector<Vertex>(pyramidV, pyramidV + sizeof(pyramidV) / sizeof(Vertex));
		MeshData::meshI = std::vector<GLuint>(pyramidI, pyramidI + sizeof(pyramidI) / sizeof(GLuint));

		return *this;
	}
}
