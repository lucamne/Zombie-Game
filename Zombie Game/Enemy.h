#pragma once

#include <TRXEngine/GLTexture.h>
#include <TRXEngine/SpriteBatch.h>

#include <glm/glm.hpp>

#include <string>

enum class ENEMY_STATE
{
	DEAD,
	ALIVE,
};


class Enemy
{
public:
	Enemy(std::string path_to_texture, glm::vec2 position, int width, int height);
	~Enemy();

	void update();
	void draw(TRXEngine::SpriteBatch& sprite_batch) const;
	void kill() { m_state = ENEMY_STATE::DEAD; }

	/// getters
	glm::vec2  getPosition() const { return m_position; }
	int  getWidth() const { return m_width; }
	int  getHeight() const{ return m_height; }
	ENEMY_STATE getState() const{ return m_state; }

private:
	ENEMY_STATE m_state{};
	glm::vec2 m_position{};
	int m_width{};
	int m_height{};
	
	TRXEngine::GLTexture m_texture{};
};

