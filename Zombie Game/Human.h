#pragma once

#include "Agent.h"

#include <glm/glm.hpp>

#include <vector>

class Zombie;

class Human : public Agent
{
public:
	Human();
	Human(glm::vec2 position, glm::vec2 dimensions, const std::string& path_to_texture);
	~Human();

	// updates humans so that they run from the nearest zombie
	void updatePosition(const std::vector<Zombie*>& zombies);
private:

};

