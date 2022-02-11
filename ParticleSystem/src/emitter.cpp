#include "emitter.h"

emitter::emitter()
	:particleShader("res/particleVertexShader.shader", "res/particleFragmentShader.shader")
{
	for (int i = 0; i < numParticles; i++)
	{
		translations[i].x = random_number_between(-0.8f, 0.8f);
		translations[i].y = random_number_between(-0.8f, 0.8f);
		translations[i].z = 0;

		lifetimes[i] = random_number_between(3.0f, 4.0f);
	}

	float quadVertices[] = {
		// positions         
	   -0.02f,  0.02f, 0.0f, 
		0.02f, -0.02f, 0.0f, 
	   -0.02f, -0.02f, 0.0f, 
	   -0.02f,  0.02f, 0.0f, 
		0.02f, -0.02f, 0.0f, 
		0.02f,  0.02f, 0.0f 
	};

	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &instancedTranslationVBO);				// buffer containing translation data
	glBindBuffer(GL_ARRAY_BUFFER, instancedTranslationVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * numParticles, &translations[0], GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glVertexAttribDivisor(1, 1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	previousTime = glfwGetTime();
}

void emitter::update()
{
	for (int i = 0; i < numParticles; i++)
	{
		translations[i].y -= dt;
		lifetimes[i] -= (glfwGetTime() - previousTime);

		if (lifetimes[i] <= 0)
		{
			translations[i].x = random_number_between(-0.8f, 0.8f);
			translations[i].y = random_number_between(-0.8f, 0.8f);
			translations[i].z = 0;

			lifetimes[i] = random_number_between(2.0f, 4.0f);
		}
	}

	previousTime = glfwGetTime();
}

void emitter::draw()
{
	particleShader.use();
	glBindBuffer(GL_ARRAY_BUFFER, instancedTranslationVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * numParticles, &translations[0], GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(VAO);
	glDrawArraysInstanced(GL_TRIANGLES, 0, 6, numParticles);
}
