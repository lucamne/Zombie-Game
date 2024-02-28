#pragma once

#include "LevelCache.h"

#include <TRXEngine/SpriteBatch.h>

#include <glm/glm.hpp>

#include <string>

// manages an instance of levelCache
class LevelManager
{
public:
	// loads level from filepath and sets active level
	static void load(const std::string& fp) { m_active_level = &(m_level_cache.load(fp)); }
	// draws active level
	static void draw(TRXEngine::SpriteBatch& sprite_batch) { m_active_level->draw(sprite_batch); }
	// get starting player position from active level
	static glm::vec2 getInitPlayerPosition() { return m_active_level->getInitPlayerPosition(); }
	// get starting zombie position from active level
	static glm::vec2 getInitZombiePosition() { return m_active_level->getInitZombiePosition(); }

private:
	static LevelCache m_level_cache;
	// pointer to currently active level
	static Level* m_active_level;
};

Level* LevelManager::m_active_level{};
