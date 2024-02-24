#include "Enemy.h"

#include <TRXEngine/ResourceManager.h>
#include <TRXEngine/Vertex.h>

Enemy::Enemy(std::string path_to_texture, glm::vec2 position, int width, int height)
	:m_state{ENEMY_STATE::ALIVE},
	m_position{ position },
	m_width{ width },
	m_height{ height },
	m_texture{ TRXEngine::ResourceManager::getTexture(path_to_texture)}
{
}

Enemy::~Enemy()
{
}

void Enemy::update()
{
}

void Enemy::draw(TRXEngine::SpriteBatch& sprite_batch) const
{
	// do not draw any dead enemies
	if (m_state == ENEMY_STATE::DEAD)
		return;

	glm::vec4 dest_rec{ m_position,m_width,m_height };
	glm::vec4 uv_rec{ 0.0f,0.0f,1.0f,1.0f };
	TRXEngine::Color color{ 255,0,0,255 };
	sprite_batch.draw(dest_rec, uv_rec, m_texture.id, 0.0f, color);
}
