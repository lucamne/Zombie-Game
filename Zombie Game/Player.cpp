#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}


void Player::movePlayer(glm::vec2 normalized_direction, int distance)
{
	// we cast distance to float because we want distance to be a whole number but glm::vec uses floats
	const glm::vec2 new_pos{ m_position + (normalized_direction * static_cast<float>(distance)) };
	
	updatePosition(new_pos);
}

void Player::updatePosition(glm::vec2 new_pos)
{
	m_position = new_pos;
	m_sprite.setPosition(new_pos);
}
