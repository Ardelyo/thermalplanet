#include "DataManager.h"
#include <fstream>
#include <iostream>

bool DataManager::save_state(const std::string& filename, const std::vector<Particle>& particles) {
    std::ofstream ofs(filename, std::ios::binary);
    if (!ofs) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return false;
    }

    size_t num_particles = particles.size();
    ofs.write(reinterpret_cast<const char*>(&num_particles), sizeof(num_particles));
    ofs.write(reinterpret_cast<const char*>(particles.data()), num_particles * sizeof(Particle));

    return true;
}

bool DataManager::load_state(const std::string& filename, std::vector<Particle>& particles) {
    std::ifstream ifs(filename, std::ios::binary);
    if (!ifs) {
        std::cerr << "Error opening file for reading: " << filename << std::endl;
        return false;
    }

    size_t num_particles;
    ifs.read(reinterpret_cast<char*>(&num_particles), sizeof(num_particles));

    particles.resize(num_particles);
    ifs.read(reinterpret_cast<char*>(particles.data()), num_particles * sizeof(Particle));

    return true;
}
