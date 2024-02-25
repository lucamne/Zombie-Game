#pragma once

#include <TRXEngine/Sprite.h>
#include <TRXEngine/SpriteBatch.h>

#include <glm/glm.hpp>

#include <vector>
#include <string>

class Map
{
public:
	Map();
	~Map();

	void init(glm::vec2 position, glm::vec2 dimensions);
	// populates wall_sprites vector
	void createSprites();
	void draw(TRXEngine::SpriteBatch& sprite_batch);
	// call during game cleanup to deallocate m_wall_sprites array
	void cleanup();

	// setters
	void setWallTexturePath(const std::string& wall_texture_path) { m_wall_texture_path = wall_texture_path; }

private:
	std::string m_wall_texture_path{};
	// vector that holds all wall sprites
	std::vector<TRXEngine::Sprite*> m_wall_sprites{};

	glm::vec2 m_map_position{};
	glm::vec2 m_map_dimensions{};
};

