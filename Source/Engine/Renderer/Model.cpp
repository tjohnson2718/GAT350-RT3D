#include "Model.h"
#include "Core/Core.h"
#include "Framework/Resource/ResourceManager.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


namespace nc
{
	bool Model::Create(std::string filename, ...)
	{
		// TODO load json model file

		return Load(filename);
	}

	bool Model::Load(const std::string& filename, const glm::vec3& translate, const glm::vec3& rotation, const glm::vec3& scale)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			WARNING_LOG("Could not load assimp file %s" << importer.GetErrorString());
			return false;
		}

		glm::mat4 mt = glm::translate(translate);
		glm::mat4 mr = glm::eulerAngleYXZ(glm::radians(rotation.y), glm::radians(rotation.x), glm::radians(rotation.z));
		glm::mat4 ms = glm::scale(scale);

		glm::mat4 mx = mt * mr * ms;
		ProcessNode(scene->mRootNode, scene, mt);

		return true;
	}

	void Model::Draw(GLenum primitive)
	{
		m_material->Bind();
		m_vertexBuffer->Draw(primitive);
	}

	void Model::ProcessNode(aiNode* node, const aiScene* scene, const glm::mat4& transform)
	{
		// process the current node meshes
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			ProcessMesh(mesh, scene, transform);
		}
		// process the current node children
		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			ProcessNode(node->mChildren[i], scene, transform);
		}
	}

	void Model::ProcessMesh(aiMesh* mesh, const aiScene* scene, const glm::mat4& transform)
	{
		std::vector<vertex_t> vertices;

		// get model vertex attributes
		for (size_t i = 0; i < mesh->mNumVertices; i++)
		{
			vertex_t vertex;

			vertex.position = transform * glm::vec4{ mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z, 1 };
			vertex.normal = transform * glm::vec4{ mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z, 0 };

			if (mesh->mTangents)
			{
				vertex.tangent = transform * glm::vec4{ mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z, 0 };
			}
			else
			{
				vertex.tangent = { 0, 0, 0 };
			}

			if (mesh->mTextureCoords[0])
			{
				vertex.texcoord = { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y };
			}
			else
			{
				vertex.texcoord = { 0, 0 };
			}

			vertices.push_back(vertex);
		}

		// create vertex buffer and attributes
		m_vertexBuffer = std::make_shared<VertexBuffer>();
		m_vertexBuffer->CreateVertexBuffer((GLsizei)(sizeof(vertex_t) * vertices.size()), (GLsizei)vertices.size(), vertices.data());
		m_vertexBuffer->SetAttribute(0, 3, sizeof(vertex_t), 0);
		m_vertexBuffer->SetAttribute(1, 2, sizeof(vertex_t), offsetof(vertex_t, texcoord));
		m_vertexBuffer->SetAttribute(2, 3, sizeof(vertex_t), offsetof(vertex_t, normal));
		m_vertexBuffer->SetAttribute(3, 3, sizeof(vertex_t), offsetof(vertex_t, tangent));

		// get model index vertices
		std::vector<GLuint> indices;
		for (size_t i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (size_t j = 0; j < face.mNumIndices; j++)
			{
				indices.push_back(face.mIndices[j]);
			}
		}

		// create index vertex buffer
		m_vertexBuffer->CreateIndexBuffer(GL_UNSIGNED_INT, (GLsizei)indices.size(), indices.data());
	}
}