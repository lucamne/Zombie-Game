#pragma once
#include "Human.h"
class Player : public Human
{
public:
	Player();
	Player(glm::vec2 position, glm::vec2 dimensions, const std::string& path_to_texture);
	~Player();

	// moves player in direction according to internal speed, vector should be normalized
	void movePlayer(glm::vec2 direction);

	// setters
	void setPosition(glm::vec2 position) { Agent::setPosition(position); }
	
	// getters
	glm::vec2 getPosition() const { return Agent::getPosition(); }
};

