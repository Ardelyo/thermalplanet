#include "Integrator.h"

void rk4_integrate(std::vector<Particle>& particles, double dt) {
    std::vector<Particle> initial_particles = particles;
    std::vector<Particle> k1_particles = particles;
    std::vector<Particle> k2_particles = particles;
    std::vector<Particle> k3_particles = particles;
    std::vector<Particle> k4_particles = particles;

    std::vector<std::array<double, 3>> forces;

    // k1
    compute_forces(initial_particles, forces);
    for (size_t i = 0; i < particles.size(); ++i) {
        k1_particles[i].px = initial_particles[i].vx * dt;
        k1_particles[i].py = initial_particles[i].vy * dt;
        k1_particles[i].pz = initial_particles[i].vz * dt;
        k1_particles[i].vx = forces[i][0] / initial_particles[i].mass * dt;
        k1_particles[i].vy = forces[i][1] / initial_particles[i].mass * dt;
        k1_particles[i].vz = forces[i][2] / initial_particles[i].mass * dt;
    }

    // k2
    for (size_t i = 0; i < particles.size(); ++i) {
        k2_particles[i].px = initial_particles[i].px + k1_particles[i].px * 0.5;
        k2_particles[i].py = initial_particles[i].py + k1_particles[i].py * 0.5;
        k2_particles[i].pz = initial_particles[i].pz + k1_particles[i].pz * 0.5;
    }
    compute_forces(k2_particles, forces);
    for (size_t i = 0; i < particles.size(); ++i) {
        k2_particles[i].vx = forces[i][0] / initial_particles[i].mass * dt;
        k2_particles[i].vy = forces[i][1] / initial_particles[i].mass * dt;
        k2_particles[i].vz = forces[i][2] / initial_particles[i].mass * dt;
    }

    // k3
    for (size_t i = 0; i < particles.size(); ++i) {
        k3_particles[i].px = initial_particles[i].px + k2_particles[i].px * 0.5;
        k3_particles[i].py = initial_particles[i].py + k2_particles[i].py * 0.5;
        k3_particles[i].pz = initial_particles[i].pz + k2_particles[i].pz * 0.5;
    }
    compute_forces(k3_particles, forces);
    for (size_t i = 0; i < particles.size(); ++i) {
        k3_particles[i].vx = forces[i][0] / initial_particles[i].mass * dt;
        k3_particles[i].vy = forces[i][1] / initial_particles[i].mass * dt;
        k3_particles[i].vz = forces[i][2] / initial_particles[i].mass * dt;
    }

    // k4
    for (size_t i = 0; i < particles.size(); ++i) {
        k4_particles[i].px = initial_particles[i].px + k3_particles[i].px;
        k4_particles[i].py = initial_particles[i].py + k3_particles[i].py;
        k4_particles[i].pz = initial_particles[i].pz + k3_particles[i].pz;
    }
    compute_forces(k4_particles, forces);
    for (size_t i = 0; i < particles.size(); ++i) {
        k4_particles[i].vx = forces[i][0] / initial_particles[i].mass * dt;
        k4_particles[i].vy = forces[i][1] / initial_particles[i].mass * dt;
        k4_particles[i].vz = forces[i][2] / initial_particles[i].mass * dt;
    }

    // Update positions and velocities
    for (size_t i = 0; i < particles.size(); ++i) {
        particles[i].px += (k1_particles[i].px + 2 * k2_particles[i].px + 2 * k3_particles[i].px + k4_particles[i].px) / 6.0;
        particles[i].py += (k1_particles[i].py + 2 * k2_particles[i].py + 2 * k3_particles[i].py + k4_particles[i].py) / 6.0;
        particles[i].pz += (k1_particles[i].pz + 2 * k2_particles[i].pz + 2 * k3_particles[i].pz + k4_particles[i].pz) / 6.0;
        particles[i].vx += (k1_particles[i].vx + 2 * k2_particles[i].vx + 2 * k3_particles[i].vx + k4_particles[i].vx) / 6.0;
        particles[i].vy += (k1_particles[i].vy + 2 * k2_particles[i].vy + 2 * k3_particles[i].vy + k4_particles[i].vy) / 6.0;
        particles[i].vz += (k1_particles[i].vz + 2 * k2_particles[i].vz + 2 * k3_particles[i].vz + k4_particles[i].vz) / 6.0;
    }
}

void handle_collisions(std::vector<Particle>& particles) {
    for (size_t i = 0; i < particles.size(); ++i) {
        for (size_t j = i + 1; j < particles.size(); ++j) {
            double dx = particles[i].px - particles[j].px;
            double dy = particles[i].py - particles[j].py;
            double dz = particles[i].pz - particles[j].pz;
            double dist_sq = dx * dx + dy * dy + dz * dz;
            double radius_sum = particles[i].radius + particles[j].radius;

            if (dist_sq < radius_sum * radius_sum) {
                // Collision detected, merge the two particles
                Particle& p1 = particles[i];
                Particle& p2 = particles[j];

                double total_mass = p1.mass + p2.mass;
                p1.vx = (p1.vx * p1.mass + p2.vx * p2.mass) / total_mass;
                p1.vy = (p1.vy * p1.mass + p2.vy * p2.mass) / total_mass;
                p1.vz = (p1.vz * p1.mass + p2.vz * p2.mass) / total_mass;
                p1.mass = total_mass;
                p1.radius = std::cbrt(p1.radius * p1.radius * p1.radius + p2.radius * p2.radius * p2.radius);

                // Remove the second particle
                particles.erase(particles.begin() + j);
                --j; // Decrement j to account for the removed particle
            }
        }
    }
}
