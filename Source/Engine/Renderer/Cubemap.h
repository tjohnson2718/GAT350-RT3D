#pragma once
#include "Texture.h"
#include <vector>

namespace nc
{
	class Cubemap : public Texture
	{
	public:
		bool Create(std::string filename, ...) override;
		bool Load(const std::vector<std::string>& filenames);
	};
}