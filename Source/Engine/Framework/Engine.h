#pragma once
#include "Core/Time.h"

#include "System.h"
#include "Singleton.h"
#include <vector>
#include <memory>

#define ENGINE nc::Engine::Instance()

namespace nc
{
	// A singleton to manage engine systems and engine related functionality.
	class Engine : public Singleton<Engine>
	{
	public:
		bool Initialize();
		void Shutdown();

		void Update();

		bool IsQuit() { return m_quit; }

		friend class Singleton;

		// Returns a pointer to a system using the system type (example: GetSystem<Renderer>())
		template <typename T>
		T* GetSystem();

		Time& GetTime() { return m_time; }

	private:
		Engine() {}

	private:
		bool m_quit = false;
		std::vector<std::unique_ptr<ISystem>> m_systems;
		Time m_time;
	};

	template<typename T>
	inline T* Engine::GetSystem()
	{
		for (auto& system : m_systems)
		{
			T* s = dynamic_cast<T*>(system.get());
			if (s) return s;
		}

		return nullptr;
	}
}