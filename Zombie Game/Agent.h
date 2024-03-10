#pragma once

#include <TRXEngine/Vertex.h>
#include <TRXEngine/SpriteBatch.h>

#include <glm/glm.hpp>

#include <string>


enum class AGENT_STATE
{
	ALIVE,
	DEAD,
};

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
	// flips collision setting and returns current setting
	bool flipCollisionSetting() { m_collisions_on = !m_collisions_on; return m_collisions_on; }
	// given center position and radius of another agent, determine if they have collided
	bool isCollidedWithAgent(glm::vec2 center_pos, float radius);

	// setters
	void setPosition(glm::vec2 pos);
	void setDimensions(glm::vec2 dim) { m_dimensions = dim; }
	void setColor(TRXEngine::Color color) { m_agent_color = color; }
	void setSpeed(float speed) { m_speed = speed; }
	void setTexturePath(const std::string& path_to_texture) { m_path_to_texture = path_to_texture; }
	void setState(AGENT_STATE state) { m_state = state; }

	// getters
	glm::vec2 getPosition() const { return m_position; }
	glm::vec2 getDimensions() const { return m_dimensions; }
	float getSpeed() const { return m_speed; }
	glm::vec2 getCenterPosition() const { return m_center_position; }
	AGENT_STATE getState() const { return m_state; }

private:
	glm::vec2 m_position{};
	glm::vec2 m_dimensions{};
	glm::vec2 m_center_position{};
	std::string m_path_to_texture{};
	TRXEngine::Color m_agent_color{ 255,255,255,255 };
	float m_speed{};
	bool m_collisions_on{};
	AGENT_STATE m_state{};

	bool isPositionInWall(glm::vec2 new_pos);
	// returns new position if a valid one is found, otherwise returns the starting position
	glm::vec2 pushOutOfWall(glm::vec2 starting_pos);
};

