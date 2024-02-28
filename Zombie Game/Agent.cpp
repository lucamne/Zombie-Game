#include "Agent.h"
#include "LevelManager.h"

#include <TRXEngine/ResourceManager.h>

#include <map>

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

void Agent::setPosition(glm::vec2 pos)
{
	m_position = pos;
	checkWallCollisions();
}

bool Agent::checkWallCollisions()
{
	const glm::vec2 TOP_LEFT{ m_position + glm::vec2(0,m_dimensions.y) };
	const glm::vec2 BOTTOM_LEFT{ m_position};
	const glm::vec2 TOP_RIGHT{ m_position  + m_dimensions};
	const glm::vec2 BOTTOM_RIGHT{ m_position + glm::vec2(m_dimensions.x,0) };
	// map holds true for each vertex if vertex is in wall block
	std::map<glm::vec2, bool> vertex_collisions{};

	// grabs level data from active level, ensure that active level has been set
	Level level_data{ LevelManager::getLevelData() };

	std::cout << level_data.getTileAtScreenCoordinate(BOTTOM_LEFT) << '\n';

	return false;
}


