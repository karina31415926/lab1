#pragma once

#include <cstdint>
#include <vector>
#include "structures/vector2d.h"
#include "structures/bounding_box.h"

class Universe {
public:
    // Fields to store universe data
    std::uint32_t num_bodies;                       // Total number of celestial bodies
    std::uint32_t current_simulation_epoch;         // Number of simulated epochs
    std::vector<double> weights;                    // Masses of celestial bodies
    std::vector<Vector2d<double>> forces;           // Forces acting on celestial bodies
    std::vector<Vector2d<double>> velocities;       // Velocities of celestial bodies
    std::vector<Vector2d<double>> positions;        // Positions of celestial bodies

    // Default constructor initializes an empty universe at epoch 0
    Universe() : num_bodies(0), current_simulation_epoch(0) {}

    // Method to calculate and return the bounding box of all celestial bodies
    BoundingBox get_bounding_box() const;
};