#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include <vector>
#include "Particle.h"

void rk4_integrate(std::vector<Particle>& particles, double dt);
void handle_collisions(std::vector<Particle>& particles);

#endif // INTEGRATOR_H
