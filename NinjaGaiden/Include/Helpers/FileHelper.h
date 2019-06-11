#pragma once

#include <string>

class FileHelper final
{
	FileHelper() = delete;
	~FileHelper() = delete;

public:
	static std::string ReadString(const std::string& filePath);
};
