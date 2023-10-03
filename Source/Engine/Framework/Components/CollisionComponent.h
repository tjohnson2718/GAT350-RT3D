#pragma once
#include "Component.h"

namespace nc
{
	class CollisionComponent : public Component
	{
	public:
		virtual bool CheckCollision(CollisionComponent* collision) { return true; }

	public:
		float m_radius = 0;
	};
}