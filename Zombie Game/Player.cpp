#include <TRXEngine/Vertex.h>
#include <TRXEngine/ResourceManager.h>

#include "Player.h"

Player::Player()
	:m_position{0},
	m_width{0},
	m_height{0}
{
}

Player::Player(const std::string& path_to_texture, glm::vec2 init_position, int width, int height)
	:m_position{init_position},
	m_width{width},
	m_height{height},
	m_texture{TRXEngine::ResourceManager::getTexture(path_to_texture)}
{
}
Player::~Player()
{
}


void Player::draw(TRXEngine::SpriteBatch& sprite_batch)
{
	// add draw call to sprite batch
	// first two arguments are position, second two arguments are dimensions 
	const glm::vec4 dest_rect(m_position, m_width, m_height);
	const glm::vec4 uv_rect(0.0f, 0.0f, 1.0f, 1.0f);
	TRXEngine::Color color{ 255,255,255,255 };
	sprite_batch.draw(dest_rect, uv_rect, m_texture.id,0.0f, color);
}
