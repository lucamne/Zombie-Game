#pragma once

#include "Textures.h"

#include <TRXEngine/Sprite.h>
#include <TRXEngine/SpriteBatch.h>

#include <glm/glm.hpp>

#include <vector>
#include <string>

class Map
{
public:
	Map();
	Map(glm::vec2 position, glm::vec2 dimensions);
	~Map();

	// populates wall_sprites vector
	void initSprites();
	void draw(TRXEngine::SpriteBatch& sprite_batch);

private:
	glm::vec2 m_map_position{};
	glm::vec2 m_map_dimensions{};

	TRXEngine::Sprite m_left_wall{};
	TRXEngine::Sprite m_right_wall{};
	TRXEngine::Sprite m_top_wall{};
	TRXEngine::Sprite m_bottom_wall{};
};

