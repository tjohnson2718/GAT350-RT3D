#pragma once
#include "Resource.h"
#include "Core/Logger.h"
#include "Core/StringUtils.h"
#include "Framework/Singleton.h"
#include <map>
#include <memory>
#include <string>
#include <vector>

#define GET_RESOURCE(type, filename, ...) nc::ResourceManager::Instance().Get<type>(filename, __VA_ARGS__)
#define GET_RESOURCES(type) nc::ResourceManager::Instance().GetAllOfType<type>();
#define ADD_RESOURCE(name, resource) nc::ResourceManager::Instance().Add(name, resource)

namespace nc
{
	// ResourceManager - Stores all currently loaded resources in a map
	// uses string (filename) as the key and a res_t (shared pointer) to the resource data
	// if the resource isn't in thre map, it is loaded/created and placed in the map
	class ResourceManager : public Singleton<ResourceManager>
	{
	public:
		template<typename T>
		bool Add(std::string name, res_t<T> resource);

		template<typename T, typename ... TArgs>
		res_t<T> Get(const std::string& filename, TArgs ... args);

		template<typename T>
		std::vector<res_t<T>> GetAllOfType();

	private:
		std::map<std::string, res_t<Resource>> m_resources;
	};

	template<typename T>
	inline bool ResourceManager::Add(std::string name, res_t<T> resource)
	{
		std::string lname = StringUtils::ToLowerCase(name);
		if (m_resources.find(lname) != m_resources.end())
		{
			WARNING_LOG("Resource already exists: " << lname);
			return false;
		}

		resource->name = lname;
		m_resources[lname] = resource;
		return true;
	}

	template<typename T, typename ...TArgs>
	inline res_t<T> ResourceManager::Get(const std::string& filename, TArgs ...args)
	{
		std::string lfilename = StringUtils::ToLowerCase(filename);
		// find resource in resources map
		if (m_resources.find(lfilename) != m_resources.end())
		{
			// return resource
			return std::dynamic_pointer_cast<T>(m_resources[lfilename]);
		}

		// resource not in resources map, create resource
		res_t<T> resource = std::make_shared<T>();
		if (!resource->Create(lfilename, args...))
		{
			// resource not created
			WARNING_LOG("Could not create resource: " << lfilename);
			return res_t<T>();
		}

		// add resource to resource map, return resource
		Add(lfilename, resource);
		return resource;
	}
	template<typename T>
	inline std::vector<res_t<T>> ResourceManager::GetAllOfType()
	{
		std::vector<res_t<T>> result;

		for (auto resource : m_resources)
		{
			auto res = std::dynamic_pointer_cast<T>(resource.second);
			if (res)
			{
				result.push_back(res);
			}
		}

		return result;
	}
}