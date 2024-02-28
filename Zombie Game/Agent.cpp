#include "Agent.h"


#include <TRXEngine/ResourceManager.h>


Agent::Agent()
	:Agent({ 0,0 },{50,50}, "")
{
}

Agent::Agent(glm::vec2 position, glm::vec2 dimensions, const std::string& path_to_texture)
	:m_position{position},
	m_dimensions{dimensions},
	m_path_to_texture{path_to_texture},
	m_speed{10}
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


/*bool Agent::checkWallCollisions(const LevelData& lvl_data)
{
	// y_invert is used to invert y value as row 0 of level_data holds the value of tiles at the top of the screen rather than the bottom
	int y_range{ static_cast<int>(lvl_data.data.size()) * lvl_data.block_height};
	// vector represents vertices of agent hitbox
	glm::vec2 bottom_left{ m_position.x, y_range - m_position.y };
	glm::vec2 top_left{m_position.x, y_range - m_position.y + m_dimensions.y };
	glm::vec2 bottom_right{ m_position.x + m_dimensions.x, y_range - m_position.y};
	glm::vec2 top_right{ (m_position + m_dimensions).x, y_range - (m_position+m_dimensions).y};

	// check if bottom left vertex is in wall which is represented by the character '#'
	if (lvl_data.data[static_cast<int>(bottom_left.y / lvl_data.block_height)][static_cast<int>(bottom_left.x / lvl_data.block_width)] == '#')
	{
		// determine which direction to push out agent based on which component is less further into block
		int x_component{ static_cast<int>(bottom_left.x) % lvl_data.block_width };
		int y_component{ static_cast<int>(bottom_left.y) % lvl_data.block_height };
		if ((x_component > 0 && x_component <= y_component) || y_component <= 0)
		{
			setPosition(getPosition() + glm::vec2(x_component, 0));
		}
		else
		{
			setPosition(getPosition() + glm::vec2(0, y_component));
		}
		return true;
	}

	// check if top left vertex is in wall which is represented by the character '#'
	if (lvl_data.data[static_cast<int>(top_left.y / lvl_data.block_height)][static_cast<int>(top_left.x / lvl_data.block_width)] == '#')
	{
		// determine which direction to push out agent based on which component is less further into block
		int x_component{ static_cast<int>(top_left.x) % lvl_data.block_width };
		int y_component{ static_cast<int>(top_left.y) % lvl_data.block_height };
		if ((x_component > 0 && x_component <= y_component) || y_component <= 0)
		{
			setPosition(getPosition() + glm::vec2(x_component, 0));
		}
		else
		{
			setPosition(getPosition() + glm::vec2(0, -y_component));
		}
		return true;
	}

	// check if bottom right vertex is in wall which is represented by the character '#'
	if (lvl_data.data[static_cast<int>(bottom_right.y / lvl_data.block_height)][static_cast<int>(bottom_right.x / lvl_data.block_width)] == '#')
	{
		// determine which direction to push out agent based on which component is less further into block
		int x_component{ static_cast<int>(bottom_right.x) % lvl_data.block_width };
		int y_component{ static_cast<int>(bottom_right.y) % lvl_data.block_height };
		if ((x_component > 0 && x_component <= y_component) || y_component <= 0)
		{
			setPosition(getPosition() + glm::vec2(-x_component, 0));
		}
		else
		{
			setPosition(getPosition() + glm::vec2(0, y_component));
		}
		return true;
	}

	// check if top right vertex is in wall which is represented by the character '#'
	if (lvl_data.data[static_cast<int>(top_right.y / lvl_data.block_height)][static_cast<int>(top_right.x / lvl_data.block_width)] == '#')
	{
		// determine which direction to push out agent based on which component is less further into block
		int x_component{ static_cast<int>(top_right.x) % lvl_data.block_width };
		int y_component{ static_cast<int>(top_right.y) % lvl_data.block_height };
		if ((x_component > 0 && x_component <= y_component) || y_component <= 0)
		{
			setPosition(getPosition() + glm::vec2(-x_component, 0));
		}
		else
		{
			setPosition(getPosition() + glm::vec2(0, -y_component));
		}
		return true;
	}

	return false;
}*/
