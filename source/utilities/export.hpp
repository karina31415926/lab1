#pragma once
#include <filesystem>
#include <fstream>

static void save_universe(const std::filesystem::path& save_universe_path, const Universe& universe) {
    // Open the output file stream
    std::ofstream universe_file(save_universe_path);
    if (!universe_file.is_open()) {
        throw std::invalid_argument("Could not open file to save the universe!");
    }

    // Set precision for double values
    universe_file << std::fixed << std::setprecision(6);

    // Write body count
    universe_file << "### Bodies" << std::endl;
    universe_file << universe.num_bodies << std::endl;

    // Write positions
    universe_file << "### Positions" << std::endl;
    for (const auto& position : universe.positions) {
        // Access the components using the operator[]
        universe_file << position[0] << " " << position[1] << std::endl;
    }

    // Write weights
    universe_file << "### Weights" << std::endl;
    for (const auto& weight : universe.weights) {
        universe_file << weight << std::endl;
    }

    // Write velocities
    universe_file << "### Velocities" << std::endl;
    for (const auto& velocity : universe.velocities) {
        // Access the components using the operator[]
        universe_file << velocity[0] << " " << velocity[1] << std::endl;
    }

    // Write forces
    universe_file << "### Forces" << std::endl;
    for (const auto& force : universe.forces) {
        // Access the components using the operator[]
        universe_file << force[0] << " " << force[1] << std::endl;
    }

    // Close the file
    universe_file.close();
}

