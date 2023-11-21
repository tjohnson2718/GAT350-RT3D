#pragma once
#include "Framework/System.h"
#include <imgui/imgui_impl_sdl.h>
#include <imgui/imgui_impl_opengl3.h>
#include <SDL2-2.28.4/include/SDL.h>
#include <imgui/imconfig.h>
#include "Core/FileIO.h"
#include "Framework/Resource/ResourceManager.h"
#include <imgui/ImFileDialog.h>
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

		template<typename T>
		static bool GetDiologResource(res_t<T>& resource, const std::string& dialogName, const std::string& title, const std::string& filetype);
	};

	template<typename T>
	inline bool Gui::GetDiologResource(res_t<T>& resource, const std::string& dialogName, const std::string& title, const std::string& filetype)
	{
		if (ImGui::IsItemClicked(0))
		{
			ifd::FileDialog::Instance().Open(dialogName, title, filetype, false);
		}
		if (ifd::FileDialog::Instance().IsDone(dialogName))
		{
			if (ifd::FileDialog::Instance().HasResult())
			{
				auto resourceName = getRelativePath(ifd::FileDialog::Instance().GetResult());
				resource = GET_RESOURCE(T, resourceName);
			}
			ifd::FileDialog::Instance().Close();
			return true;
		}

		return false;
	}
}
