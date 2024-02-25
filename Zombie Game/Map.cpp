#include "Map.h"

Map::Map()
{
}

Map::~Map()
{
}

void Map::init(glm::vec2 position, glm::vec2 dimensions)
{
	m_map_position = position;
	m_map_dimensions = dimensions;
}

void Map::createSprites()
{
	// sprite dimensions
	static glm::vec2 wall_dimensions{ 50,50 };

	// create vertical wall sprites on left and right of map
	for (int y{ 0 }; y < m_map_dimensions.y; y += static_cast<int>(wall_dimensions.y))
	{
		TRXEngine::Sprite* wall_sprite1{ new TRXEngine::Sprite() };
		TRXEngine::Sprite* wall_sprite2{ new TRXEngine::Sprite() };
		// sprite1 is set to left wall and sprite2 is set to right wall
		wall_sprite1->init(m_wall_texture_path, glm::vec4(0, y, wall_dimensions));
		wall_sprite1->init(m_wall_texture_path, glm::vec4(m_map_dimensions.x, y, wall_dimensions));

		m_wall_sprites.push_back(wall_sprite1);
		m_wall_sprites.push_back(wall_sprite2);
	}

	// create horizontal wall sprites
	for (int x{ 0 }; x < m_map_dimensions.x; x += static_cast<int>(wall_dimensions.x))
	{
		TRXEngine::Sprite* wall_sprite1{ new TRXEngine::Sprite() };
		TRXEngine::Sprite* wall_sprite2{ new TRXEngine::Sprite() };
		// sprite1 is set to bottom wall and sprite2 is set to top wall
		wall_sprite1->init(m_wall_texture_path, glm::vec4(x, 0, wall_dimensions));
		wall_sprite1->init(m_wall_texture_path, glm::vec4(x, m_map_dimensions.y, wall_dimensions));

		m_wall_sprites.push_back(wall_sprite1);
		m_wall_sprites.push_back(wall_sprite2);
	}
}

void Map::draw(TRXEngine::SpriteBatch& sprite_batch)
{
	for (TRXEngine::Sprite* sprite : m_wall_sprites)
	{
		sprite->draw(sprite_batch);
	}
}

void Map::cleanup()
{
	for (TRXEngine::Sprite* sprite : m_wall_sprites)
	{
		delete sprite;
	}
}

