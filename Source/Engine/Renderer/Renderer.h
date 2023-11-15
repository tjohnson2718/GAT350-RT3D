#pragma once
#include "Framework/System.h"
#include "Font.h"
#include "Model.h"
#include "Texture.h"
#include "Cubemap.h"
#include "Shader.h"
#include "Program.h"
#include "Gui.h"
#include "VertexBuffer.h"
#include "Framebuffer.h"
#include "Material.h"

#include <glad/include/glad/glad.h>
#include <SDL2-2.28.4/include/SDL.h>
#include <string>

namespace nc
{
	class Renderer : public ISystem
	{
	public:
		Renderer() = default;
		~Renderer() = default;

		bool Initialize();
		void Shutdown();

		void Update() {}

		void CreateWindow(const std::string& title, int width, int height);
		void BeginFrame(const glm::vec3& color = glm::vec3{ 0 });
		void EndFrame();

		void ClearDepth();

		void SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
		void DrawLine(int x1, int y1, int x2, int y2);
		void DrawLine(float x1, float y1, float x2, float y2);
		void DrawPoint(int x, int y);
		void DrawPoint(float x, float y);

		void SetViewport(int width, int height);
		void ResetViewport();

		int GetWidth() const { return m_width; }
		int GetHeight() const { return m_height; }

		friend class Texture;
		friend class Gui;

	private:
		int m_width = 0;
		int m_height = 0;

		SDL_Renderer* m_renderer = nullptr;
		SDL_Window* m_window = nullptr;
		SDL_GLContext m_context = nullptr;
	};
}
