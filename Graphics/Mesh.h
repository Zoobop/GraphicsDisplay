#pragma once

#include <string>
#include <vector>

#include "VertexArray.h"
#include "ElementBuffer.h"
#include "Camera.h"
#include "Texture.h"

#define MESH_CUBE MeshData().CubeMesh()
#define MESH_PLANE MeshData().PlaneMesh()
#define MESH_PYRAMID MeshData().PyramidMesh()
#define MESH_SPHERE MeshData()


namespace ZM { namespace Graphics {

	class MeshData
	{
	public:
		MeshData();
		MeshData(const Vertex vertices[], const GLuint indices[]);

		MeshData& CubeMesh();
		MeshData& PlaneMesh();
		MeshData& PyramidMesh();

	public:
		std::vector<Vertex> meshV;
		std::vector<GLuint> meshI;
	};



	class Mesh
	{
	public:
		Mesh();
		Mesh(MeshData& meshData);
		Mesh(MeshData& meshData, std::vector<Texture>& textures);
		Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures);

		void Draw(Shader& shader, Camera& camera, DMatrix4 matrix = DMatrix4::Identity(), DVector3 translation = DVector3::Zero(), glm::quat rotation = glm::quat(1.0f, 1.0f, 1.0f, 1.0f), DVector3 scale = DVector3::Identity());

	protected:

		void Initialize();

	public:

		std::vector<Vertex> vertices;
		std::vector<GLuint> indices;
		std::vector<Texture> textures;

		VertexArray vao;

	protected:


	};
}}
