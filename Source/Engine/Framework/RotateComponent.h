#pragma once
#include "Components/Component.h"
#include <glm/glm/glm.hpp>

namespace nc
{
	class RotateComponent : public Component
	{
	public:
		CLASS_DECLARATION(RotateComponent)
		bool Initialize() override;
		void Update(float dt) override;
		void ProcessGui() override;


	public:
		glm::vec3 euler{ 0 };
	};
}

