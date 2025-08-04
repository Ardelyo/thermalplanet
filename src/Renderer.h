#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "Particle.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

class Renderer {
public:
    Renderer();
    ~Renderer();

    bool init(int width, int height, const char* title);
    void render(const std::vector<Particle>& particles);
    void cleanup();
    bool window_should_close();

    // Simulation parameters that can be modified through ImGui
    struct SimParams {
        float dt = 1.0f;
        float minTemp = 1000.0f;
        float maxTemp = 3000.0f;
        bool paused = false;
    } simParams;

private:
    GLFWwindow* window;
    unsigned int shaderProgram;
    unsigned int VAO, VBO, tempVBO;

    glm::mat4 view;
    glm::mat4 projection;

    void processInput(GLFWwindow *window);
    void compileShaders();
    void renderImGui();
};

#endif // RENDERER_H
