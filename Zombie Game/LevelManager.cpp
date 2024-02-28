#include "LevelManager.h"

LevelCache LevelManager::m_level_cache{};
Level* LevelManager::m_active_level{};

void LevelManager::load(const std::string& fp) { m_active_level = &(m_level_cache.load(fp)); }
void LevelManager::draw(TRXEngine::SpriteBatch& sprite_batch) { m_active_level->draw(sprite_batch); }
glm::vec2 LevelManager::getInitPlayerPosition() { return m_active_level->getInitPlayerPosition(); }
glm::vec2 LevelManager::getInitZombiePosition() { return m_active_level->getInitZombiePosition(); }