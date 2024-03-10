#include "Agent.h"
#include "LevelManager.h"

#include <TRXEngine/ResourceManager.h>

#include <map>
#include <cmath>
#include <iostream>

Agent::Agent()
	:Agent({ 0,0 },{50,50}, "")
{
}

Agent::Agent(glm::vec2 position, glm::vec2 dimensions, const std::string& path_to_texture)
	:m_position{ position },
	m_dimensions{ dimensions },
	m_center_position{ m_position + m_dimensions * 0.5f },
	m_path_to_texture{ path_to_texture },
	m_speed{ 10 },
	m_collisions_on{ true },
	m_state{AGENT_STATE::ALIVE}
{
}

Agent::~Agent()
{
}

void Agent::draw(TRXEngine::SpriteBatch& sprite_batch) const
{
	// agent is dead no need to draw it
	if (m_state == AGENT_STATE::DEAD)
	{
		return;
	}

	static TRXEngine::GLTexture agent_texture{ TRXEngine::ResourceManager::getTexture(m_path_to_texture) };
	glm::vec4 dest_rec{ m_position,m_dimensions };
	glm::vec4 uv_rec{ 0.0f,0.0f,1.0f,1.0f };

	sprite_batch.draw(dest_rec, uv_rec, agent_texture.id, 1.0f, m_agent_color);
}


bool Agent::isCollidedWithAgent(glm::vec2 center_pos, float radius)
{
	float d{ glm::distance(m_center_position,center_pos) };
	// 15 is subtracted to let the sprites overlap more visually before reporting collision
	return d < (radius / 2.0f + m_dimensions.x / 2.0f) - 15;
}

void Agent::setPosition(glm::vec2 pos)
{
	// if new position does not place any vertices of agent in wall then set that position
	if (!isPositionInWall(pos))
	{
		m_position = pos;
		m_center_position = pos + m_dimensions * 0.5f;
	}
	else
	{
		m_position = pushOutOfWall(pos);
		m_center_position = m_position + m_dimensions * 0.5f;
	}
}

bool Agent::isPositionInWall(glm::vec2 new_pos)
{
	// holds level data from active level, ensure that active level has been set
	Level level_data{ LevelManager::getLevelData() };

	glm::vec2 dimensions{ getDimensions() };

	glm::vec2 top_left{ new_pos + glm::vec2(0,dimensions.y) };
	glm::vec2 bottom_left{ new_pos };
	glm::vec2 top_right{ new_pos + dimensions };
	glm::vec2 bottom_right{ new_pos + glm::vec2(dimensions.x,0) };

	return level_data.getTileAtScreenCoordinate(top_left) == '#' ||
		level_data.getTileAtScreenCoordinate(bottom_left) == '#' ||
		level_data.getTileAtScreenCoordinate(top_right) == '#' ||
		level_data.getTileAtScreenCoordinate(bottom_right) == '#';
}

glm::vec2 Agent::pushOutOfWall(glm::vec2 starting_pos)
{
	Level level_data{ LevelManager::getLevelData() };
	int tile_w{ level_data.getTileWidth() };
	int tile_h{ level_data.getTileHeight() };

	glm::vec2 dimensions{ getDimensions() };

	glm::vec2 top_left{ starting_pos + glm::vec2(0,dimensions.y) };
	glm::vec2 bottom_left{ starting_pos };
	glm::vec2 top_right{ starting_pos + dimensions };
	glm::vec2 bottom_right{ starting_pos + glm::vec2(dimensions.x,0) };

	glm::vec2 x_move{};
	glm::vec2 y_move{};

	if (level_data.getTileAtScreenCoordinate(top_left) == '#')
	{
		// try moving right
		if (static_cast<int>(top_left.x) % tile_w == 0) 
			x_move = { 1,0 };
		else 
			x_move = { tile_w - (static_cast<int>(top_left.x) % tile_w), 0 };
		if (!isPositionInWall(starting_pos + x_move))
		{
			return starting_pos + x_move;
		}

		// try moving down
		// -1 is added to y component to ensure space from wall
		y_move = { 0,-(static_cast<int>(top_left.y) % tile_h) - 1 };
		if (!isPositionInWall(starting_pos + y_move))
		{
			return starting_pos + y_move;
		}

		// try moving diagonal
		if (!isPositionInWall(starting_pos + y_move + x_move))
		{
			return starting_pos + y_move + x_move;
		}
	}
	if (level_data.getTileAtScreenCoordinate(bottom_left) == '#')
	{
		// try moving right
		if (static_cast<int>(bottom_left.x) % tile_w == 0)
			x_move = { 1,0 };
		else
			x_move = { tile_w - (static_cast<int>(bottom_left.x) % tile_w), 0 };
		if (!isPositionInWall(starting_pos + x_move))
		{
			return starting_pos + y_move;
		}

		// try moving up
		if (static_cast<int>(bottom_left.y) % tile_h == 0)
			y_move = { 0,1 };
		else
			y_move = { 0, tile_h -(static_cast<int>(bottom_left.y) % tile_h) };
		if (!isPositionInWall(starting_pos + y_move))
		{
			return starting_pos + y_move;
		}

		// try moving diagonal
		if (!isPositionInWall(starting_pos + y_move + x_move))
		{
			return starting_pos + y_move + x_move;
		}
	}
	if (level_data.getTileAtScreenCoordinate(top_right) == '#')
	{
		// try moving left
		// -1 is added to x component to ensure space from wall
		x_move = { - (static_cast<int>(top_right.x) % tile_w) - 1, 0 };
		if (!isPositionInWall(starting_pos + x_move))
		{
			return starting_pos + x_move;
		}

		// try moving down
		// -1 is added to y component to ensure space from wall
		y_move = { 0,-(static_cast<int>(top_right.y) % tile_h) - 1 };
		if (!isPositionInWall(starting_pos + y_move))
		{
			return starting_pos + y_move;
		}

		// try moving diagonal
		if (!isPositionInWall(starting_pos + y_move + x_move))
		{
			return starting_pos + y_move + x_move;
		}
	}
	if (level_data.getTileAtScreenCoordinate(bottom_right) == '#')
	{
		// try moving left
		// -1 is added to x component to ensure space from wall
		x_move = { -(static_cast<int>(bottom_right.x) % tile_w) - 1, 0 };
		if (!isPositionInWall(starting_pos + x_move))
		{
			return starting_pos + x_move;
		}

		// try moving up
		if (static_cast<int>(bottom_right.y) % tile_h == 0)
			y_move = { 0,1 };
		else
			y_move = { 0, tile_h - (static_cast<int>(bottom_right.y) % tile_h) };
		if (!isPositionInWall(starting_pos + y_move))
		{
			return starting_pos + y_move;
		}

		// try moving diagonal
		if (!isPositionInWall(starting_pos + y_move + x_move))
		{
			return starting_pos + y_move + x_move;
		}
	}

	return starting_pos;
}



