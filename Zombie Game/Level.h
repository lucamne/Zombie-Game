#pragma once

#include <TRXEngine/SpriteBatch.h>
#include <TRXEngine/GLTexture.h>

#include <glm/glm.hpp>

#include <vector>
#include <string>


class Level
{
public:
	Level();
	~Level();
	// loads in level data from text file
	void load(std::string fp);
	// draws non-agent components of level (walls)
	void draw(TRXEngine::SpriteBatch& sprite_batch);
	
	// getters

	glm::vec2 getInitPlayerPosition() const { return m_init_player_position; }
	glm::vec2 getInitZombiePosition() const { return m_init_zombie_position; }

private:
	std::vector<std::string> m_data{};
	// width of each tile
	int m_tile_width{};
	// height of each tile
	int m_tile_height{};
	// starting position of player, set upon initial load
	glm::vec2 m_init_player_position{};
	// starting position of zombie, set upon initial load
	glm::vec2 m_init_zombie_position{};
	// draw call to be made on initial draw call

	void initPositions();
	void drawWall(int x, int y, TRXEngine::SpriteBatch& sprite_batch);
	glm::vec2 levelCoordsToScreenCoords(glm::vec2 level_coordinates);
};

