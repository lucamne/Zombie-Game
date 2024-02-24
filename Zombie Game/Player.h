#pragma once

#include "Projectile.h"

#include <TRXEngine/SpriteBatch.h>
#include <TRXEngine/ImageLoader.h>
#include <TRXEngine/GLTexture.h>
#include <TRXEngine/Sprite.h>

#include<glm/glm.hpp>

#include <string>

class Player
{
public:
	Player();
	~Player();

	// setters
	void setPosition(glm::vec2 pos) { m_position = pos; }
	void setDimension(glm::vec2 dim) { m_dimensions = dim; }
	void setSprite(const TRXEngine::Sprite& sprite) { m_sprite = sprite; }

	void movePlayer(glm::vec2 normalized_direction, int distance);

private:
	glm::vec2 m_position{};
	// width then height
	glm::vec2 m_dimensions{};
	TRXEngine::Sprite m_sprite{};

	// updates player position and sprite position
	void updatePosition(glm::vec2 new_pos);
};

