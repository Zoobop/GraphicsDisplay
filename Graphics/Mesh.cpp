#include "Mesh.h"

namespace ZM { namespace Graphics {

	Mesh::Mesh(MeshData& meshData)
	{
		Texture textures[] = { n_TEXTURE_DEFAULT_DIFFUSE, n_TEXTURE_DEFAULT_SPECULAR };

		Mesh::textures = std::vector<Texture>(textures, textures + sizeof(textures) / sizeof(Texture));
		Mesh::vertices = meshData.meshV;
		Mesh::indices = meshData.meshI;

		Initialize();
	}

	Mesh::Mesh(MeshData& meshData, std::vector<Texture>& textures)
	{
		Mesh::textures = textures;
		Mesh::vertices = meshData.meshV;
		Mesh::indices = meshData.meshI;

		Initialize();
	}

	Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures)
	{
		Mesh::vertices = vertices;
		Mesh::indices = indices;
		Mesh::textures = textures;

		Initialize();
	}

	Mesh::Mesh()
	{

	}

	void Mesh::Draw(Shader& shader, Camera& camera, DMatrix4 matrix = DMatrix4::Identity(), DVector3 translation = DVector3::Zero(), glm::quat rotation = glm::quat(1.0f, 1.0f, 1.0f, 1.0f), DVector3 scale = DVector3::Identity())
	{
		shader.Activate();
		vao.Bind();

		unsigned int numDiffuse = 0;
		unsigned int numSpecular = 0;

		for (unsigned int i = 0; i < textures.size(); i++) {

			std::string num;
			std::string type = textures[i].type;
			if (type == "diffuse") {
				num = std::to_string(numDiffuse++);
			}
			else if (type == "specular") {
				num = std::to_string(numSpecular++);
			}
			textures[i].TexUnit(shader, (type + num).c_str(), i);
			textures[i].Bind();
		}

		glUniform3f(glGetUniformLocation(shader.GetShaderID(), "camPos"), camera.position.x, camera.position.y, camera.position.z);
		camera.Matrix(shader, "camMatrix");

		glm::mat4 trans(1.0f);
		glm::mat4 rot(1.0f);
		glm::mat4 scl(1.0f);

		trans = glm::translate(trans, translation.ConvertToGLM());
		rot = glm::mat4_cast(rotation);
		scl = glm::scale(scl, scale.ConvertToGLM());

		glUniformMatrix4fv(glGetUniformLocation(shader.GetShaderID(), "translation"), 1, GL_FALSE, glm::value_ptr(trans));
		glUniformMatrix4fv(glGetUniformLocation(shader.GetShaderID(), "rotation"), 1, GL_FALSE, glm::value_ptr(rot));
		glUniformMatrix4fv(glGetUniformLocation(shader.GetShaderID(), "scale"), 1, GL_FALSE, glm::value_ptr(scl));
		shader.SetUniformMat4("model", matrix);

		glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, 0);
	}

	void Mesh::Initialize()
	{
		vao.Bind();

		/** Generates Vertex Buffer Object and links it to vertices */
		VertexBuffer vbo(vertices);
		/** Generates Element Buffer Object and links it to indices */
		ElementBufferObject ebo(indices);

		/** Links vbo to vao */
		vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
		vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
		vao.LinkAttrib(vbo, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
		vao.LinkAttrib(vbo, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));
		/** Unbind all to prevent accidentally modifying them */
		vao.Unbind();
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
}}
