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
	
	//getters
	// get starting player position from active level
	static glm::vec2 getInitPlayerPosition() { return m_active_level->getInitPlayerPosition(); }
	// get starting zombie position from active level
	static glm::vec2 getInitZombiePosition() { return m_active_level->getInitZombiePosition(); }
	// get vector of starting human positions
	static const std::vector<glm::vec2>& getInitHumanPositions() { return m_active_level->getInitHumanPositions(); }
	// get raw level data
	static const Level& getLevelData() { return *m_active_level; }

	// setters
	// set tile width of active level
	static void setTileWidth(int width) { m_active_level->setTileWidth(width); }
	static void setTileHeight(int height) { m_active_level->setTileHeight(height); }


private:
	static LevelCache m_level_cache;
	// pointer to currently active level
	static Level* m_active_level;
};

