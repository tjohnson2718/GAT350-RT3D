#pragma once
#include <filesystem>
#include <string>

namespace nc
{
	// Returns the file path of the current directory. (example: C:\Project\Code)
	std::string getFilePath();
	// Set current directory file path, can be relative to current directory.
	bool setFilePath(const std::filesystem::path& path);
	// Returns the filename excluding the path directories. (example: C:Project\Code\main.cpp -> main.cpp)
	std::string getFileName(const std::filesystem::path& path);

	// Returns (true/false) if a file exists.
	bool fileExists(const std::filesystem::path& path);
	// Sets the size of the file in size parameter, returns (true/false) if successful.
	bool getFileSize(const std::filesystem::path& path, size_t& size);
	// Reads the file as text into the buffer parameter, returns (true/false) if successful.
	bool readFile(const std::filesystem::path& path, std::string& buffer);
}
