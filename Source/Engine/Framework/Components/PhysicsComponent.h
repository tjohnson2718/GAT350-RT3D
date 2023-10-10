#pragma once
#include "Component.h"
#include "Core/Math/Vector2.h"
#include <glm/glm/glm.hpp>

namespace nc
{
	class PhysicsComponent : public Component
	{
	public:
		virtual void ApplyForce(const glm::vec3& force) = 0;
		virtual void ApplyTorque(float torque) = 0;

		virtual void SetPosition(const glm::vec3& position) {};
		virtual void SetVelocity(const glm::vec3& velocity) { this->velocity = velocity; }
		virtual void SetGravityScale(float scale) {}

	public:
		glm::vec3 velocity;
		glm::vec3 acceleration;
		float mass = 1.0f;
		float damping = 0;
	};
}
