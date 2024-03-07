#include "Zombie.h"

#include <iostream>

Zombie::Zombie()
	:Agent()
{
}

Zombie::Zombie(glm::vec2 position, glm::vec2 dimensions, const std::string& path_to_texture)
	:Agent(position,dimensions,path_to_texture)
{
}

Zombie::~Zombie()
{
}

void Zombie::updatePosition(const std::vector<Player>& humans)
{
	if (humans.size() == 0)
	{
		return;
	}
	
	glm::vec2 this_center{ this->getCenterPosition() };
	// set initial values for min_distance and direction to first human in vector
	float min_distance{glm::distance(humans[0].getCenterPosition(),this_center)};
	glm::vec2 new_direction{glm::normalize(humans[0].getCenterPosition() - this_center)};

	for (int i{ 1 }; i < humans.size(); i++)
	{
		// calculate distance between this zombie and human i
		glm::vec2 human_center{ humans[i].getCenterPosition() };
		float d{ glm::distance(human_center,this_center) };
		// if the distance is smaller than all other distances seen so far set direction of zombie so it chases human i
		if (d < min_distance)
		{
			min_distance = d;
			new_direction = glm::normalize(human_center - this_center);
		}
	}

	std::cout << new_direction.x << ',' << new_direction.y << '\n';
	setPosition(getPosition() + (new_direction * static_cast<float>(getSpeed())));
}

void Zombie::updatePosition(const Player& player)
{
	glm::vec2 new_direction{ glm::normalize(player.getCenterPosition() - this->getCenterPosition()) };
	setPosition(getPosition() + (new_direction * static_cast<float>(getSpeed())));
}
