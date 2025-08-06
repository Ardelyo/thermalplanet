#include "Gravity.h"
#include <cmath>

const double G = 6.67430e-11;

void compute_forces(const std::vector<Particle>& particles, std::vector<std::array<double, 3>>& forces) {
    forces.assign(particles.size(), {0.0, 0.0, 0.0});

    for (size_t i = 0; i < particles.size(); ++i) {
        for (size_t j = i + 1; j < particles.size(); ++j) {
            double dx = particles[j].px - particles[i].px;
            double dy = particles[j].py - particles[i].py;
            double dz = particles[j].pz - particles[i].pz;
            double dist_sq = dx*dx + dy*dy + dz*dz;
            double dist = std::sqrt(dist_sq);

            if (dist > 1e-9) { // Avoid division by zero
                double force = G * particles[i].mass * particles[j].mass / dist_sq;
                double fx = force * dx / dist;
                double fy = force * dy / dist;
                double fz = force * dz / dist;

                forces[i][0] += fx;
                forces[i][1] += fy;
                forces[i][2] += fz;

                forces[j][0] -= fx;
                forces[j][1] -= fy;
                forces[j][2] -= fz;
            }
        }
    }
}

void apply_gravity(std::vector<Particle>& particles, double dt) {
    std::vector<std::array<double, 3>> forces;
    compute_forces(particles, forces);

    for (size_t i = 0; i < particles.size(); ++i) {
        particles[i].vx += forces[i][0] / particles[i].mass * dt;
        particles[i].vy += forces[i][1] / particles[i].mass * dt;
        particles[i].vz += forces[i][2] / particles[i].mass * dt;
    }
}
