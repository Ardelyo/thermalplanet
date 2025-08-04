#include "Renderer.h"
#include <iostream>
#include <glad/glad.h>

// Shader sources
const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in float aTemp;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out float temperature;
void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    gl_PointSize = 2.0; // Adjust particle size
    temperature = aTemp;
}
)";

const char* fragmentShaderSource = R"(
#version 330 core
in float temperature;
out vec4 FragColor;
void main()
{
    // Temperature range from 1000K (blue) to 3000K (red)
    float t = clamp((temperature - 1000.0) / 2000.0, 0.0, 1.0);
    vec3 cold = vec3(0.0, 0.0, 1.0); // Blue
    vec3 hot = vec3(1.0, 0.0, 0.0);  // Red
    vec3 color = mix(cold, hot, t);
    FragColor = vec4(color, 1.0);
}
)";

Renderer::Renderer() : window(nullptr) {}

Renderer::~Renderer() {
    cleanup();
}

bool Renderer::init(int width, int height, const char* title) {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    glViewport(0, 0, width, height);
    glEnable(GL_PROGRAM_POINT_SIZE);

    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    ImGui::StyleColorsDark();

    compileShaders();

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &tempVBO);

    // Setup camera
    view = glm::lookAt(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 1000.0f);

    return true;
}

void Renderer::render(const std::vector<Particle>& particles) {
    processInput(window);

    // Start ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Render ImGui window
    renderImGui();

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shaderProgram);

    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, &projection[0][0]);

    glBindVertexArray(VAO);
    
    // Update positions
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, particles.size() * sizeof(glm::vec3), nullptr, GL_DYNAMIC_DRAW);
    glm::vec3* positions = (glm::vec3*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    if (positions) {
        for (size_t i = 0; i < particles.size(); ++i) {
            positions[i] = glm::vec3(particles[i].px, particles[i].py, particles[i].pz);
        }
        glUnmapBuffer(GL_ARRAY_BUFFER);
    }

    // Update temperatures
    glBindBuffer(GL_ARRAY_BUFFER, tempVBO);
    glBufferData(GL_ARRAY_BUFFER, particles.size() * sizeof(float), nullptr, GL_DYNAMIC_DRAW);
    float* temperatures = (float*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    if (temperatures) {
        for (size_t i = 0; i < particles.size(); ++i) {
            temperatures[i] = particles[i].temperature;
        }
        glUnmapBuffer(GL_ARRAY_BUFFER);
    }

    // Set up vertex attributes
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, tempVBO);
    glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    glDrawArrays(GL_POINTS, 0, particles.size());

    // Render ImGui
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Renderer::renderImGui() {
    ImGui::Begin("Simulation Controls");
    
    ImGui::Text("Simulation Parameters");
    ImGui::Checkbox("Pause", &simParams.paused);
    ImGui::SliderFloat("Time Step", &simParams.dt, 0.1f, 10.0f, "%.1f s");
    ImGui::SliderFloat("Min Temperature", &simParams.minTemp, 500.0f, 2000.0f, "%.0f K");
    ImGui::SliderFloat("Max Temperature", &simParams.maxTemp, 2000.0f, 5000.0f, "%.0f K");
    
    ImGui::End();
}

void Renderer::cleanup() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &tempVBO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
}

bool Renderer::window_should_close() {
    return glfwWindowShouldClose(window);
}

void Renderer::processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void Renderer::compileShaders() {
    // Vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Link shaders
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}
