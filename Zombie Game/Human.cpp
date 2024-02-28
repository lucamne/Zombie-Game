#include "Human.h"

Human::Human()
	:Human({0,0}, {50,50}, "")
{
}

Human::Human(glm::vec2 position, glm::vec2 dimensions, const std::string& path_to_texture)
	:Agent(position, dimensions, path_to_texture)
{
}

Human::~Human()
{
}