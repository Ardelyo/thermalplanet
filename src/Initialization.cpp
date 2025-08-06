#include "Initialization.h"
#include <random>
#include <cmath>

void initialize_spheres(
    std::vector<Particle>& particles,
    int num_particles_target,
    double target_mass,
    double target_radius,
    double target_px, double target_py, double target_pz,
    double target_vx, double target_vy, double target_vz,
    int num_particles_impactor,
    double impactor_mass,
    double impactor_radius,
    double impactor_px, double impactor_py, double impactor_pz,
    double impactor_vx, double impactor_vy, double impactor_vz
) {
    particles.clear();
    std::mt19937 gen(12345); // for reproducibility
    std::uniform_real_distribution<> dis(-1.0, 1.0);

    // Target
    double target_particle_mass = target_mass / num_particles_target;
    for (int i = 0; i < num_particles_target; ++i) {
        double x, y, z, r2;
        do {
            x = dis(gen);
            y = dis(gen);
            z = dis(gen);
            r2 = x*x + y*y + z*z;
        } while (r2 > 1.0);
        Particle p;
        p.px = target_px + target_radius * x;
        p.py = target_py + target_radius * y;
        p.pz = target_pz + target_radius * z;
        p.vx = target_vx;
        p.vy = target_vy;
        p.vz = target_vz;
        p.mass = target_particle_mass;
        p.radius = target_particle_radius;
        p.temperature = 2000; // Initial temp
        particles.push_back(p);
    }

    // Impactor
    double impactor_particle_mass = impactor_mass / num_particles_impactor;
    double impactor_particle_radius = impactor_radius / std::cbrt(num_particles_impactor);
    for (int i = 0; i < num_particles_impactor; ++i) {
        double x, y, z, r2;
        do {
            x = dis(gen);
            y = dis(gen);
            z = dis(gen);
            r2 = x*x + y*y + z*z;
        } while (r2 > 1.0);
        Particle p;
        p.px = impactor_px + impactor_radius * x;
        p.py = impactor_py + impactor_radius * y;
        p.pz = impactor_pz + impactor_radius * z;
        p.vx = impactor_vx;
        p.vy = impactor_vy;
        p.vz = impactor_vz;
        p.mass = impactor_particle_mass;
        p.radius = impactor_particle_radius;
        p.temperature = 2000; // Initial temp
        particles.push_back(p);
    }
}
