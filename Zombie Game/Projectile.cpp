#include "Projectile.h"

#include <TRXEngine/ResourceManager.h>

Projectile::Projectile(const std::string& path_to_texture, glm::vec2 init_position, int width, int height, glm::vec2 direction, float speed, int lifetime)
	:m_position{ init_position },
	m_direction{ glm::normalize(direction) },
	m_speed{ speed },
	m_width{ width },
	m_height{ height },
	m_lifetime{ lifetime },
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

bool Projectile::update()
{
	if (--m_lifetime <= 0)
	{
		return true;
	}
	m_position += m_direction * m_speed;
	return false;
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
	for (int i{0}; i < m_projectiles.size();)
	{
		// if projectile's lifetime is 0 destroy projectile object and remove from projectiles vector
		if (m_projectiles[i]->update())
		{
			delete m_projectiles[i];
			// replace current projectile pointer with last projectile pointer and then remove that pointer from vector
			m_projectiles[i] = m_projectiles.back();
			m_projectiles.pop_back();
		}
		else {
			// only increment i if projectile is not destroyed so that the replacement projectile does not get skipped
			i++;
		}
	}
}

void ProjectileManager::cleanup()
{
	for (Projectile* projectile : m_projectiles)
	{
		delete projectile;
	}
}
