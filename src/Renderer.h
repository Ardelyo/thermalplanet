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
    GLFWwindow* get_window() { return window; }

    // Simulation parameters that can be modified through ImGui
    enum ColoringMode {
        TEMPERATURE,
        VELOCITY
    };

    struct SimParams {
        float dt = 1.0f;
        float minTemp = 1000.0f;
        float maxTemp = 3000.0f;
        bool paused = false;
        float G = 6.67430e-11f;
        float particleSize = 2.0f;
        int particleCount = 0;
        ColoringMode coloringMode = TEMPERATURE;
        bool showVelocityVectors = false;
    } simParams;

private:
    GLFWwindow* window;
    unsigned int particleShaderProgram;
    unsigned int vectorShaderProgram;
    unsigned int VAO, VBO, tempVBO, velVBO;

    glm::mat4 view;
    glm::mat4 projection;

    void processInput(GLFWwindow *window);
    void compileShaders();
    void renderImGui();
};

#endif // RENDERER_H
