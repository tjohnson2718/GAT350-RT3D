#include "GUI.h"
#include "Renderer.h"
#include "Framework/Engine.h"
#include <imgui/ImFileDialog.h>

namespace nc
{
	bool Gui::Initialize()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();

		ImGui_ImplSDL2_InitForOpenGL(ENGINE.GetSystem<Renderer>()->m_window, ENGINE.GetSystem<Renderer>()->m_context);
		const char* glsl_version = "#version 430";
		ImGui_ImplOpenGL3_Init(glsl_version);

		ImGui::StyleColorsDark();

		// ImFileDialog requires you to set the CreateTexture and DeleteTexture
		ifd::FileDialog::Instance().CreateTexture = [](uint8_t* data, int w, int h, char fmt) -> void*
			{
				GLuint texture = 0;

				glGenTextures(1, &texture);
				glBindTexture(GL_TEXTURE_2D, texture);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, (fmt == 0) ? GL_BGRA : GL_RGBA, GL_UNSIGNED_BYTE, data);
				glGenerateMipmap(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, 0);
				uintptr_t texID = texture;

				return (void*)(texID);
			};

		ifd::FileDialog::Instance().DeleteTexture = [](void* texID)
			{
				GLuint texture = (GLuint)((uintptr_t)texID);
				//glDeleteTextures(1, &texture);
			};

		return true;
	}

	void Gui::Shutdown()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();
	}

	void Gui::Update()
	{
		//
	}

	void Gui::BeginFrame()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();
	}

	void Gui::EndFrame()
	{
		ImGui::EndFrame();
	}

	void Gui::Draw()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void Gui::ProcessEvent(SDL_Event& event)
	{
		ImGui_ImplSDL2_ProcessEvent(&event);
	}
}