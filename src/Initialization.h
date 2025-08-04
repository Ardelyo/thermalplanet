#ifndef INITIALIZATION_H
#define INITIALIZATION_H

#include <vector>
#include "Particle.h"

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
);

#endif // INITIALIZATION_H
