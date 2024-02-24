#pragma once

#include <TRXEngine/SpriteBatch.h>
#include <TRXEngine/Sprite.h>

#include<glm/glm.hpp>

#include <string>

enum class CHARACTER_TYPE
{
	PLAYER,
	ZOMBIE,
	CIVILIAN
};

class Character
{
public:
	Character();
	~Character();

	void draw(TRXEngine::SpriteBatch& sprite_batch) { m_sprite.draw(sprite_batch); }

	void moveCharacter(glm::vec2 normalized_direction, int distance);

	// setters
	// set sprite should be usually be called before setPosition or setDimension
	void setSprite(const TRXEngine::Sprite& sprite) { m_sprite = sprite; }
	void setPosition(glm::vec2 pos) { updatePosition(pos); }
	void setDimension(glm::vec2 dim) { updateDimensions(dim); }
	void setType(CHARACTER_TYPE type) { m_type = type; }

	// getters
	glm::vec2 getPosition() const { return m_position; }
	// returns position of center of Character as opposed to bottom left
	glm::vec2 getCenterPosition() const { return m_position + 0.5f * m_dimensions; }
	

private:
	CHARACTER_TYPE m_type{};

	glm::vec2 m_position{};
	// width then height
	glm::vec2 m_dimensions{};
	TRXEngine::Sprite m_sprite{};

	// updates Character position and sprite position
	void updatePosition(glm::vec2 new_pos);
	void updateDimensions(glm::vec2 new_dim);
};

