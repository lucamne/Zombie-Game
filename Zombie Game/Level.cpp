#include "Level.h"
#include "Textures.h"

#include <TRXEngine/ResourceManager.h>
#include <TRXEngine/Vertex.h>

#include <glm/glm.hpp>

#include <fstream>

Level::Level()
	:m_player{ {0,0}, {50,50}, TEXTURES::PLAYER }
{
	m_level_data.block_height = 50;
	m_level_data.block_width = 50;

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
		m_level_data.data.push_back(line);
	}

	file.close();

	initPositions();
}

void Level::draw(TRXEngine::SpriteBatch& sprite_batch)
{
	// draw walls
	for (int y{ 0 }; y < m_level_data.data.size(); y++)
	{
		for (int x{ 0 }; x < m_level_data.data[y].size(); x++)
		{
			switch (m_level_data.data[y][x])
			{
			case '#':
				drawWall(x, y, sprite_batch);
				break;
			default:
				break;
			}
		}
	}

	m_player.draw(sprite_batch);
}

void Level::movePlayer(glm::vec2 direction)
{
	m_player.movePlayer(direction);
	m_player.checkWallCollisions(m_level_data);
}

// initializes the positions of agents based on m_level_data
void Level::initPositions()
{
	// slightly innefficient as this double for loop is replicated in draw
	// however, the function is only called once so efficieny should not be a major issue
	for (int y{ 0 }; y < m_level_data.data.size(); y++)
	{
		for (int x{ 0 }; x < m_level_data.data[y].size(); x++)
		{
			switch (m_level_data.data[y][x])
			{
			case '@':
				// draw / initialize player
				// set initial position of p[layer based on initial level layout
				m_player.setPosition(levelCoordsToScreenCoords({ x,y }));
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

	glm::vec4 dest_rec{ levelCoordsToScreenCoords({x,y}),m_level_data.block_width,m_level_data.block_height};
	glm::vec4 uv_rec{ 0.0f,0.0f,1.0f,1.0f };
	TRXEngine::Color color{ 165,42,42,255 };

	sprite_batch.draw(dest_rec, uv_rec, wall_texture.id, 1.0f, color);
}

glm::vec2 Level::levelCoordsToScreenCoords(glm::vec2 level_coordinates)
{
	// multiply x level coordinates by block_width
	// subtract y from total rows in level then multiply by block_height so that level is not flipped withh respect to level.txt drawing
	 return { level_coordinates.x * m_level_data.block_width,(m_level_data.data.size() - level_coordinates.y) * m_level_data.block_height };
}
