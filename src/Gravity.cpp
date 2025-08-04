#include "Gravity.h"
#include <cmath>

const double G = 6.67430e-11;

void apply_gravity(std::vector<Particle>& particles, double dt) {
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

                particles[i].vx += fx / particles[i].mass * dt;
                particles[i].vy += fy / particles[i].mass * dt;
                particles[i].vz += fz / particles[i].mass * dt;

                particles[j].vx -= fx / particles[j].mass * dt;
                particles[j].vy -= fy / particles[j].mass * dt;
                particles[j].vz -= fz / particles[j].mass * dt;
            }
        }
    }
}
