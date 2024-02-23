#include "Projectile.h"

#include <TRXEngine/ResourceManager.h>

Projectile::Projectile(const std::string& path_to_texture, glm::vec2 init_position, int width, int height, glm::vec2 direction, float speed)
	:m_position{init_position},
	m_direction{glm::normalize(direction)},
	m_speed{speed},
	m_width{width},
	m_height{height},
	m_texture{ TRXEngine::ResourceManager::getTexture(path_to_texture) }
{
}

Projectile::~Projectile()
{
}

void Projectile::draw(TRXEngine::SpriteBatch& sprite_batch)
{
	const glm::vec4 dest_rec{ m_position,m_width,m_height };
	const glm::vec4 uv_rec{ 0.0f,0.0f,1.0f,1.0f };
	sprite_batch.draw(dest_rec, uv_rec, m_texture.id, 0.0f, { 255,255,255,255 });
}

void Projectile::update()
{
	m_position += m_direction * m_speed;
}

ProjectileManager::ProjectileManager()
{
}

ProjectileManager::~ProjectileManager()
{
}

void ProjectileManager::drawProjectiles(TRXEngine::SpriteBatch& sprite_batch)
{
	for (Projectile* projectile : m_projectiles)
	{
		projectile->draw(sprite_batch);
	}
}

void ProjectileManager::updateProjectiles()
{
	for (Projectile* projectile : m_projectiles)
	{
		projectile->update();
	}
}

void ProjectileManager::cleanup()
{
	for (Projectile* projectile : m_projectiles)
	{
		delete projectile;
	}
}
