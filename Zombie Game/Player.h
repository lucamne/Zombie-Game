#pragma once

#include <TRXEngine/SpriteBatch.h>
#include <TRXEngine/Sprite.h>

#include<glm/glm.hpp>

#include <string>

class Player
{
public:
	Player();
	~Player();

	void draw(TRXEngine::SpriteBatch& sprite_batch) { m_sprite.draw(sprite_batch); }

	// setters
	// set sprite should be usually be called before setPosition or setDimension
	void setSprite(const TRXEngine::Sprite& sprite) { m_sprite = sprite; }
	void setPosition(glm::vec2 pos) { updatePosition(pos); }
	void setDimension(glm::vec2 dim) { updateDimensions(dim); }

	void movePlayer(glm::vec2 normalized_direction, int distance);

private:
	glm::vec2 m_position{};
	// width then height
	glm::vec2 m_dimensions{};
	TRXEngine::Sprite m_sprite{};

	// updates player position and sprite position
	void updatePosition(glm::vec2 new_pos);
	void updateDimensions(glm::vec2 new_dim);
};

