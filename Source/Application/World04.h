#pragma once
#include "Framework/World.h"
#include "Renderer/Renderer.h"
#include "Core/Math/Transform.h"
#include <vector>


namespace nc
{
	class World04 : public World
	{
	public:
		bool Initialize() override;
		void Shutdown() override;
		void Update(float dt) override;
		void Draw(Renderer& renderer) override;

	private:
		float m_time;
		float m_speed = 5;

		glm::vec3 m_lightPosition{ 0.0f, 0.8f, 0.0f };
		glm::vec3 m_lightColor{ 1.0f, 1.0f, 1.0f };
		glm::vec3 m_ambientLighting{ 0.2f, 0.2f, 0.2f };

		Transform m_transform;
		res_t<Model> m_model;
		//res_t<Material> m_material;
	};
}