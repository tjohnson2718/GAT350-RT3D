#pragma once

namespace nc
{
	// Abstract class (Interface) for all engine systems (Renderer, Input System, Audio System, ...)
	class ISystem
	{
	public:
		virtual bool Initialize() = 0;
		virtual void Shutdown() = 0;
		virtual void Update() = 0;
	};
}
