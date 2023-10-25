#pragma once
#include "Component.h"

namespace nc
{
	class RenderComponent : public Component
	{
	public:
		virtual void Draw(class Renderer& renderer) = 0;
	};
}
