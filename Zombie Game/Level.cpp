#include "Level.h"
#include "Textures.h"

#include <TRXEngine/ResourceManager.h>
#include <TRXEngine/Vertex.h>

#include <glm/glm.hpp>

#include <fstream>

Level::Level()
	:m_tile_width{50},
	m_tile_height{50},
	m_init_player_position{0,0},
	m_init_zombie_position{0,0}

{
}
Level::~Level()
{
}

void Level::load(std::string fp)
{
	std::ifstream file{};
	file.open(fp);
	if (file.fail())
	{
		perror(fp.c_str());
		system("PAUSE");
		exit(1);
	}

	std::string line{};
	while (std::getline(file, line))
	{
		m_data.push_back(line);
	}

	file.close();

	initPositions();
}

void Level::draw(TRXEngine::SpriteBatch& sprite_batch)
{
	// draw walls
	for (int y{ 0 }; y < m_data.size(); y++)
	{
		for (int x{ 0 }; x < m_data[y].size(); x++)
		{
			switch (m_data[y][x])
			{
			case '#':
				drawWall(x, y, sprite_batch);
				break;
			default:
				break;
			}
		}
	}
}

char Level::getTileAtScreenCoordinate(glm::vec2 screen_coords)
{
	int x_tile{ static_cast<int>(screen_coords.x / m_tile_width) };
	int y_tile{ static_cast<int>(m_data.size()) -1 - static_cast<int>(screen_coords.y / m_tile_height) };
	// bounds checking to prevent crash
	if (x_tile < 0 || x_tile >= m_data[0].size() || y_tile < 0 || y_tile >= m_data.size())
	{
		return '?';
	}
	return m_data[y_tile][x_tile];
}

// initializes the positions of agents based on m_level_data
void Level::initPositions()
{
	// slightly innefficient as this double for loop is replicated in draw
	// however, the function is only called once so efficieny should not be a major issue
	for (int y{ 0 }; y < m_data.size(); y++)
	{
		for (int x{ 0 }; x < m_data[y].size(); x++)
		{
			switch (m_data[y][x])
			{
			case '@':
				// draw / initialize player
				// set initial position of p[layer based on initial level layout
				m_init_player_position = levelCoordsToScreenCoords({ x,y });
				break;
			case 'Z':
				m_init_zombie_position = levelCoordsToScreenCoords({ x,y });
				break;
			default:
				break;
			}
		}
	}
}

// function to draw wall sprites in the correct location
void Level::drawWall(int x, int y, TRXEngine::SpriteBatch& sprite_batch)
{
	static TRXEngine::GLTexture wall_texture{ TRXEngine::ResourceManager::getTexture(TEXTURES::WALL) };

	glm::vec4 dest_rec{ levelCoordsToScreenCoords({x,y}),m_tile_width,m_tile_height};
	glm::vec4 uv_rec{ 0.0f,0.0f,1.0f,1.0f };
	TRXEngine::Color color{ 165,42,42,255 };

	sprite_batch.draw(dest_rec, uv_rec, wall_texture.id, 1.0f, color);
}

glm::vec2 Level::levelCoordsToScreenCoords(glm::vec2 tile_coordinates)
{
	// multiply x level coordinates by block_width
	// subtract y from total rows in level then multiply by block_height so that level is not flipped withh respect to level.txt drawing
	 return { tile_coordinates.x * m_tile_width,(m_data.size() - 1 - tile_coordinates.y) * m_tile_height };
}
