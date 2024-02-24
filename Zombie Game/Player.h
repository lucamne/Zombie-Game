#pragma once

#include "Projectile.h"

#include <TRXEngine/SpriteBatch.h>
#include <TRXEngine/ImageLoader.h>
#include <TRXEngine/GLTexture.h>

#include<glm/glm.hpp>

#include <string>

class Player
{
public:
	Player();
	Player(const std::string& path_to_texture, glm::vec2 init_posiiton, int width, int height);
	~Player();

	void draw(TRXEngine::SpriteBatch& sprite_batch);
	void fireProjectile(glm::vec2 target, float speed);
	// call for autonomous updates, must be called in order to update projectiles spawned from this player
	void update();
	// performs cleanup operations namely for projectile manager
	void cleanup() { m_projectile_manager.cleanup(); }

	/// setters
	void setPosition(glm::vec2 position) { m_position = position; }
	
	/// getters
	glm::vec2 getPosition() const { return m_position; }
	const std::vector<Projectile*>& getProjectiles() const { return m_projectile_manager.getProjectiles(); }

private:
	glm::vec2 m_position{};
	int m_width{};
	int m_height{};

	ProjectileManager m_projectile_manager{};

	// holds texture information
	TRXEngine::GLTexture m_texture{};
};

