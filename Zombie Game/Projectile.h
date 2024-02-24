#pragma once

#include <TRXEngine/SpriteBatch.h>
#include <TRXEngine/GLTexture.h>

#include <glm/glm.hpp>

#include <string>
#include <vector>

class Projectile
{
public:
	Projectile(const std::string& path_to_texture, glm::vec2 init_position, int width, int height, glm::vec2 direction, float speed, int lifetime);
	~Projectile();

	// draws projectile to sprite_batch
	void draw(TRXEngine::SpriteBatch& sprite_batch);
	// updates position based on velocity and lifetime, returns true if lifetime has ended
	bool update();

	/// setters
	void setPosition(glm::vec2 position) { m_position = position; }
	/// getters
	glm::vec2 getPosition() const { return m_position; }
	glm::vec2 getCenterPosition() const { return m_position + glm::vec2(m_width / 2, m_height / 2); }

private:
	glm::vec2 m_position{};
	// normalized direction vector
	glm::vec2 m_direction{};
	float m_speed{};
	int m_width{};
	int m_height{};
	// lifetime measured in frames
	int m_lifetime{};

	TRXEngine::GLTexture m_texture{};

};

class ProjectileManager
{
public:
	ProjectileManager();
	~ProjectileManager();

	void drawProjectiles(TRXEngine::SpriteBatch& sprite_batch);
	void updateProjectiles();
	// destroys all Projectile objects being held in m_projectiles
	void cleanup();

	/// setters
	void addProjectile(Projectile& projectile) { m_projectiles.push_back(&projectile); }
	/// getters
	const std::vector<Projectile*>& getProjectiles() const { return m_projectiles; }

private:
	std::vector<Projectile* > m_projectiles{};
};

