#pragma once
#include "Resource.h"
#include "Core/Logger.h"
#include "Framework/Singleton.h"
#include <map>
#include <memory>
#include <string>

#define GET_RESOURCE(type, filename, ...) nc::ResourceManager::Instance().Get<type>(filename, __VA_ARGS__)

namespace nc
{
	// ResourceManager - Stores all currently loaded resources in a map
	// uses string (filename) as the key and a res_t (shared pointer) to the resource data
	// if the resource isn't in thre map, it is loaded/created and placed in the map
	class ResourceManager : public Singleton<ResourceManager>
	{
	public:
		template<typename T, typename ... TArgs>
		res_t<T> Get(const std::string& filename, TArgs ... args);

	private:
		std::map<std::string, res_t<Resource>> m_resources;
	};

	template<typename T, typename ...TArgs>
	inline res_t<T> ResourceManager::Get(const std::string& filename, TArgs ...args)
	{
		// find resource in resources map
		if (m_resources.find(filename) != m_resources.end())
		{
			// return resource
			return std::dynamic_pointer_cast<T>(m_resources[filename]);
		}

		// resource not in resources map, create resource
		res_t<T> resource = std::make_shared<T>();
		if (!resource->Create(filename, args...))
		{
			// resource not created
			WARNING_LOG("Could not create resource: " << filename);
			return res_t<T>();
		}

		// add resource to resource map, return resource
		m_resources[filename] = resource;
		return resource;
	}
}