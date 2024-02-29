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
	static void load(const std::string& fp);
	// draws active level
	static void draw(TRXEngine::SpriteBatch& sprite_batch);
	
	//getters
	// get starting player position from active level
	static glm::vec2 getInitPlayerPosition();
	// get starting zombie position from active level
	static glm::vec2 getInitZombiePosition();
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

