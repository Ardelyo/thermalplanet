#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "Particle.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Renderer {
public:
    Renderer();
    ~Renderer();

    bool init(int width, int height, const char* title);
    void render(const std::vector<Particle>& particles);
    void cleanup();
    bool window_should_close();

private:
    GLFWwindow* window;
    unsigned int shaderProgram;
    unsigned int VAO, VBO;

    glm::mat4 view;
    glm::mat4 projection;

    void processInput(GLFWwindow *window);
    void compileShaders();
};

#endif // RENDERER_H
