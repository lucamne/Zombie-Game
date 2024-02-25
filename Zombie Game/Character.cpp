#include "Character.h"

#include <random>

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

void Character::setType(CHARACTER_TYPE type)
{
	m_type = type;
	// if character is zombie or civilian we can initialize a random direction vector
	if (type == CHARACTER_TYPE::ZOMBIE || type == CHARACTER_TYPE::CIVILIAN)
	{
		// generate random x and y values between -100 and 100
		glm::vec2 rand_direction{ rand() % 200 - 100, rand() % 200 - 100 };
		// normalize vector
		rand_direction = glm::normalize(rand_direction);
		
		m_direction = rand_direction;
	}
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
