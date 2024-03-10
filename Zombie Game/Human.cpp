#include "Human.h"
#include "Zombie.h"
#include "Textures.h"

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

void Human::update(std::vector<Zombie*>& zombies)
{
	// if human is dead no need to update
	if (Agent::getState() == AGENT_STATE::DEAD)
	{
		return;
	}
	// if human has not collided with A zombie than move human away from zombies
	if (!checkCollisions(zombies))
	{
		updatePosition(zombies);

	}
}

bool Human::checkCollisions(std::vector<Zombie*>& zombies)
{
	for (const Zombie* z : zombies)
	{
		// if zombie is dead do not check for collisions
		if (z->getState() == AGENT_STATE::DEAD)
		{
			continue;
		}

		// if current human has collided with a zombie, create a new zombie in the position of the human
		if (Agent::isCollidedWithAgent(z->getCenterPosition(), z->getDimensions().x))
		{
			Zombie* new_zombie{ new Zombie(Agent::getPosition(),Agent::getDimensions(),TEXTURES::ZOMBIE) };
			zombies.push_back(new_zombie);
			// set human's state to dead
			Agent::setState(AGENT_STATE::DEAD);

			// return true to indidicate collision with zombie
			return true;
		}
	}
	// return false to indicate no detected collision
	return false;
}

void Human::updatePosition(const std::vector<Zombie*>& zombies)
{
	glm::vec2 this_center{ this->getCenterPosition() };
	float min_distance{0};
	glm::vec2 new_direction{0,0};
	
	int i{ 0 };
	// find first alive zombie and use that to set min distance and new_direction (currently assume there will always be an alive zombie)
	for (; i < zombies.size(); i++)
	{
		if (zombies[i]->getState() == AGENT_STATE::ALIVE)
		{
			min_distance = glm::distance(this_center, zombies[i]->getCenterPosition());
			new_direction = glm::normalize(zombies[i]->getCenterPosition() - this_center ) * -1.0f;
			i++;
			break;
		}
	}


	for (; i < zombies.size(); i++)
	{
		// if zombie is dead then don't use it to update position
		if (zombies[i]->getState() == AGENT_STATE::DEAD)
		{
			continue;
		}
		// calculate distance between this zombie and human i
		glm::vec2 zombie_center{ zombies[i]->getCenterPosition() };
		float d{ glm::distance(zombie_center,this_center) };
		// if the distance is smaller than all other distances seen so far set direction of zombie so it chases human i
		if (d < min_distance)
		{
			min_distance = d;
			new_direction = glm::normalize(zombie_center - this_center) * -1.0f;
		}
	}

	// set x and y components seperately so that zombie will still move even if one direction places them in a wall
	// set x component
	setPosition(getPosition() + (glm::vec2(new_direction.x, 0) * static_cast<float>(Agent::getSpeed())));
	// set y component
	setPosition(getPosition() + (glm::vec2(0, new_direction.y) * static_cast<float>(Agent::getSpeed())));
}
