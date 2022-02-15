#pragma once
#include"imgui/imgui.h"
#include"imgui/imgui_impl_glfw.h"
#include"imgui/imgui_impl_opengl3.h"
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>

class guiLayer
{
public:
	guiLayer(GLFWwindow* window);
	~guiLayer();

	void changeColor(float color[3]);
	void changeParameters(int &numParticles, float &forceMul, glm::vec3& scaleVec);
	void render();
};