#pragma once
#include "Component.h"

namespace kiko
{
	class ScriptComponent : public Component
	{
	public:
		virtual void OnCollision(Actor* other) = 0;
	};
}