#pragma once
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include"shader_class.h"
#include"utility.h"

class emitter
{
public:

	int numParticles = 100;
	float dt = 0.0001;					//fall down speed
	float previousTime = 0;			//previous frame time used for updating lifetimes

	glm::vec3 translations[2000];		//position offset of particles
	float lifetimes[2000];

	unsigned int VBO;					
	unsigned int VAO;
	unsigned int instancedTranslationVBO;

	Shader particleShader;

	emitter();

	void update();
	void draw();
};