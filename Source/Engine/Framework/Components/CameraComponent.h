#pragma once
#include "Component.h"
#include "Renderer/Program.h"
#include "Renderer/Renderer.h"

namespace nc
{
	class CameraComponent : public Component
	{
	public:
		CLASS_DECLARATION(CameraComponent)

		bool Initialize() override;
		void Update(float dt) override;
		void ProcessGui() override;

		void SetPerspective(float fov, float aspect, float near, float far);
		void SetLookAt(const glm::vec3& eye, const glm::vec3& center, const glm::vec3& up = { 0, 1, 0 });

		void SetProgram(const res_t<Program> program);

	public:
		glm::mat4 projection{ 1 };
		glm::mat4 view{ 1 };

		float fov = 70.0f;
		float aspect = 0.0f;
		float near = 0.1f;
		float far = 100.0f;

		Renderer renderer;
	};
}
