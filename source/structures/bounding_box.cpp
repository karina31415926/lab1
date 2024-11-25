#include "structures/bounding_box.h"
#include <cmath>
#include <algorithm>
#include <stdexcept>

BoundingBox::BoundingBox() : x_min(0.0), x_max(0.0), y_min(0.0), y_max(0.0) {}

// Parameterized constructor initializes fields with given values
BoundingBox::BoundingBox(double x_min, double x_max, double y_min, double y_max)
    : x_min(x_min), x_max(x_max), y_min(y_min), y_max(y_max) {}

// Check if a given position lies within the bounding box (inclusive of bounds)
bool BoundingBox::contains(const Vector2d<double>& position) const {
    return position[0] >= x_min && position[0] <= x_max &&
        position[1] >= y_min && position[1] <= y_max;
}

// Retrieve a specific quadrant of the bounding box
BoundingBox BoundingBox::get_quadrant(std::uint8_t quadrant_index) const {
    // Calculate the midpoints of the bounding box
    double x_mid = (x_min + x_max) / 2.0;
    double y_mid = (y_min + y_max) / 2.0;

    switch (quadrant_index) {
    case 0: // Top-left quadrant
        return BoundingBox(x_min, x_mid, y_mid, y_max);
    case 1: // Top-right quadrant
        return BoundingBox(x_mid, x_max, y_mid, y_max);
    case 2: // Bottom-left quadrant
        return BoundingBox(x_min, x_mid, y_min, y_mid);
    case 3: // Bottom-right quadrant
        return BoundingBox(x_mid, x_max, y_min, y_mid);
    default:
        throw std::invalid_argument("Invalid quadrant index. Valid indices are 0, 1, 2, or 3.");
    }
}

// Get a string representation of the bounding box
std::string BoundingBox::get_string() const {
    return "x_min: " + std::to_string(x_min) + ", x_max: " + std::to_string(x_max) +
        ", y_min: " + std::to_string(y_min) + ", y_max: " + std::to_string(y_max);
}

// Calculate the diagonal length of the bounding box
double BoundingBox::get_diagonal() const {
    return std::max(1.0, std::sqrt(std::pow(x_max - x_min, 2) + std::pow(y_max - y_min, 2)));
}

// Perform a sanity check to ensure the bounding box dimensions are valid
void BoundingBox::plotting_sanity_check() {
    double x_size = x_max - x_min;
    double y_size = y_max - y_min;

    if (x_size == 0 && y_size != 0) {
        // Inflate x bounds to make it a square
        x_min -= y_size / 2;
        x_max += y_size / 2;
    }
    else if (y_size == 0 && x_size != 0) {
        // Inflate y bounds to make it a square
        y_min -= x_size / 2;
        y_max += x_size / 2;
    }
    else if (x_size == 0 && y_size == 0) {
        throw std::invalid_argument("Both x and y sizes are zero, cannot fix bounding box.");
    }
}

// Scale the bounding box by a given factor
BoundingBox BoundingBox::get_scaled(std::uint32_t scaling_factor) const {
    double x_mid = (x_min + x_max) / 2.0;
    double y_mid = (y_min + y_max) / 2.0;
    double x_size = x_max - x_min;
    double y_size = y_max - y_min;

    return BoundingBox(
        x_mid - x_size * scaling_factor / 2.0,
        x_mid + x_size * scaling_factor / 2.0,
        y_mid - y_size * scaling_factor / 2.0,
        y_mid + y_size * scaling_factor / 2.0
    );
}