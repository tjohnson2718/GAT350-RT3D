#pragma once
#include "Framework/Resource/Resource.h"
#include "GUI.h"
#include <glm/glm/glm.hpp>
#include <vector>
#include <memory>

namespace nc
{
	class Texture;
	class Program;

	class Material : public Resource
	{
	public:
		const uint32_t ALBEDO_TEXTURE_MASK		= (1 << 0); // 00001
		const uint32_t SPECULAR_TEXTURE_MASK	= (1 << 1); // 00010
		const uint32_t NORMAL_TEXTURE_MASK		= (1 << 2); // 00100
		const uint32_t EMISSIVE_TEXTURE_MASK	= (1 << 3); // 01000
		const uint32_t CUBEMAP_TEXTURE_MASK		= (1 << 4); // 10000

	public:
		virtual bool Create(std::string filename, ...) override;

		void Bind();

		res_t<Program> GetProgram() { return m_program; }
		void ProcessGui();

	public:
		uint32_t params{ 0 };
		glm::vec3 albedo{ 1 };
		glm::vec3 specular{ 1 };
		glm::vec3 emissive{ 0 };
		float shininess = 2;


		glm::vec2 tiling{ 1, 1 };
		glm::vec2 offset{ 0 };

		res_t<Texture> albedoTexture;
		res_t<Texture> specularTexture;
		res_t<Texture> normalTexture;
		res_t<Texture> emissiveTexture;
		res_t<Texture> cubemapTexture;
		

	private:
		res_t<Program> m_program;
	};
}