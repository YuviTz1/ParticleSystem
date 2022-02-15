#include "emitter.h"

emitter::emitter()
	:particleShader("res/particleVertexShader.shader", "res/particleFragmentShader.shader"), particleVec(2000)
{
	for (int i = 0; i < numParticles; i++)
	{
		//randomise particle starting position, lifetime and force
		particleVec[i].position.x = random_number_between(-0.6f, -0.5f);
		particleVec[i].position.y = random_number_between(-1.0f, -0.8f);
		particleVec[i].position.z = 0;
		particleVec[i].lifetime = random_number_between(3.0f, 6.0f);

		particleVec[i].force.x = random_number_between(-0.00004, 0.00004);
		particleVec[i].force.y = random_number_between(0.00014, 0.00025);
		particleVec[i].force.z = 0;

		particleVec[i].force *= forceMultiplier;
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

	//setup OpenGL buffers
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &instancedTranslationVBO);				// buffer containing translation data
	glBindBuffer(GL_ARRAY_BUFFER, instancedTranslationVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(particle)*numParticles, particleVec.data(), GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(particle), (void*)0);
	glVertexAttribDivisor(1, 1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	previousTime = glfwGetTime();
	scaleMat = glm::scale(scaleMat, glm::vec3(1.0f, 1.0f, 1.0f));
}

void emitter::update()
{
	for (int i = 0; i < numParticles; i++)
	{
		particleVec[i].position.y -= dt;
		particleVec[i].position += particleVec[i].force;
		particleVec[i].lifetime -= (glfwGetTime() - previousTime);

		//respawn dead particle with new position, lifetime and force
		if (particleVec[i].lifetime <= 0)
		{
			particleVec[i].position.x = random_number_between(-0.6f, -0.5f);
			particleVec[i].position.y = random_number_between(-1.0f, -0.8f);
			particleVec[i].position.z = 0;
			particleVec[i].lifetime = random_number_between(3.0f, 6.0f);

			particleVec[i].force.x = random_number_between(-0.00004, 0.00004);
			particleVec[i].force.y = random_number_between(0.00014, 0.00025);
			particleVec[i].force.z = 0;

			particleVec[i].force *= forceMultiplier;
		}
	}

	previousTime = glfwGetTime();
	scaleMat = glm::scale(glm::mat4(1.0f), scaleVec);
}

void emitter::draw()
{
	particleShader.use();

	//set scale matrix uniform
	unsigned int scaleMatLoc = glGetUniformLocation(particleShader.ID, "scaleMat");
	glUniformMatrix4fv(scaleMatLoc, 1, GL_FALSE, glm::value_ptr(scaleMat));

	//set color uniform
	unsigned int colorVecLoc = glGetUniformLocation(particleShader.ID, "fColor");
	glUniform3f(colorVecLoc, particleColor[0], particleColor[1], particleColor[2]);
	

	glBindBuffer(GL_ARRAY_BUFFER, instancedTranslationVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(particle) * numParticles, particleVec.data(), GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(VAO);
	glDrawArraysInstanced(GL_TRIANGLES, 0, 6, numParticles);
}