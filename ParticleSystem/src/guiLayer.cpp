#include "guiLayer.h"

guiLayer::guiLayer(GLFWwindow* window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

guiLayer::~guiLayer()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void guiLayer::changeColor(float color[3])
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Particle Color", NULL);
	ImGui::ColorPicker3("Color", color);
	ImGui::End();
}

void guiLayer::changeParameters(int &numParticles, float &forceMul, glm::vec3& scaleVec)
{
	ImGui::Begin("Particle Parameters", NULL);
	ImGui::SliderFloat2("Size", &scaleVec.x, 0.1f, 4.0f);
	ImGui::SliderInt("Number", &numParticles, 100, 2000);
	ImGui::SliderFloat("force", &forceMul, 0.5f, 5.0f);

	ImGui::Text("Application Average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

	ImGui::End();
}

void guiLayer::render()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
