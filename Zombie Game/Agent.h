#pragma once

#include <TRXEngine/Sprite.h>
#include <TRXEngine/Vertex.h>

#include <glm/glm.hpp>

/// <summary>
///  Agent class handles collision and rendering for all agents (zombies, humans -> player)
/// </summary>
class Agent
{
public:
	Agent();
	Agent(glm::vec2 position, glm::vec2 dimensions, const std::string& path_to_texture);
	~Agent();

	void draw(TRXEngine::SpriteBatch& sprite_batch) const;

	// setters
	void setPosition(glm::vec2 pos) { m_position = pos; }
	void setDimensions(glm::vec2 dim) { m_dimensions = dim; }
	void setColor(TRXEngine::Color color) { m_agent_color = color; }
	void setSpeed(int speed) { m_speed = speed; }

	// getters
	glm::vec2 getPosition() const { return m_position; }
	glm::vec2 getDimensions() const { return m_dimensions; }
	int getSpeed() const { return m_speed; }

private:
	glm::vec2 m_position{};
	glm::vec2 m_dimensions{};
	std::string m_path_to_texture{};
	TRXEngine::Color m_agent_color{ 255,255,255,255 };
	int m_speed{};

	// checks if agent has collided with wall and pushes them out from wall
	// returns true if a collision has occured
	bool checkWallCollisions(const std::vector<std::string>& level_data);
};
