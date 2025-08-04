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

                // Calculate kinetic energy change due to gravitational interaction
                double v_rel_sq = 
                    (particles[j].vx - particles[i].vx) * (particles[j].vx - particles[i].vx) +
                    (particles[j].vy - particles[i].vy) * (particles[j].vy - particles[i].vy) +
                    (particles[j].vz - particles[i].vz) * (particles[j].vz - particles[i].vz);
                
                // Convert some kinetic energy to heat
                double heat_factor = 0.1; // 10% of kinetic energy goes to heat
                double heat_transfer = heat_factor * 0.5 * v_rel_sq * dt;
                
                // Update temperatures based on kinetic energy conversion
                particles[i].temperature += heat_transfer / particles[i].mass;
                particles[j].temperature += heat_transfer / particles[j].mass;

                // Apply gravitational forces
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
