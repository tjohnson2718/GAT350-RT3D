#pragma once
#include "Framework/Object.h"

namespace nc
{
	class Component : public Object
	{
	public:
		virtual void Update(float dt) = 0;

		friend class Actor;

	public:
		class Actor* m_owner = nullptr;
	};
}

