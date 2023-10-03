#pragma once
#include "Component.h"
#include "Core/Math/Vector2.h"

namespace nc
{
	class PhysicsComponent : public Component
	{
	public:
		virtual void ApplyForce(const vec2& force) = 0;
		virtual void ApplyTorque(float torque) = 0;

		virtual void SetPosition(const vec2& position) {};
		virtual void SetVelocity(const vec2& velocity) { this->velocity = velocity; }
		virtual void SetGravityScale(float scale) {}

	public:
		vec2 velocity;
		vec2 acceleration;
		float mass = 1.0f;
		float damping = 0;
	};
}
