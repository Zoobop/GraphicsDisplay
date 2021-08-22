#include "Model.h"
#include "../Engine/Utils/FileUtils.h"

namespace ZM { namespace Graphics {

	Model::Model(const char* filePath)
	{
		std::string text = FileUtils::GetFileContents(filePath);
		m_JSON = json::parse(text);

		m_FilePath = filePath;
		m_Data = GetData();
	}

	void Model::Draw(Shader& shader, Camera& camera)
	{

	}

	void Model::LoadMesh(unsigned int indMesh)
	{
		unsigned int posAccInd = m_JSON["meshes"][indMesh]["primitives"][0]["attributes"]["POSITION"];
		unsigned int normalAccInd = m_JSON["meshes"][indMesh]["primitives"][0]["attributes"]["NORMAL"];
		unsigned int texAccInd = m_JSON["meshes"][indMesh]["primitives"][0]["attributes"]["TEXCOORD_0"];
		unsigned int indAccInd = m_JSON["meshes"][indMesh]["primitives"][0]["attributes"]["indices"];

		std::vector<float> posVec = GetFloats(m_JSON["accessors"][posAccInd]);
		std::vector<DVector3> positions = GroupFloatsVec3(posVec);

		std::vector<float> normalVec = GetFloats(m_JSON["accessors"][normalAccInd]);
		std::vector<DVector3> normals = GroupFloatsVec3(normalVec);

		std::vector<float> texVec = GetFloats(m_JSON["accessors"][texAccInd]);
		std::vector<DVector2> texUVs = GroupFloatsVec2(texVec);

		std::vector<Vertex> vertices = AssembleVertices(positions, normals, texUVs);
		std::vector<GLuint> indices = GetIndices(m_JSON["accessors"][indAccInd]);
		std::vector<Texture> textures = GetTextures();

		m_LoadedMeshes.push_back(Mesh(vertices, indices, textures));
	}

	void Model::TraverseNode(unsigned int nextNode, DMatrix4 matrix /*= DMatrix4::Identity()*/)
	{
		json node = m_JSON["nodes"][nextNode];

		DVector3 translation = DVector3::Zero();
		if (node.find("translation") != node.end()) {

			float transValues[3];
			for (unsigned int i = 0; i < node["translation"].size(); i++) {

				transValues[i] = (node["translation"][i]);
			}

			translation = glm::make_vec3(transValues);
		}

		glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
		if (node.find("rotation") != node.end()) {

			float rotValues[4] = {

				node["rotation"][3],
				node["rotation"][0],
				node["rotation"][1],
				node["rotation"][2],
			};
			rotation = glm::make_quat(rotValues);
		}

		DVector3 scale = DVector3::Identity();
		if (node.find("scale") != node.end()) {

			float scaleValues[3];
			for (unsigned int i = 0; i < node["scale"].size(); i++) {

				scaleValues[i] = (node["scale"][i]);
			}

			scale = glm::make_vec3(scaleValues);
		}

		DMatrix4 matNode(1.0f);
		if (node.find("matrix") != node.end()) {

			float matValues[16];
			for (unsigned int i = 0; i < node["matrix"].size(); i++) {

				matValues[i] = (node["matrix"][i]);
			}

			matNode = DMatrix4(matValues);
		}

		DMatrix4 trans(1.0f);
		glm::mat4 rot(1.0f);
		DMatrix4 scl(1.0f);

		trans = DMatrix4::Translate(translation);
		rot = glm::mat4_cast(rotation);
		scl = DMatrix4::Scale(scale);

		glm::mat4 matNextNode = matrix.ConvertToGLM() * matNode.ConvertToGLM() * trans.ConvertToGLM() * rot * scl.ConvertToGLM();

		if (node.find("mesh") != node.end()) {

			m_TranslationsMeshes.push_back(translation);
			m_RotationsMeshes.push_back(rotation);
			m_ScalesMeshes.push_back(scale);
			m_MatricesMeshes.push_back(matNextNode);

			LoadMesh(node["mesh"]);
		}

		if (node.find("children") != node.end()) {

			for (unsigned int i = 0; i < node["children"].size(); i++) {

				//TraverseNode(node["children"][i], matNextNode);
			}
		}
	}

	std::vector<unsigned char> Model::GetData()
	{
		std::string bytesText;
		std::string uri = m_JSON["buffer"][0]["uri"];

		std::string fileStr = std::string(m_FilePath);
		std::string fileDirectory = fileStr.substr(0, fileStr.find_last_of('/') + 1);
		bytesText = FileUtils::GetFileContents((fileDirectory + uri).c_str());

		std::vector<unsigned char> data(bytesText.begin(), bytesText.end());
		return data;
	}

	std::vector<float> Model::GetFloats(json accessor)
	{
		std::vector<float> floatVec;

		unsigned int buffViewInd = accessor.value("bufferView", 1);
		unsigned int count = accessor["count"];
		unsigned int accByteOffset = accessor.value("byteOffset", 0);
		std::string type = accessor["type"];

		json bufferView = m_JSON["bufferViews"][buffViewInd];
		unsigned int byteOffset = bufferView["byteOffset"];

		unsigned int numPerVert;
		if (type == "SCALAR") numPerVert = 1;
		else if (type == "VEC2") numPerVert = 2;
		else if (type == "VEC3") numPerVert = 3;
		else if (type == "VEC4") numPerVert = 4;
		else throw std::invalid_argument("Type is invalid (not SCALAR, VEC2, VEC3, VEC4)");

		unsigned int beginningOfData = byteOffset + accByteOffset;
		unsigned int lengthOfData = count * 4 * numPerVert;
		for (unsigned int i = beginningOfData; i < beginningOfData + lengthOfData; i) {

			unsigned char bytes[] = { m_Data[i++], m_Data[i++], m_Data[i++], m_Data[i++], m_Data[i++] };
			float value;
			std::memcpy(&value, bytes, sizeof(float));
			floatVec.push_back(value);
		}

		return floatVec;
	}

	std::vector<GLuint> Model::GetIndices(json accessor)
	{
		std::vector<GLuint> indices;

		unsigned int buffViewInd = accessor.value("bufferView", 1);
		unsigned int count = accessor["count"];
		unsigned int accByteOffset = accessor.value("byteOffset", 0);
		unsigned int componentType = accessor["componentType"];

		json bufferView = m_JSON["bufferViews"][buffViewInd];
		unsigned int byteOffset = bufferView["byteOffset"];

		unsigned int beginningOfData = byteOffset + accByteOffset;
		if (componentType == DevM_UNSIGNED_INT) {

			for (unsigned int i = beginningOfData; i < byteOffset + accByteOffset + count * 2; i) {

				unsigned char bytes[] = { m_Data[i++], m_Data[i++], m_Data[i++], m_Data[i++] };
				unsigned int value;
				std::memcpy(&value, bytes, sizeof(unsigned int));
				indices.push_back((GLuint)value);
			}
		}
		else if (componentType == DevM_UNSIGNED_SHORT) {

			for (unsigned int i = beginningOfData; i < byteOffset + accByteOffset + count * 2; i) {

				unsigned char bytes[] = { m_Data[i++], m_Data[i++] };
				unsigned short value;
				std::memcpy(&value, bytes, sizeof(unsigned short));
				indices.push_back((GLuint)value);
			}
		}
		else if (componentType == DevM_SHORT) {

			for (unsigned int i = beginningOfData; i < byteOffset + accByteOffset + count * 2; i) {

				unsigned char bytes[] = { m_Data[i++], m_Data[i++] };
				short value;
				std::memcpy(&value, bytes, sizeof(short));
				indices.push_back((GLuint)value);
			}
		}

		return indices;
	}

	std::vector<Texture> Model::GetTextures()
	{
		std::vector<Texture> textures;

		std::string fileStr = std::string(m_FilePath);
		std::string fileDirectory = fileStr.substr(0, fileStr.find_last_of('/') + 1);
		
		unsigned int unit = 0;
		for (unsigned int i = 0; i < m_JSON["images"].size(); i++) {

			std::string texPath = m_JSON["images"][i]["uri"];

			bool skip = false;
			for (unsigned int j = 0; j < m_LoadedTexNames.size(); j++) {

				if (m_LoadedTexNames[j] == texPath) {

					textures.push_back(m_LoadedTex[j]);
					skip = true;
					break;
				}
			}

			if (!skip) {

				if (texPath.find("baseColor") != std::string::npos) {
					Texture diffuse = Texture((fileDirectory + texPath).c_str(), "diffuse", (unsigned int)m_LoadedTex.size());
					textures.push_back(diffuse);
					m_LoadedTex.push_back(diffuse);
					m_LoadedTexNames.push_back(texPath);
				}
				else if (texPath.find("metallicRoughness") != std::string::npos) {
					Texture specular = Texture((fileDirectory + texPath).c_str(), "specular", (unsigned int)m_LoadedTex.size());
					textures.push_back(specular);
					m_LoadedTex.push_back(specular);
					m_LoadedTexNames.push_back(texPath);
				}
			}
		}

		return textures;
	}

	std::vector<Vertex> Model::AssembleVertices(std::vector<DVector3> positions, std::vector<DVector3> normals, std::vector<DVector2> texUVs)
	{
		std::vector<Vertex> vertices;
		for (int i = 0; i < positions.size(); i++) {

			vertices.push_back
			(
				Vertex
				{
					positions[i],
					normals[i],
					DVector3::Identity(),
					texUVs[i]
				}
			);
		}

		return vertices;
	}

	std::vector<DVector2> Model::GroupFloatsVec2(std::vector<float> floatVec)
	{
		std::vector<DVector2> vectors;
		for (int i = 0; i < floatVec.size(); i) {

			vectors.push_back(DVector2(floatVec[i++], floatVec[i++]));
		}

		return vectors;
	}

	std::vector<DVector3> Model::GroupFloatsVec3(std::vector<float> floatVec)
	{
		std::vector<DVector3> vectors;
		for (int i = 0; i < floatVec.size(); i) {

			vectors.push_back(DVector3(floatVec[i++], floatVec[i++], floatVec[i++]));
		}

		return vectors;
	}

	std::vector<DVector4> Model::GroupFloatsVec4(std::vector<float> floatVec)
	{
		std::vector<DVector4> vectors;
		for (int i = 0; i < floatVec.size(); i) {

			vectors.push_back(DVector4(floatVec[i++], floatVec[i++], floatVec[i++], floatVec[i++]));
		}

		return vectors;
	}

}}