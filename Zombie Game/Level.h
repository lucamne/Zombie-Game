#pragma once

#include "Player.h"
#include "LevelData.h"

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

	void draw(TRXEngine::SpriteBatch& sprite_batch);

	// functions to control player within level // 
	// setters
	
	// moves player in direction according to internally stored speed
	void movePlayer(glm::vec2 direction);

	// getters
	glm::vec2 getPlayerPosition() const { return m_player.getPosition(); }

private:
	Player m_player{};
	LevelData m_level_data{};
	
	// draw call to be made on initial draw call
	void initPositions();
	void drawWall(int x, int y, TRXEngine::SpriteBatch& sprite_batch);
	glm::vec2 levelCoordsToScreenCoords(glm::vec2 level_coordinates);
};

