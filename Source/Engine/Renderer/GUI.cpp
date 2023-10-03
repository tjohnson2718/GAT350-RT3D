#include "GUI.h"
#include "Renderer.h"
#include "Core/Logger.h"

namespace kiko
{
	GUI g_gui;

	bool GUI::Initialize(Renderer& renderer)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		// Setup Dear ImGui style
		ImGui::StyleColorsDark();

		// Setup Platform/Renderer backends
		if (!ImGui_ImplSDL2_InitForSDLRenderer(renderer.m_window, renderer.m_renderer))
		{
			ERROR_LOG("Could not create imgui.");
			return false;
		}

		if (!ImGui_ImplSDLRenderer_Init(renderer.m_renderer))
		{
			ERROR_LOG("Could not create imgui.");
			return false;
		}

		return true;
	}
	void GUI::Shutdown()
	{
		ImGui_ImplSDLRenderer_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();
	}

	void GUI::BeginFrame()
	{
		ImGui_ImplSDLRenderer_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();
	}

	void GUI::Draw()
	{
		ImGui::Render();
		ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
	}
}
