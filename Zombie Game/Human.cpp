#include "Human.h"

#include "Zombie.h"

Human::Human()
	:Agent()
{
}

Human::Human(glm::vec2 position, glm::vec2 dimensions, const std::string& path_to_texture)
	:Agent(position, dimensions, path_to_texture)
{
}

Human::~Human()
{
}

void Human::updatePosition(const std::vector<Zombie*>& zombies)
{
	glm::vec2 this_center{ this->getCenterPosition() };
	// set initial values for min_distance and direction to first human in vector
	float min_distance{ glm::distance(zombies[0]->getCenterPosition(),this_center) };
	// new direction is opposite the direction of the nearest zombie
	glm::vec2 new_direction{ glm::normalize(zombies[0]->getCenterPosition() - this_center) * -1.0f};

	for (int i{ 1 }; i < zombies.size(); i++)
	{
		// calculate distance between this zombie and human i
		glm::vec2 human_center{ zombies[i]->getCenterPosition() };
		float d{ glm::distance(human_center,this_center) };
		// if the distance is smaller than all other distances seen so far set direction of zombie so it chases human i
		if (d < min_distance)
		{
			min_distance = d;
			new_direction = glm::normalize(human_center - this_center) * -1.0f;
		}
	}

	// set x and y components seperately so that zombie will still move even if one direction places them in a wall
	// set x component
	setPosition(getPosition() + (glm::vec2(new_direction.x, 0) * static_cast<float>(Agent::getSpeed())));
	// set y component
	setPosition(getPosition() + (glm::vec2(0, new_direction.y) * static_cast<float>(Agent::getSpeed())));
}
