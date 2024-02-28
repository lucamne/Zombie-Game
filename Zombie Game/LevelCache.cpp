#include "LevelCache.h"

#include <fstream>

LevelCache::LevelCache()
{
}

LevelCache::~LevelCache()
{
	for (auto iter : m_level_cache)
	{
		delete iter.second;
	}
}

Level& LevelCache::load(const std::string& fp)
{
	auto iter{ m_level_cache.find(fp) };
	if (iter != m_level_cache.end())
	{
		return *(iter->second);
	}

	Level* new_level{new Level()};
	new_level->load(fp);
	m_level_cache.emplace(fp, new_level);
	return *new_level;
}



