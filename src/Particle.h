#ifndef PARTICLE_H
#define PARTICLE_H

struct Particle {
    double px, py, pz; // Position
    double vx, vy, vz; // Velocity
    double mass;
    double temperature;
};

#endif // PARTICLE_H
