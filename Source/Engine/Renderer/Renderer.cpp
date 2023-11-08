#include "Renderer.h"
#include "Texture.h"
#include <SDL2-2.28.4/include/SDL_ttf.h>
#include <SDL2-2.28.4/include/SDL_image.h>

namespace nc
{
	void APIENTRY DebugCallback(GLenum source, GLenum type, GLuint id,
		GLenum severity, GLsizei length, const GLchar* message, const void* param);

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

		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(DebugCallback, 0);

		// disable all messages with severity `GL_DEBUG_SEVERITY_NOTIFICATION`
		glDebugMessageControl(
			GL_DONT_CARE,
			GL_DONT_CARE,
			GL_DEBUG_SEVERITY_NOTIFICATION,
			0, NULL,
			GL_FALSE);

		glViewport(0, 0, width, height);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);
	}

	void Renderer::BeginFrame(const glm::vec3& color)
	{
		glDepthMask(GL_TRUE);
		glClearColor(color.r, color.g, color.b, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

	void Renderer::SetViewport(int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	void Renderer::ResetViewport()
	{
		glViewport(0, 0, m_width, m_height);
	}



	void APIENTRY DebugCallback(GLenum source, GLenum type, GLuint id,
		GLenum severity, GLsizei length, const GLchar* message, const void* param) {

		std::string sourceString;
		switch (source)
		{
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
			sourceString = "WindowSys";
			break;
		case GL_DEBUG_SOURCE_APPLICATION:
			sourceString = "App";
			break;
		case GL_DEBUG_SOURCE_API:
			sourceString = "OpenGL";
			break;
		case GL_DEBUG_SOURCE_SHADER_COMPILER:
			sourceString = "ShaderCompiler";
			break;
		case GL_DEBUG_SOURCE_THIRD_PARTY:
			sourceString = "3rdParty";
			break;
		case GL_DEBUG_SOURCE_OTHER:
			sourceString = "Other";
			break;
		default:
			sourceString = "Unknown";
		}

		std::string typeString;
		switch (type)
		{
		case GL_DEBUG_TYPE_ERROR:
			typeString = "Error";
			break;
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
			typeString = "Deprecated";
			break;
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
			typeString = "Undefined";
			break;
		case GL_DEBUG_TYPE_PORTABILITY:
			typeString = "Portability";
			break;
		case GL_DEBUG_TYPE_PERFORMANCE:
			typeString = "Performance";
			break;
		case GL_DEBUG_TYPE_MARKER:
			typeString = "Marker";
			break;
		case GL_DEBUG_TYPE_PUSH_GROUP:
			typeString = "PushGrp";
			break;
		case GL_DEBUG_TYPE_POP_GROUP:
			typeString = "PopGrp";
			break;
		case GL_DEBUG_TYPE_OTHER:
			typeString = "Other";
			break;
		default:
			typeString = "Unknown";
		}

		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:
			ASSERT_LOG(0, "OPENGL Source: " << sourceString << " Type: " << typeString << "(" << id << ") | " << message);
			break;
		case GL_DEBUG_SEVERITY_MEDIUM:
			ERROR_LOG("OPENGL Source: " << sourceString << " Type: " << typeString << "(" << id << ") | " << message);
			break;
		case GL_DEBUG_SEVERITY_LOW:
			WARNING_LOG("OPENGL Source: " << sourceString << " Type: " << typeString << "(" << id << ") | " << message);
			break;
		case GL_DEBUG_SEVERITY_NOTIFICATION:
			INFO_LOG("OPENGL Source: " << sourceString << " Type: " << typeString << "(" << id << ") | " << message);
			break;
		}
	}
}
