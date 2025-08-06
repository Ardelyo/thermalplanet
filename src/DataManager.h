#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <vector>
#include <string>
#include "Particle.h"

class DataManager {
public:
    static bool save_state(const std::string& filename, const std::vector<Particle>& particles);
    static bool load_state(const std::string& filename, std::vector<Particle>& particles);
};

#endif // DATAMANAGER_H
