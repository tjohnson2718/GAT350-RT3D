#pragma once
#include "Framework/Resource/Resource.h"
#include "VertexBuffer.h"
#include "Material.h"

struct aiNode;
struct aiMesh;
struct aiScene;

namespace nc
{
	class Model : public Resource
	{
	public:
		// vertex attributes
		struct vertex_t
		{
			glm::vec3 position;
			glm::vec2 texcoord;
			glm::vec3 normal;
			glm::vec3 tangent;
		};

	public:
		bool Create(std::string filename, ...) override;
		bool Load(const std::string& filename, const glm::vec3& translate = glm::vec3(0), const glm::vec3& rotation = glm::vec3(0), const glm::vec3& scale = glm::vec3(1));
		void Draw(GLenum primitive = GL_TRIANGLES);

	private:
		void ProcessNode(aiNode* node, const aiScene* scene, const glm::mat4& transform);
		void ProcessMesh(aiMesh* mesh, const aiScene* scene, const glm::mat4& transform);

	private:
		res_t<VertexBuffer> m_vertexBuffer;
	};
}