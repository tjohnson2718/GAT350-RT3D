#include "FileIO.h"
#include "Logger.h"
#include <fstream>
#include <iostream>

namespace nc
{
	std::string getFilePath()
	{
		return std::filesystem::current_path().string();
	}

	bool setFilePath(const std::filesystem::path& path)
	{
		std::error_code ec;
		std::filesystem::current_path(path, ec);

		return ec.value() == 0;
	}

	std::string getFileName(const std::filesystem::path& path)
	{
		return path.filename().string();
	}

	std::string getRelativePath(const std::filesystem::path& path)
	{
		return std::filesystem::relative(path).string();
	}

	bool fileExists(const std::filesystem::path& path)
	{
		return std::filesystem::exists(path);
	}

	bool getFileSize(const std::filesystem::path& path, size_t& size)
	{
		std::error_code ec;
		size = std::filesystem::file_size(path, ec);

		return ec.value() == 0;
	}

	bool readFile(const std::filesystem::path& path, std::string& buffer)
	{
		if (!fileExists(path))
		{
			WARNING_LOG("File not loaded: " << path.string());
			return false;
		}

		size_t size;
		if (!getFileSize(path, size)) 
		{
			WARNING_LOG("File size is 0: " << path.string());
			return false;
		}

		buffer.resize(size);
				
		std::ifstream stream(path);
		stream.read(buffer.data(), size);
		stream.close();

		return true;
	}
}
