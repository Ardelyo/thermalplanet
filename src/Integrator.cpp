#include "Integrator.h"

void integrate(std::vector<Particle>& particles, double dt) {
    const double cooling_rate = 0.001; // Adjust this value as needed

    for (auto& p : particles) {
        p.px += p.vx * dt;
        p.py += p.vy * dt;
        p.pz += p.vz * dt;

        // Apply cooling effect
        p.temperature -= cooling_rate * p.temperature * dt;
        if (p.temperature < 0) p.temperature = 0; // Ensure temperature doesn't go below zero
    }
}
