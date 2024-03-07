#include "Player.h"

Player::Player()
	:Player({0,0},{50,50},"")
{
}

Player::Player(glm::vec2 position, glm::vec2 dimensions, const std::string& path_to_texture)
	:Human(position,dimensions,path_to_texture)
{
}

Player::~Player()
{
}

void Player::movePlayer(glm::vec2 direction)
{
	glm::vec2 move_direc{ glm::normalize(direction) };

	Agent::setPosition(Agent::getPosition() + move_direc * static_cast<float>(Agent::getSpeed()));
}
