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
	m_center_position{ m_position.x + m_dimensions * 0.5f },
	m_path_to_texture{ path_to_texture },
	m_speed{ 10 },
	m_collisions_on{ true }
{
}

Agent::~Agent()
{
}

void Agent::draw(TRXEngine::SpriteBatch& sprite_batch) const
{
	static TRXEngine::GLTexture agent_texture{ TRXEngine::ResourceManager::getTexture(m_path_to_texture) };
	glm::vec4 dest_rec{ m_position,m_dimensions };
	glm::vec4 uv_rec{ 0.0f,0.0f,1.0f,1.0f };

	sprite_batch.draw(dest_rec, uv_rec, agent_texture.id, 1.0f, m_agent_color);
}

void Agent::setPosition(glm::vec2 pos)
{
	if (isNewPositionInWall(pos))
		return;
	m_position = pos;
	m_center_position = pos + m_dimensions * 0.5f;
}

// needs fixing, pushing agent out of wall not working correctly
bool Agent::checkWallCollisions()
{	
	// used as map key
	enum VERTEX_TYPE
	{
		TOP_LEFT,
		BOTTOM_LEFT,
		TOP_RIGHT,
		BOTTOM_RIGHT,
	};
	// holds level data from active level, ensure that active level has been set
	Level level_data{ LevelManager::getLevelData() };
	
	glm::vec2 top_left{ m_position + glm::vec2(0,m_dimensions.y) };
	glm::vec2 bottom_left{  m_position };
	glm::vec2 top_right{m_position + m_dimensions };
	glm::vec2 bottom_right{ m_position + glm::vec2(m_dimensions.x,0) };

	// map holds AgentVertex (glm::vec2) if AgentVertex is in wall block
	std::map<VERTEX_TYPE,bool> vertex_collisions{};
	// check top left vertex
	vertex_collisions.emplace(TOP_LEFT, level_data.getTileAtScreenCoordinate(top_left) == '#');
	// check bottom left vertex
	vertex_collisions.emplace(BOTTOM_LEFT, level_data.getTileAtScreenCoordinate(bottom_left) == '#');
	// check top right vertex
	vertex_collisions.emplace(TOP_RIGHT, level_data.getTileAtScreenCoordinate(top_right) == '#');
	// check bottom right vertex
	vertex_collisions.emplace(BOTTOM_RIGHT, level_data.getTileAtScreenCoordinate(bottom_right) == '#');

	// keeps track of number of vertices in wall tiles
	int collision_count{ 0 };
	float x_pos{};
	float y_pos{};
	// tile dimensions
	int tile_width{ level_data.getTileWidth() };
	int tile_height{ level_data.getTileHeight()};
	// change in position vector
	glm::vec2 change_in_position{};

	// check top left vertex
	if (vertex_collisions[TOP_LEFT])
	{
		change_in_position = { tile_width - (static_cast<int>(top_left.x) % tile_width) , -(static_cast<int>(top_left.y) % tile_height) };
		x_pos = top_left.x;
		y_pos = top_left.y;	
		collision_count++;
	}
	// check bottom_left vertex
	if (vertex_collisions[BOTTOM_LEFT])
	{

		if (collision_count == 1)
		{
			change_in_position.y = 0;
		}
		else
		{
			change_in_position = { tile_width - (static_cast<int>(bottom_left.x) % tile_width) ,tile_height - (static_cast<int>(bottom_left.y) % tile_height) };
			x_pos = bottom_left.x;
			y_pos = bottom_left.y;
		}
		collision_count++;
	}
	// check top_right vertex
	if (vertex_collisions[TOP_RIGHT])
	{
		if (collision_count == 1)
		{
			if (static_cast<int>(top_right.x) == x_pos)
			{
				change_in_position = { -(static_cast<int>(top_right.x) % tile_width),0 };
				y_pos = top_right.y;
			}
			else
			{
				change_in_position = { 0, -(static_cast<int>(top_right.y) % tile_height) };
				x_pos = top_right.x;
			}
		}
		else if (collision_count == 2)
		{
			if (change_in_position.x == 0)
			{
				change_in_position += glm::vec2(-(static_cast<int>(top_right.x) % tile_width), 0);
			}
			else
			{
				change_in_position += glm::vec2(0, -(static_cast<int>(top_right.y) % tile_height));
			}
		}

		else
		{
			change_in_position = { -(static_cast<int>(top_right.x) % tile_width) , -static_cast<int>(top_right.y) % tile_height };
			x_pos = top_right.x;
			y_pos = top_right.y;
		}
		collision_count++;
	}
	// check bottom_right vertex
	if (vertex_collisions[BOTTOM_RIGHT])
	{
		if (collision_count == 1)
		{
			if (static_cast<int>(bottom_right.x) == x_pos)
			{
				change_in_position = { -(static_cast<int>(bottom_right.x) % tile_width), 0 };
				y_pos = bottom_right.y;
			}
			else
			{
				change_in_position = { 0, tile_height - (static_cast<int>(bottom_right.y) % tile_height) };
				x_pos = bottom_right.x;
			}
		}
		else if (collision_count == 2)
		{
			if (change_in_position.x == 0)
			{
				change_in_position += glm::vec2(-(static_cast<int>(bottom_right.x) % tile_width), 0);
			}
			else
			{
				change_in_position += glm::vec2(0, tile_height - (static_cast<int>(bottom_right.y) % tile_height));
			}
		}
		else
		{
			change_in_position = { -(static_cast<int>(bottom_right.x) % tile_width) , tile_height - (static_cast<int>(bottom_right.y) % tile_height) };
			x_pos = bottom_right.x;
			y_pos = bottom_right.y;
		}
		collision_count++;

	}
	//std::cout << collision_count << '\n';
	// if no collisions return
	if (collision_count == 0)
		return false;
	// if one value is 0 must move according to other component
	if (change_in_position.x == 0 || change_in_position.y == 0)
	{
		m_position += change_in_position;
		return true;
	}
	// push agent the direction with the smallest component
	if (std::abs(change_in_position.x) <= std::abs(change_in_position.y))
	{
		m_position += glm::vec2(change_in_position.x,0);
	}
	else
	{
		m_position += glm::vec2(0, change_in_position.y);
	}
	return true;
}

bool Agent::isNewPositionInWall(glm::vec2 new_pos)
{
	// holds level data from active level, ensure that active level has been set
	Level level_data{ LevelManager::getLevelData() };

	glm::vec2 top_left{ new_pos + glm::vec2(0,m_dimensions.y-1) };
	glm::vec2 bottom_left{ new_pos };
	glm::vec2 top_right{ new_pos + m_dimensions - glm::vec2(1,1) };
	glm::vec2 bottom_right{ new_pos + glm::vec2(m_dimensions.x-1,0) };
	
	return level_data.getTileAtScreenCoordinate(top_left) == '#' ||
		level_data.getTileAtScreenCoordinate(bottom_left) == '#' ||
		level_data.getTileAtScreenCoordinate(top_right) == '#' ||
		level_data.getTileAtScreenCoordinate(bottom_right) == '#';
}




