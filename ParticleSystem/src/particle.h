#pragma once

#include<glm/glm.hpp>

class particle
{
public:
	glm::vec3 position = glm::vec3(0.0f);
	glm::vec3 force = glm::vec3(0.0f);
	float lifetime = 0;
};