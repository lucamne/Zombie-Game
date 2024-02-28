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

bool Agent::checkWallCollisions(const std::vector<std::string>& level_data)
{
	// vector represents vertices of agent hitbox
	glm::vec2 bottom_left{ m_position };
	glm::vec2 top_left{ m_position + glm::vec2(0,m_dimensions.y) };
	glm::vec2 bottom_right{ m_position + glm::vec2(m_dimensions.x,0)};
	glm::vec2 top_right{ m_position + m_dimensions};

	int num_of_rows{ level_data.size() };

}
