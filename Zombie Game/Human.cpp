#include "Human.h"

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
