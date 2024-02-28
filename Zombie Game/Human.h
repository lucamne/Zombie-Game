#pragma once
#include "Agent.h"

#include <glm/glm.hpp>

class Human : public Agent
{
public:
	Human();
	Human(glm::vec2 position, glm::vec2 dimensions, const std::string& path_to_texture);
	~Human();
private:

};

