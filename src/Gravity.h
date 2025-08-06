#ifndef GRAVITY_H
#define GRAVITY_H

#include <vector>
#include <array>
#include "Particle.h"

void compute_forces(const std::vector<Particle>& particles, std::vector<std::array<double, 3>>& forces);
void apply_gravity(std::vector<Particle>& particles, double dt);

#endif // GRAVITY_H
