#pragma once
#include "Actor.h"
#include <list>

namespace nc
{
	class Renderer;

	// Manages Actors in the scene which can be loaded and read from a JSON file.
	class Scene
	{
	public:
		Scene() = default;

		bool Initialize();
		void Update(float dt);
		void Draw(Renderer& renderer);

		void Add(std::unique_ptr<Actor> actor);
		void RemoveAll(bool force = false);

		bool Load(const std::string& filename);
		void Read(const json_t& value);

		template<typename T>
		T* GetActor();
		template<typename T = Actor>
		T* GetActorByName(const std::string& name);

		void SetGame(World* game) { m_game = game; }

		friend class Actor;

	private:
		World* m_game = nullptr;
		std::list<std::unique_ptr<Actor>> m_actors;
	};

	template<typename T>
	inline T* Scene::GetActor()
	{
		for (auto& actor : m_actors)
		{
			T* result = dynamic_cast<T*>(actor.get());
			if (result) return result;
		}

		return nullptr;
	}

	template<typename T>
	inline T* Scene::GetActorByName(const std::string& name)
	{
		for (auto& actor : m_actors)
		{
			if (actor->name == name)
			{
				T* result = dynamic_cast<T*>(actor.get());
				if (result) return result;
			}
		}

		return nullptr;
	}


}