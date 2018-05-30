#pragma once
#include <string>

class Config
{
public:
	std::string objectToLoad;

	void LoadFromFile(const std::string& path);
};

