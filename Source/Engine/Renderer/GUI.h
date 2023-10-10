#pragma once
#include "Framework/System.h"
#include <imgui/imgui_impl_sdl.h>
#include <imgui/imgui_impl_opengl3.h>
#include <SDL2-2.28.4/include/SDL.h>

namespace nc
{
	class Renderer;

	class Gui : public ISystem
	{
	public:
		Gui() = default;
		~Gui() = default;

		bool Initialize() override;
		void Shutdown() override;
		void Update() override;

		void BeginFrame();
		void EndFrame();
		void Draw();

		void ProcessEvent(SDL_Event& event);
	};
}
