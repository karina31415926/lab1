#include "structures/universe.h"
#include <limits>
#include <stdexcept>

// Calculate the smallest bounding box that contains all celestial bodies
BoundingBox Universe::get_bounding_box() const {
    if (positions.empty()) {
        throw std::runtime_error("No celestial bodies in the universe to calculate a bounding box.");
    }

    // Initialize min and max values to extreme values
    double x_min = std::numeric_limits<double>::max();
    double x_max = std::numeric_limits<double>::lowest();
    double y_min = std::numeric_limits<double>::max();
    double y_max = std::numeric_limits<double>::lowest();

    // Loop through all positions to find min and max bounds
    for (const auto& position : positions) {
        x_min = std::min(x_min, position[0]);
        x_max = std::max(x_max, position[0]);
        y_min = std::min(y_min, position[1]);
        y_max = std::max(y_max, position[1]);
    }

    // Return a BoundingBox with the computed bounds
    return BoundingBox(x_min, x_max, y_min, y_max);
}

