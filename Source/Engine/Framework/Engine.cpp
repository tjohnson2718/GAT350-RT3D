#include "Engine.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"

namespace nc
{
	bool Engine::Initialize()
	{
		// create systems
		m_systems.push_back(std::move(std::make_unique<Renderer>()));
		m_systems.push_back(std::move(std::make_unique<InputSystem>()));

		// initialize systems
		for (auto& system : m_systems)
		{
			system->Initialize();
		}

		GetSystem<Renderer>()->CreateWindow("GAT350", 800, 600);

		return true;
	}

	void Engine::Shutdown()
	{
		// shutdown systems
		for (auto& system : m_systems)
		{
			system->Shutdown();
		}

		m_systems.clear();
	}

	void Engine::Update()
	{
		// update sdl events
		SDL_Event event;
		SDL_PollEvent(&event);
		
		// update time
		m_time.Tick();

		// update systems
		for (auto& system : m_systems)
		{
			system->Update();
		}

		m_quit = GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_ESCAPE);
	}
}
