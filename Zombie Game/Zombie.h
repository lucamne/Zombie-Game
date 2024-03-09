#pragma once
#include "Agent.h"
#include "Human.h"
#include "Player.h"

#include <glm/glm.hpp>

#include <vector>

// zombies 
class Zombie :public Agent
{
public:
	Zombie();
	Zombie(glm::vec2 position, glm::vec2 dimensions, const std::string& path_to_texture);
	~Zombie();

	void updatePosition(const std::vector<Human>& humans);
	void updatePosition(const Player& player);
	void updatePosition(const std::vector<Human>& humans, const Player& player);

private:
	
};

