#include <iostream>
#include <vector>
#include "Particle.h"
#include "Initialization.h"
#include "Gravity.h"
#include "Integrator.h"
#include "Renderer.h"

#include "DataManager.h"

int main() {
    std::cout << "Project Theia Initialized!" << std::endl;

    std::vector<Particle> particles;

    // Initialize particles for two planetary bodies
    initialize_spheres(
        particles,
        1000, 5.972e24, 6.371e6, 0, 0, 0, 0, 0, 0, // Target (Earth-like)
        100, 7.342e22, 1.737e6, 7e6, 0, 0, 10000, 0, 0 // Impactor (Moon-like)
    );

    std::cout << "Initialized " << particles.size() << " particles." << std::endl;

    Renderer renderer;
    if (!renderer.init(800, 600, "Project Theia")) {
        return -1;
    }

    // Main simulation loop
    while (!renderer.window_should_close()) {
        if (glfwGetKey(renderer.get_window(), GLFW_KEY_S) == GLFW_PRESS) {
            DataManager::save_state("simulation_state.bin", particles);
            std::cout << "Simulation state saved." << std::endl;
        }

        if (glfwGetKey(renderer.get_window(), GLFW_KEY_L) == GLFW_PRESS) {
            DataManager::load_state("simulation_state.bin", particles);
            std.cout << "Simulation state loaded." << std::endl;
        }

        if (!renderer.simParams.paused) {
            apply_gravity(particles, renderer.simParams.dt);
            rk4_integrate(particles, renderer.simParams.dt);
            handle_collisions(particles);
        }

        renderer.render(particles);
    }

    std::cout << "Simulation finished." << std::endl;

    return 0;
}
