#include "Config.h"
#include <fstream>

void Config::LoadFromFile(const std::string& path)
{
	std::string line;
	std::ifstream file(path);
	if (file.is_open())
	{
		while (getline(file, line))
		{
			int trim = line.find("object_to_load");
			if (trim >= 0)
			{
				objectToLoad = line.substr(trim + 15);
			}	
		}
		file.close();
	}
}