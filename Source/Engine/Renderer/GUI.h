#pragma once
#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl.h>
#include <imgui/imgui_impl_sdlrenderer.h>

namespace kiko
{
	class GUI
	{
	public:
		bool Initialize(class Renderer& renderer);
		void Shutdown();

		void BeginFrame();
		void Draw();
	};

	extern GUI g_gui;
}