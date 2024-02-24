#include "Character.h"

Character::Character()
{
}

Character::~Character()
{
}


void Character::moveCharacter(glm::vec2 normalized_direction, int distance)
{
	// we cast distance to float because we want distance to be a whole number but glm::vec uses floats
	const glm::vec2 new_pos{ m_position + (normalized_direction * static_cast<float>(distance)) };
	
	updatePosition(new_pos);
}

void Character::updatePosition(glm::vec2 new_pos)
{
	m_position = new_pos;
	m_sprite.setPosition(new_pos);
}

void Character::updateDimensions(glm::vec2 new_dim)
{
	m_dimensions = new_dim;
	m_sprite.setDimension(new_dim);
}
