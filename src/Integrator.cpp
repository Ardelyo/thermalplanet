#include "Integrator.h"

void integrate(std::vector<Particle>& particles, double dt) {
    for (auto& p : particles) {
        p.px += p.vx * dt;
        p.py += p.vy * dt;
        p.pz += p.vz * dt;
    }
}
