#include <iostream>
#include <vector>
#include "Particle.h"
#include "Initialization.h"
#include "Gravity.h"
#include "Integrator.h"
#include "Renderer.h"

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

    double dt = 1.0; // Time step in seconds

    // Main simulation loop
    while (!renderer.window_should_close()) {
        apply_gravity(particles, dt);
        integrate(particles, dt);

        renderer.render(particles);
    }

    std::cout << "Simulation finished." << std::endl;

    return 0;
}
