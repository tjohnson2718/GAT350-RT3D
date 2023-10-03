#include "Renderer.h"
#include "Texture.h"
#include <SDL2-2.28.4/include/SDL_ttf.h>
#include <SDL2-2.28.4/include/SDL_image.h>

namespace nc
{
	bool Renderer::Initialize()
	{
		SDL_Init(SDL_INIT_VIDEO);
		IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
		TTF_Init();

		return true;
	}

	void Renderer::Shutdown()
	{
		SDL_GL_DeleteContext(m_context);
		SDL_DestroyWindow(m_window);
		TTF_Quit();
		IMG_Quit();
	}

	void Renderer::CreateWindow(const std::string& title, int width, int height)
	{
		m_width = width;
		m_height = height;

		m_window = SDL_CreateWindow(title.c_str(), 100, 100, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

		SDL_GL_SetSwapInterval(1);

		m_context = SDL_GL_CreateContext(m_window);
		gladLoadGL();

		glViewport(0, 0, width, height);
	}

	void Renderer::BeginFrame()
	{
		glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Renderer::EndFrame()
	{
		SDL_GL_SwapWindow(m_window);
	}

	void Renderer::SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
	{
		SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
	}

	void Renderer::DrawLine(int x1, int y1, int x2, int y2)
	{
		SDL_RenderDrawLine(m_renderer, x1, y1, x2, y2);
	}

	void Renderer::DrawLine(float x1, float y1, float x2, float y2)
	{
		SDL_RenderDrawLineF(m_renderer, x1, y1, x2, y2);
	}

	void Renderer::DrawPoint(int x, int y)
	{
		SDL_RenderDrawPoint(m_renderer, x, y);
	}

	void Renderer::DrawPoint(float x, float y)
	{
		SDL_RenderDrawPointF(m_renderer, x, y);
	}

	void Renderer::DrawTexture(Texture* texture, float x, float y, float angle)
	{
		vec2 size = texture->GetSize();

		SDL_Rect dest;
		dest.x = (int)(x - (size.x * 0.5f));
		dest.y = (int)(y - (size.y * 0.5f));
		dest.w = (int)size.x;
		dest.h = (int)size.y;

		// https://wiki.libsdl.org/SDL2/SDL_RenderCopyEx
		SDL_RenderCopyEx(m_renderer, texture->m_texture, nullptr, &dest, angle, nullptr, SDL_FLIP_NONE);
	}

	void Renderer::DrawTexture(Texture* texture, const Transform& transform)
	{
		mat3 mx = transform.GetMatrix();

		vec2 position = mx.GetTranslation();
		vec2 size = texture->GetSize() * mx.GetScale();

		SDL_Rect dest;
		dest.x = (int)(position.x - (size.x * 0.5f));
		dest.y = (int)(position.y - (size.y * 0.5f));
		dest.w = (int)size.x;
		dest.h = (int)size.y;

		// https://wiki.libsdl.org/SDL2/SDL_RenderCopyEx
		SDL_RenderCopyEx(m_renderer, texture->m_texture, nullptr, &dest, RadiansToDegrees(mx.GetRotation()), nullptr, SDL_FLIP_NONE);
	}

	void Renderer::DrawTexture(Texture* texture, const Rect& source, const Transform& transform)
	{
		mat3 mx = transform.GetMatrix();

		vec2 position = mx.GetTranslation();
		vec2 size = vec2{ source.w, source.h } * mx.GetScale();

		SDL_Rect dest;
		dest.x = (int)(position.x - (size.x * 0.5f));
		dest.y = (int)(position.y - (size.y * 0.5f));
		dest.w = (int)size.x;
		dest.h = (int)size.y;

		// https://wiki.libsdl.org/SDL2/SDL_RenderCopyEx
		SDL_RenderCopyEx(m_renderer, texture->m_texture, (SDL_Rect*)(&source), &dest, RadiansToDegrees(mx.GetRotation()), nullptr, SDL_FLIP_NONE);
	}

	void Renderer::DrawTexture(Texture* texture, const Rect& source, const Transform& transform, const vec2& origin, bool flipH)
	{
		mat3 mx = transform.GetMatrix();

		vec2 position = mx.GetTranslation();
		vec2 size = vec2{ source.w, source.h } *mx.GetScale();

		SDL_Rect dest;
		dest.x = (int)(position.x - (size.x * origin.x));
		dest.y = (int)(position.y - (size.y * origin.y));
		dest.w = (int)size.x;
		dest.h = (int)size.y;

		SDL_Point center{ (int)(size.x * origin.x), (int)(size.y * origin.y) };

		// https://wiki.libsdl.org/SDL2/SDL_RenderCopyEx
		SDL_RenderCopyEx(m_renderer, texture->m_texture, (SDL_Rect*)(&source), &dest, RadiansToDegrees(mx.GetRotation()), &center, (flipH) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
	}
}
