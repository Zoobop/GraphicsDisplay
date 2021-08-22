#pragma once

#include <JSON/json.h>
#include "Mesh.h"

using json = nlohmann::json;

namespace DevEngine::Graphics {

#define DevM_UNSIGNED_INT 5125
#define DevM_UNSIGNED_SHORT 5123
#define DevM_SHORT 5122

	class Model
	{
	public:
		Model(const char* filePath);

		void Draw(Shader& shader, Camera& camera);

	private:

		void LoadMesh(unsigned int indMesh);
		void TraverseNode(unsigned int nextNode, DMatrix4 matrix = DMatrix4::Identity());

		std::vector<unsigned char> GetData();
		std::vector<float> GetFloats(json accessor);
		std::vector<GLuint> GetIndices(json accessor);
		std::vector<Texture> GetTextures();

		std::vector<Vertex> AssembleVertices(std::vector<DVector3> positions, std::vector<DVector3> normals, std::vector<DVector2> texUVs);

		std::vector<DVector2> GroupFloatsVec2(std::vector<float> floatVec);
		std::vector<DVector3> GroupFloatsVec3(std::vector<float> floatVec);
		std::vector<DVector4> GroupFloatsVec4(std::vector<float> floatVec);

	private:
		const char* m_FilePath;
		std::vector<unsigned char> m_Data;
		json m_JSON;

		std::vector<std::string> m_LoadedTexNames;
		std::vector<Texture> m_LoadedTex;

		std::vector<Mesh> m_LoadedMeshes;
		std::vector<DVector3> m_TranslationsMeshes;
		std::vector<DQuaternion> m_RotationsMeshes;
		std::vector<DVector3> m_ScalesMeshes;
		std::vector<DMatrix4> m_MatricesMeshes;
	};

}