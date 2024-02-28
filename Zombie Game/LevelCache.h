#pragma once

#include "Level.h"

#include <map>
#include <string>

// Holds a cache of level information, handles loading 
class LevelCache
{
public:
	LevelCache();
	~LevelCache();
	// returns level and loads it into cache if it has not already been loaded in
	Level& load(const std::string& fp);

private:
	std::map<std::string, Level*> m_level_cache{};
};