#pragma once
#include "Framework/World.h"
#include "Renderer/Renderer.h"


namespace nc
{
	class World03 : public World
	{
	public:
		bool Initialize() override;
		void Shutdown() override;
		void Update(float dt) override;
		void Draw(Renderer& renderer) override;

	private:
		float m_time;
		float m_speed = 5;

		Transform m_transform;

		GLuint m_vao;
		res_t<Program> m_program;
		res_t<Texture> m_texture;
	};
}