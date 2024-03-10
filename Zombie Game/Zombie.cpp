#include "Zombie.h"
#include "Human.h"

#include <iostream>

Zombie::Zombie()
	:Agent()
{
}

Zombie::Zombie(glm::vec2 position, glm::vec2 dimensions, const std::string& path_to_texture)
	:Agent(position,dimensions,path_to_texture)
{
	Agent::setSpeed(3.0f);
	Agent::setColor({ 255, 0, 0, 255 });
}

Zombie::~Zombie()
{
}

void Zombie::updatePosition(const std::vector<Human*>& humans)
{
	if (humans.size() == 0)
	{
		return;
	}
	
	glm::vec2 this_center{ this->getCenterPosition() };
	float min_distance{};
	glm::vec2 new_direction{};

	int i{ 0 };

	// find first alive human and set min_distance and new_direction with that human
	for (; i < humans.size(); i++)
	{
		if (humans[i]->getState() == AGENT_STATE::ALIVE)
		{
			min_distance = glm::distance(humans[i]->getCenterPosition(), this_center);
			new_direction = glm::normalize(humans[i]->getCenterPosition() - this_center);
			i++;
			break;
		}
	}

	for (; i < humans.size(); i++)
	{
		// if human is dead then do not use it to determine zombie position
		if (humans[i]->getState() == AGENT_STATE::DEAD)
		{
			continue;
		}

		// calculate distance between this zombie and human i
		glm::vec2 human_center{ humans[i]->getCenterPosition() };
		float d{ glm::distance(human_center,this_center) };
		// if the distance is smaller than all other distances seen so far set direction of zombie so it chases human i
		if (d < min_distance)
		{
			min_distance = d;
			new_direction = glm::normalize(human_center - this_center);
		}
	}

	Agent::setPosition(Agent::getPosition() + (new_direction * static_cast<float>(Agent::getSpeed())));
}

void Zombie::updatePosition(const Player& player)
{
	glm::vec2 new_direction{ glm::normalize(player.getCenterPosition() - this->getCenterPosition()) };

	// set x and y components seperately so that zombie will still move even if one direction places them in a wall

	// set x component
	setPosition(getPosition() + (glm::vec2(new_direction.x,0) *static_cast<float>(Agent::getSpeed())));
	// set y component
	setPosition(getPosition() + (glm::vec2(0, new_direction.y) * static_cast<float>(Agent::getSpeed())));

}

void Zombie::updatePosition(const std::vector<Human*>& humans, const Player& player)
{
	glm::vec2 this_center{ this->getCenterPosition() };
	// set initial values for min_distance and direction to first human in vector
	float min_distance{ glm::distance(player.getCenterPosition(),this_center) };
	glm::vec2 new_direction{ glm::normalize(player.getCenterPosition() - this_center) };

	for (int i{ 0 }; i < humans.size(); i++)
	{
		// if human is dead then do not use it to determine zombie position
		if (humans[i]->getState() == AGENT_STATE::DEAD)
		{
			continue;
		}

		// calculate distance between this zombie and human i
		glm::vec2 human_center{ humans[i]->getCenterPosition() };
		float d{ glm::distance(human_center,this_center) };
		// if the distance is smaller than all other distances seen so far set direction of zombie so it chases human i
		if (d < min_distance)
		{
			min_distance = d;
			new_direction = glm::normalize(human_center - this_center);
		}
	}


	// set x and y components seperately so that zombie will still move even if one direction places them in a wall
	// set x component
	setPosition(getPosition() + (glm::vec2(new_direction.x, 0) * static_cast<float>(Agent::getSpeed())));
	// set y component
	setPosition(getPosition() + (glm::vec2(0, new_direction.y) * static_cast<float>(Agent::getSpeed())));
}
