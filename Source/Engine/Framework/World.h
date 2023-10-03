#pragma once
#include <memory>

namespace nc
{
	class Scene;
	class Renderer;

	// An abstract class that contains the scene and methods to initialize, shutdown, update and draw the world.
	class World
	{
	public:
		World() = default;
		virtual ~World() = default;

		virtual bool Initialize() = 0;
		virtual void Shutdown() = 0;

		virtual void Update(float dt) = 0;
		virtual void Draw(Renderer& renderer) = 0;

		bool IsQuit() const { return m_quit; }

	protected:
		bool m_quit = false;
		std::unique_ptr<Scene> m_scene;
	};
}
